using Microsoft.AspNetCore.Mvc;
using System.Threading.Tasks;
using WEB_253502_Lishykk.Domain.Entities;
using WEB_253502_Lishykk.UI.Services.CarService;
using WEB_253502_Lishykk.UI.Services.CategoryService;
using WEB_253502_Lishykk.UI.Extensions;

namespace WEB_253502_Lishykk.UI.Controllers
{
    [Route("Car")]
    public class CarController : Controller
    {
        private readonly ICarService _carService;
        private readonly ICategoryService _categoryService;

        public CarController(ICarService carService, ICategoryService categoryService)
        {
            _carService = carService;
            _categoryService = categoryService;
        }

        [HttpGet("{category?}")]
        // Метод для отображения списка автомобилей с фильтрацией по категории
        public async Task<IActionResult> Index(string? category, int pageNo = 1)
        {
            Console.WriteLine($"Requested Page: {pageNo}, Category: {category}"); // Логируем параметры
            var categoryResponse = await _categoryService.GetCategoryListAsync();
            if (!categoryResponse.Successfull)
                return NotFound(categoryResponse.ErrorMessage);

            ViewBag.Categories = categoryResponse.Data;

            var carResponse = await _carService.GetCarListAsync(category, pageNo);
            if (!carResponse.Successfull)
                return NotFound(carResponse.ErrorMessage);
           
            ViewData["currentCategory"] = category ?? "All";

            //return View("MyList", carResponse.Data); 

            var listModel = new WEB_253502_Lishykk.UI.Models.ListModel<Car>
            {
                Items = carResponse.Data.Items,
                CurrentPage = carResponse.Data.CurrentPage,
                TotalPages = carResponse.Data.TotalPages
            };
            // Проверяем, является ли запрос асинхронным (Ajax)
            if (Request.IsAjaxRequest())
            {
                // Возвращаем частичное представление для асинхронного обновления списка автомобилей
                return PartialView("_ListPartial", listModel);
            }
            //return View("MyList", listModel);
            return View("Index", listModel);
        }

    }
}
