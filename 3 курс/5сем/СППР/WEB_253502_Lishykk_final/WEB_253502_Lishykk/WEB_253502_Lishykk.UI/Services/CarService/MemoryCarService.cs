//using System.Collections.Generic;
//using System.Threading.Tasks;
//using Microsoft.AspNetCore.Http;
//using WEB_253502_Lishykk.UI.Domain.Entities;
//using WEB_253502_Lishykk.UI.Domain.Models;
//using WEB_253502_Lishykk.UI.Services.CategoryService;

//namespace WEB_253502_Lishykk.UI.Services.CarService
//{
//    public class MemoryCarService : ICarService
//    {
//        private List<Car> _cars;
//        private List<Category> _categories;
//        private readonly int _itemsPerPage;
//        public MemoryCarService(ICategoryService categoryService, IConfiguration config)
//        {
//            _categories = categoryService.GetCategoryListAsync().Result.Data;
//            _itemsPerPage = int.Parse(config["ItemsPerPage"]); // Читаем количество элементов на странице из конфигурации
//            SetupData();
//        }

//        private void SetupData()
//        {
//            _cars = new List<Car>
//            {
//                new Car { Id = 1, Name = "Toyota RAV4", Description = "Compact SUV", Price = 30000,
//                          ImagePath = "Images/toyota_rav4.jpg", ImageMimeType = "image/jpeg",
//                          Category = _categories.Find(c => c.NormalizedName.Equals("suv")) },

//                new Car { Id = 2, Name = "Honda Accord", Description = "Mid-size sedan", Price = 25000,
//                          ImagePath = "Images/honda_accord.jpg", ImageMimeType = "image/jpeg",
//                          Category = _categories.Find(c => c.NormalizedName.Equals("sedan")) },

//                new Car { Id = 3, Name = "Ford Fiesta", Description = "Compact hatchback", Price = 18000,
//                          ImagePath = "Images/ford_fiesta.jpg", ImageMimeType = "image/jpeg",
//                          Category = _categories.Find(c => c.NormalizedName.Equals("hatchback")) },

//                new Car { Id = 4, Name = "BMW 4 Series", Description = "Luxury coupe", Price = 45000,
//                          ImagePath = "Images/bmw_4_series.jpg", ImageMimeType = "image/jpeg",
//                          Category = _categories.Find(c => c.NormalizedName.Equals("coupe")) },

//                new Car { Id = 5, Name = "Ford F-150", Description = "Full-size pickup truck", Price = 40000,
//                          ImagePath = "Images/ford_f150.jpg", ImageMimeType = "image/jpeg",
//                          Category = _categories.Find(c => c.NormalizedName.Equals("truck")) },

//                new Car { Id = 6, Name = "Mazda MX-5 Miata", Description = "Sporty convertible", Price = 35000,
//                          ImagePath = "Images/mazda_mx5.jpg", ImageMimeType = "image/jpeg",
//                          Category = _categories.Find(c => c.NormalizedName.Equals("convertible")) },

//                new Car { Id = 7, Name = "Tesla Model S", Description = "Luxury electric sedan", Price = 80000,
//                  ImagePath = "Images/tesla_model_s.jpg", ImageMimeType = "image/jpeg",
//                  Category = _categories.Find(c => c.NormalizedName.Equals("sedan")) },

//                new Car { Id = 8, Name = "Chevrolet Tahoe", Description = "Full-size SUV", Price = 60000,
//                          ImagePath = "Images/chevrolet_tahoe.jpg", ImageMimeType = "image/jpeg",
//                          Category = _categories.Find(c => c.NormalizedName.Equals("suv")) },

//                new Car { Id = 9, Name = "Volkswagen Golf", Description = "Compact hatchback", Price = 22000,
//                          ImagePath = "Images/vw_golf.jpg", ImageMimeType = "image/jpeg",
//                          Category = _categories.Find(c => c.NormalizedName.Equals("hatchback")) }
//            };
//        }

//        public Task<ResponseData<ListModel<Car>>> GetCarListAsync(string? categoryNormalizedName, int pageNo = 1)
//        {
//            var filteredCars = _cars
//                .Where(car => string.IsNullOrEmpty(categoryNormalizedName) || car.Category?.NormalizedName == categoryNormalizedName)
//                .ToList();

//            int totalPages = (int)Math.Ceiling(filteredCars.Count / (double)_itemsPerPage);

//            var items = filteredCars
//                .Skip((pageNo - 1) * _itemsPerPage)  // Пропустить элементы для предыдущих страниц
//                .Take(_itemsPerPage)                // Взять нужное количество элементов для текущей страницы
//                .ToList();

//            var result = new ListModel<Car>
//            {
//                Items = items,
//                CurrentPage = pageNo,
//                TotalPages = totalPages
//            };

//            return Task.FromResult(ResponseData<ListModel<Car>>.Success(result));
//        }

//        public Task<ResponseData<Car>> GetCarByIdAsync(int id)
//        {
//            var car = _cars.Find(c => c.Id == id);
//            return Task.FromResult(ResponseData<Car>.Success(car));
//        }

//        public Task<ResponseData<Car>> UpdateCarAsync(int id, Car car, IFormFile? formFile)
//        {
//            var existingCar = _cars.Find(c => c.Id == id);
//            if (existingCar != null)
//            {
//                existingCar.Name = car.Name;
//                existingCar.Description = car.Description;
//                existingCar.Price = car.Price;

//                if (formFile != null)
//                {
//                    // Обновление изображения
//                    existingCar.ImagePath = $"Images/{formFile.FileName}";
//                    existingCar.ImageMimeType = formFile.ContentType;
//                }
//            }

//            return (Task<ResponseData<Car>>)Task.CompletedTask;
//        }

//        public Task<ResponseData<string>> DeleteCarAsync(int id)
//        {
//            _cars.RemoveAll(c => c.Id == id);
//            return (Task<ResponseData<string>>)Task.CompletedTask;
//        }

//        public Task<ResponseData<Car>> CreateCarAsync(Car car, IFormFile? formFile)
//        {
//            car.Id = _cars.Max(c => c.Id) + 1;
//            if (formFile != null)
//            {
//                // Добавление нового изображения
//                car.ImagePath = $"Images/{formFile.FileName}";
//                car.ImageMimeType = formFile.ContentType;
//            }
//            _cars.Add(car);

//            return Task.FromResult(ResponseData<Car>.Success(car));
//        }
//    }
//}
