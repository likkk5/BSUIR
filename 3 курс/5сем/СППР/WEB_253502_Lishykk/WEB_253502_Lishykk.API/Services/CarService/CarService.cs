using Microsoft.EntityFrameworkCore;
using System.Drawing.Printing;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.Extensions.Options;
using WEB_253502_Lishykk.API.Data;
using WEB_253502_Lishykk.Domain.Models;
using WEB_253502_Lishykk.UI.Domain.Models;
using WEB_253502_Lishykk.Domain.Entities;
using WEB_253502_Lishykk.API.Models;

namespace WEB_253502_Lishykk.API.Services.CarService
{
    public class CarService : ICarService
    {
        private readonly AppDbContext _context;
        private readonly IWebHostEnvironment _webHostEnvironment;
        private readonly string _baseUrl;
        private const int _maxPageSize = 20;

        public CarService(AppDbContext context, IWebHostEnvironment webHostEnvironment, IOptions<AppSettings> appSettings)
        {
            _context = context;
            _webHostEnvironment = webHostEnvironment;
            _baseUrl = appSettings.Value.BaseUrl;
        }

        public async Task<ResponseData<Car>> CreateCarAsync(Car car)
        {
            var Car = _context.Cars.Add(car);
            await _context.SaveChangesAsync();
            return ResponseData<Car>.Success(Car.Entity);
        }
        //public async Task<ResponseData<Car>> CreateCarAsync(Car car, IFormFile? formFile)
        //{
        //    // Если в базе данных есть элементы, получить максимальный ID, иначе установить 1
        //    car.Id = _context.Cars.Any() ? _context.Cars.Max(c => c.Id) + 1 : 1;
        //    if (formFile != null)
        //    {
        //        // Добавление нового изображения
        //        car.ImagePath = $"Images/{formFile.FileName}";
        //        car.ImageMimeType = formFile.ContentType;
        //        // Сохранение файла 
        //        var imagePath = Path.Combine("wwwroot", car.ImagePath);
        //        using (var stream = new FileStream(imagePath, FileMode.Create))
        //        {
        //            await formFile.CopyToAsync(stream);
        //        }
        //    }
        //    _context.Add(car);
        //    await _context.SaveChangesAsync();

        //    return ResponseData<Car>.Success(car);
        //}
        public async Task<ResponseData<string>> DeleteCarAsync(int id)
        {
            var query = _context.Cars.AsQueryable();
            var car = await query.FirstOrDefaultAsync(c => c.Id.Equals(id));
            if (car is not null)
            {
                _context.Cars.Remove(car);
                await _context.SaveChangesAsync();
                return ResponseData<string>.Success("Car deleted");
            }
            return ResponseData<string>.Error("No such product");
        }

        //public async Task<ResponseData<Car>> GetCarByIdAsync(int id)
        //{
        //    var query = _context.Cars.AsQueryable();
        //    var car = await query.FirstOrDefaultAsync(c => c.Id.Equals(id));

        //    if (car is null)
        //    {
        //        return ResponseData<Car>.Error("No such product", car);
        //    }
        //    return ResponseData<Car>.Success(car);
        //}
        public async Task<ResponseData<CarDTO>> GetCarByIdAsync(int id)
        {
            var query = _context.Cars.AsQueryable();
            var car = await query.FirstOrDefaultAsync(c => c.Id == id);

            if (car == null)
            {
                return ResponseData<CarDTO>.Error("No such product", null);
            }

            // Преобразование Car в CarDTO
            var carDTO = new CarDTO
            {
                Id = car.Id,
                Name = car.Name,
                Description = car.Description,
                CategoryId = car.CategoryId,
                Price = car.Price,
                ImagePath = _baseUrl + car.ImagePath,  // Формирование полного URL для изображения
                ImageMimeType = car.ImageMimeType,
                Category = null  // Можно заполнить, если нужно, но в вашем случае это null
            };

            return ResponseData<CarDTO>.Success(carDTO);
        }

        //public async Task<ResponseData<ListModel<Car>>> GetCarListAsync(string? categoryNormalizedName,
        //                                                                            int pageNo = 1, int pageSize = 3)
        //{
        //    if (pageSize > _maxPageSize)
        //        pageSize = _maxPageSize;

        //    var query = _context.Cars
        //                             .Include(c => c.Category)
        //                             .AsQueryable();
        //    var dataList = new ListModel<Car>();

        //    query = query.Where(c => categoryNormalizedName == null || c.Category.NormalizedName.Equals(categoryNormalizedName));
        //    var count = await query.CountAsync();

        //    if (count == 0)
        //    {
        //        return ResponseData<ListModel<Car>>.Success(dataList);
        //    }

        //    int totalPages = (int)Math.Ceiling(count / (double)pageSize);

