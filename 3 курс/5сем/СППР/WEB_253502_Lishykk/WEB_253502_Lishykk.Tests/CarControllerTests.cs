using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using NSubstitute;
using System.Collections.Generic;
using System.Threading.Tasks;
using WEB_253502_Lishykk.UI.Controllers;
using WEB_253502_Lishykk.Domain.Entities;
using WEB_253502_Lishykk.Domain.Models;
using WEB_253502_Lishykk.UI.Services.CarService;
using WEB_253502_Lishykk.UI.Services.CategoryService;
using Xunit;

namespace WEB_253502_Lishykk.Tests
{
    public class CarControllerTests
    {
        private readonly ICarService _carService = Substitute.For<ICarService>();
        private readonly ICategoryService _categoryService = Substitute.For<ICategoryService>();
        private readonly CarController _controller;
        private readonly ITempDataDictionary _tempData;

        public CarControllerTests()
        {
            // Мокируем TempData
            _tempData = Substitute.For<ITempDataDictionary>();

            _controller = new CarController(_carService, _categoryService)
            {
                TempData = _tempData // Устанавливаем TempData в контроллере
            };

            // Настройка HttpContext и HttpRequest для тестов
            var httpContext = Substitute.For<HttpContext>();
            var httpRequest = Substitute.For<HttpRequest>();
            httpContext.Request.Returns(httpRequest);
            _controller.ControllerContext = new ControllerContext
            {
                HttpContext = httpContext
            };
        }

        [Fact]
        public async Task Index_Returns404_WhenCategoryListFails()
        {
            // Arrange: имитируем неуспешный ответ от _categoryService
            _categoryService.GetCategoryListAsync().Returns(Task.FromResult(new ResponseData<List<Category>>
            {
                Successfull = false,
                ErrorMessage = "Failed to load categories"
            }));

            // Act: вызов метода Index
            var result = await _controller.Index(null);

            // Assert: проверяем, что возвращается NotFoundResult
            var notFoundResult = Assert.IsType<NotFoundObjectResult>(result);
            Assert.Equal("Failed to load categories", notFoundResult.Value);
        }

        [Fact]
        public async Task Index_Returns404_WhenCarListFails()
        {
            // Arrange: успешный ответ для категорий, но неуспешный для автомобилей
            _categoryService.GetCategoryListAsync().Returns(Task.FromResult(new ResponseData<List<Category>>
            {
                Successfull = true,
                Data = new List<Category> { new Category { Id = 1, Name = "SUV" } }
            }));

            _carService.GetCarListAsync(Arg.Any<string>(), Arg.Any<int>()).Returns(Task.FromResult(new ResponseData<ListModel<Car>>
            {
                Successfull = false,
                ErrorMessage = "Failed to load cars"
            }));

            // Act: вызов метода Index
            var result = await _controller.Index(null);

            // Assert: проверяем, что возвращается NotFoundResult для списка автомобилей
            var notFoundResult = Assert.IsType<NotFoundObjectResult>(result);
            Assert.Equal("Failed to load cars", notFoundResult.Value);
        }

        [Fact]
        public async Task Index_PassesCategoriesToViewData_OnSuccess()
        {
            // Arrange: успешное получение списков категорий и автомобилей
            var categories = new List<Category> { new Category { Id = 1, Name = "SUV" } };
            _categoryService.GetCategoryListAsync().Returns(Task.FromResult(new ResponseData<List<Category>>
            {
                Successfull = true,
                Data = categories
            }));

            var carListModel = new ListModel<Car>
            {
                Items = new List<Car> { new Car { Id = 1, Name = "Car1" } },
                CurrentPage = 1,
                TotalPages = 1
            };

            _carService.GetCarListAsync(Arg.Any<string>(), Arg.Any<int>()).Returns(Task.FromResult(new ResponseData<ListModel<Car>>
            {
                Successfull = true,
                Data = carListModel
            }));

            // Act: вызов метода Index
            var result = await _controller.Index(null);

            // Assert: проверяем, что категории переданы в ViewData
            var viewResult = Assert.IsType<ViewResult>(result);
            Assert.Equal(categories, viewResult.ViewData["Categories"]);
            Assert.Equal("All", viewResult.ViewData["currentCategory"]);
        }

        [Fact]
        public async Task Index_PassesModelToView_OnSuccess()
        {
            // Arrange: успешное получение данных
            var categories = new List<Category> { new Category { Id = 1, Name = "SUV" } };
            _categoryService.GetCategoryListAsync().Returns(Task.FromResult(new ResponseData<List<Category>>
            {
                Successfull = true,
                Data = categories
            }));

            // Создаем модель из пространства имён UI.Models
            var carListModel = new WEB_253502_Lishykk.Domain.Models.ListModel<Car>
            {
                Items = new List<Car> { new Car { Id = 1, Name = "Car1" } },
                CurrentPage = 1,
                TotalPages = 3
            };

            // Mock для CarService с типом из UI.Models
            _carService.GetCarListAsync(Arg.Any<string>(), Arg.Any<int>()).Returns(Task.FromResult(new ResponseData<WEB_253502_Lishykk.Domain.Models.ListModel<Car>>
            {
                Successfull = true,
                Data = carListModel
            }));

            // Act: вызов метода Index
            var result = await _controller.Index(null);

            // Assert: проверяем, что модель передана в представление
            var viewResult = Assert.IsType<ViewResult>(result);
            var model = Assert.IsType<WEB_253502_Lishykk.UI.Models.ListModel<Car>>(viewResult.Model);
            Assert.Equal(carListModel.Items, model.Items);
            Assert.Equal(carListModel.CurrentPage, model.CurrentPage);
            Assert.Equal(carListModel.TotalPages, model.TotalPages);
        }

        [Fact]
        public async Task Index_SetsCorrectCategory_WhenCategoryProvided()
        {
            // Arrange: успешное получение данных с указанием категории
            var categories = new List<Category> { new Category { Id = 1, Name = "SUV" } };
            _categoryService.GetCategoryListAsync().Returns(Task.FromResult(new ResponseData<List<Category>>
            {
                Successfull = true,
                Data = categories
            }));

            var carListModel = new ListModel<Car>
            {
                Items = new List<Car> { new Car { Id = 1, Name = "Car1" } },
                CurrentPage = 1,
                TotalPages = 1
            };

            _carService.GetCarListAsync(Arg.Any<string>(), Arg.Any<int>()).Returns(Task.FromResult(new ResponseData<ListModel<Car>>
            {
                Successfull = true,
                Data = carListModel
            }));

            // Act: вызов метода Index с категорией "SUV"
            var result = await _controller.Index("SUV");

            // Assert: проверяем, что передана правильная категория в ViewData
            var viewResult = Assert.IsType<ViewResult>(result);
            Assert.Equal("SUV", viewResult.ViewData["currentCategory"]);
        }
    }
}
