using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using WEB_253502_Lishykk.API.Data;
using WEB_253502_Lishykk.API.Models;
using WEB_253502_Lishykk.API.Services.CarService;
using WEB_253502_Lishykk.Domain.Entities;
using WEB_253502_Lishykk.Domain.Models;

namespace WEB_253502_Lishykk.API.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class CarController(ICarService carService, ILogger<CarController> logger) : ControllerBase
    {
        private readonly ICarService _carService = carService;
        private readonly ILogger<CarController> _logger= logger;

        // GET: api/Car
        //[HttpGet("category/{category?}")]
        [HttpGet("{category?}")]
        [AllowAnonymous]
        public async Task<ActionResult<ResponseData<List<CarDTO>>>> GetCars(string? category, int pageNo = 1, int pageSize = 3)
        {
            return Ok(await _carService.GetCarListAsync(category, pageNo, pageSize));
        }

        // GET: api/Car/5
        [HttpGet("{id:int}")]
        [Authorize(Policy = "admin")]
        public async Task<ActionResult<ResponseData<CarDTO>>> GetCar(int id)
        {
            var claims = User.Claims;
            foreach (var claim in claims)
            {
                _logger.LogInformation($"Claim Type: {claim.Type}, Claim Value: {claim.Value}");
            }
            var result = await _carService.GetCarByIdAsync(id);

            if (!result.Successfull)
            {
                return NotFound(result);
            }

            return Ok(result);
        }

        // PUT: api/Car/5
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPut("{id:int}")]
        [Authorize(Policy = "admin")]
        public async Task<ActionResult<ResponseData<Car>>> PutCar(int id, Car car)
        {
            var carResult = await _carService.UpdateCarAsync(id, car);
            if (!carResult.Successfull)
            {
                return NotFound(carResult);
            }
            return Ok(carResult);
        }

        // POST: api/Car
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPost]
        [Authorize(Policy = "admin")]
        public async Task<ActionResult<Car>> PostCar(Car car)
        {
            return Ok(await _carService.CreateCarAsync(car));
        }

        // DELETE: api/Car/5
        [HttpDelete("{id:int}")]
        [Authorize(Policy = "admin")]
        public async Task<ActionResult<ResponseData<string>>> DeleteCar(int id)
        {
            var result = await _carService.DeleteCarAsync(id);
            if (!result.Successfull)
            {
                return NotFound(result);
            }
            return Ok(result);
        }

        private bool CarExists(int id)
        {
            var car = _carService.GetCarByIdAsync(id);
            return car.Result.Successfull;
        }
    }
}