        //    if (pageNo > totalPages) // если количество товаров между запросами изменилось, их стало меньше и номер запрашиваемой страницы уже не существует
        //        return ResponseData<ListModel<Car>>.Error("No such page");

        //    dataList.Items = await query
        //                            .OrderBy(c => c.Id)
        //                            .Skip((pageNo - 1) * pageSize)
        //                            .Take(pageSize)
        //                            .ToListAsync();
        //    dataList.CurrentPage = pageNo;
        //    dataList.TotalPages = totalPages;
        //    return ResponseData<ListModel<Car>>.Success(dataList);
        //}
        public async Task<ResponseData<ListModel<CarDTO>>> GetCarListAsync(string? categoryNormalizedName, int pageNo = 1, int pageSize = 3)
        {
            if (pageSize > _maxPageSize)
                pageSize = _maxPageSize;

            var query = _context.Cars
                                .Include(c => c.Category)
                                .AsQueryable();

            var dataList = new ListModel<CarDTO>();

            query = query.Where(c => categoryNormalizedName == null || c.Category.NormalizedName.Equals(categoryNormalizedName));
            var count = await query.CountAsync();

            if (count == 0)
            {
                return ResponseData<ListModel<CarDTO>>.Success(dataList);
            }

            int totalPages = (int)Math.Ceiling(count / (double)pageSize);

            if (pageNo > totalPages)
                return ResponseData<ListModel<CarDTO>>.Error("No such page");

            var cars = await query
                             .OrderBy(c => c.Id)
                             .Skip((pageNo - 1) * pageSize)
                             .Take(pageSize)
                             .Select(c => new CarDTO
                             {
                                 Id = c.Id,
                                 Name = c.Name,
                                 Description = c.Description,
                                 CategoryId = c.CategoryId,
                                 Price = c.Price,
                                 ImagePath = _baseUrl + c.ImagePath,  // Формирование полного URL к изображению
                                 ImageMimeType = c.ImageMimeType,
                                 Category = null  
                             })
                             .ToListAsync();

            dataList.Items = cars;
            dataList.CurrentPage = pageNo;
            dataList.TotalPages = totalPages;
            return ResponseData<ListModel<CarDTO>>.Success(dataList);
        }
        public async Task<ResponseData<string>> SaveImageAsync(int id, IFormFile formFile)
        {
            var query = _context.Cars.AsQueryable();
            var car = await query.FirstOrDefaultAsync(c => c.Id.Equals(id));

            if (car is null)
            {
                return ResponseData<string>.Error("No such product");
            }


            if (formFile is null || formFile.Length == 0)
            {
                return ResponseData<string>.Error("Invalid file");
            }


            var fileExtension = Path.GetExtension(formFile.FileName);
            var allowedExtensions = new[] { ".jpg", ".jpeg", ".png", ".gif" };
            if (!allowedExtensions.Contains(fileExtension.ToLower()))
            {
                return ResponseData<string>.Error("Invalid image format");
            }
            var fileName = Path.GetFileName(formFile.FileName);
            var savePath = Path.Combine(_webHostEnvironment.WebRootPath, "images", fileName);


            using (var stream = new FileStream(savePath, FileMode.Create))
            {
                await formFile.CopyToAsync(stream);
            }

            car.ImagePath = _baseUrl + formFile.FileName;
            _context.Cars.Update(car);
            await _context.SaveChangesAsync();
            return ResponseData<string>.Success(car.ImagePath);
        }

        //public async Task<ResponseData<Car>> UpdateCarAsync(int id, Car product)
        //{
        //    var query = _context.Cars.AsQueryable();
        //    var car = await query.FirstOrDefaultAsync(c => c.Id.Equals(id));
        //    if (car is not null)
        //    {
        //        car.Name = product.Name;
        //        car.Description = product.Description;
        //        car.Price = product.Price;
        //        //car.CategoryId = product.CategoryId;
        //        await _context.SaveChangesAsync();
        //        return ResponseData<Car>.Success(car);
        //    }
        //    return ResponseData<Car>.Error("No such product", car);
        //}
        public async Task<ResponseData<Car>> UpdateCarAsync(int id, Car car)
        {
            var existingCar = await _context.Cars.FirstOrDefaultAsync(c => c.Id.Equals(id));
            if (existingCar != null)
            {
                // Обновление остальных свойств
                existingCar.Name = car.Name;
                existingCar.Description = car.Description;
                existingCar.Price = car.Price;
                existingCar.CategoryId = car.CategoryId;

                // Обновление пути к изображению, если он был предоставлен
                if (!string.IsNullOrEmpty(car.ImagePath))
                {
                    existingCar.ImagePath = car.ImagePath;
                }

                await _context.SaveChangesAsync();
                return ResponseData<Car>.Success(existingCar); // Возвращаем обновленный объект
            }

            return ResponseData<Car>.Error("No such product", car);
        }

    }
}
