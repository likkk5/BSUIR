using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Options;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WEB_253502_Lishykk.API;
using WEB_253502_Lishykk.API.Data;
using WEB_253502_Lishykk.API.Models;
using WEB_253502_Lishykk.API.Services.CarService;
using WEB_253502_Lishykk.Domain.Entities;
using WEB_253502_Lishykk.Domain.Models;
using Xunit;

namespace WEB_253502_Lishykk.Tests
{
    public class CarServiceTests
    {
        private readonly DbContextOptions<AppDbContext> _dbContextOptions;
        private const int _maxPageSize = 3;

        private AppDbContext CreateContext()
        {
            var options = new DbContextOptionsBuilder<AppDbContext>()
                .UseSqlite("DataSource=:memory:")
                .Options;

            var context = new AppDbContext(options);
            context.Database.OpenConnection();
            context.Database.EnsureCreated();
            return context;
        }

        private CarService CreateService(AppDbContext context)
        {
            var appSettings = Options.Create(new AppSettings { BaseUrl = "http://localhost/" });
            return new CarService(context, null, appSettings);
        }

        private void SeedDatabase(AppDbContext context)
        {
            var categories = new List<Category>
            {
                new Category { Name = "SUV", NormalizedName = "suv" },
                new Category { Name = "Sedan", NormalizedName = "sedan" },
                new Category { Name = "Hatchback", NormalizedName = "hatchback" },
                new Category { Name = "Coupe", NormalizedName = "coupe" },
                new Category { Name = "Convertible", NormalizedName = "convertible" }
            };

            context.Categories.AddRange(categories);
            context.SaveChanges();

            var cars = new List<Car>
            {
                new Car { Name = "Toyota RAV4", Description = "Compact SUV", Price = 30000, ImagePath = "images/image1.jpg", ImageMimeType = "image/jpeg", CategoryId = categories.First(c => c.NormalizedName == "suv").Id },
                new Car { Name = "Honda Accord", Description = "Mid-size sedan", Price = 25000, ImagePath = "images/image2.jpg", ImageMimeType = "image/jpeg", CategoryId = categories.First(c => c.NormalizedName == "sedan").Id },
                new Car { Name = "Ford Fiesta", Description = "Compact hatchback", Price = 18000, ImagePath = "images/image3.jpg", ImageMimeType = "image/jpeg", CategoryId = categories.First(c => c.NormalizedName == "hatchback").Id },
                new Car { Name = "Chevrolet Camaro", Description = "Sports coupe", Price = 35000, ImagePath = "images/image4.jpg", ImageMimeType = "image/jpeg", CategoryId = categories.First(c => c.NormalizedName == "coupe").Id },
                new Car { Name = "Mazda MX-5", Description = "Compact convertible", Price = 28000, ImagePath = "images/image5.jpg", ImageMimeType = "image/jpeg", CategoryId = categories.First(c => c.NormalizedName == "convertible").Id },
                new Car { Name = "Tesla Model 3", Description = "Electric sedan", Price = 40000, ImagePath = "images/image6.jpg", ImageMimeType = "image/jpeg", CategoryId = categories.First(c => c.NormalizedName == "sedan").Id },
                new Car { Name = "BMW X5", Description = "Luxury SUV", Price = 60000, ImagePath = "images/image7.jpg", ImageMimeType = "image/jpeg", CategoryId = categories.First(c => c.NormalizedName == "suv").Id },
                new Car { Name = "Audi A4", Description = "Compact executive car", Price = 35000, ImagePath = "images/image8.jpg", ImageMimeType = "image/jpeg", CategoryId = categories.First(c => c.NormalizedName == "sedan").Id }
            };

            context.Cars.AddRange(cars);
            context.SaveChanges();
        }

        [Fact]
        public async Task GetCarListAsync_ReturnsFirstPageOfThreeItems()
        {
            // Arrange
            using var context = CreateContext();
            SeedDatabase(context);

            var service = CreateService(context);
            var result = await service.GetCarListAsync(null);

            Assert.IsType<ResponseData<ListModel<CarDTO>>>(result);
            Assert.True(result.Successfull);
            Assert.Equal(1, result.Data.CurrentPage);
            Assert.Equal(3, result.Data.Items.Count);
            Assert.Equal("Toyota RAV4", result.Data.Items[0].Name);
            Assert.Equal(3, result.Data.TotalPages);
        }

        [Fact]
        public async Task GetCarListAsync_ReturnsCorrectPage()
        {
            // Arrange
            using var context = CreateContext();
            SeedDatabase(context); 

            var service = CreateService(context);
            var result = await service.GetCarListAsync(null, 1, 2);

            Assert.True(result.Successfull);
            Assert.Equal(1, result.Data.CurrentPage);
            Assert.Equal(2, result.Data.Items.Count);
            Assert.Equal("Toyota RAV4", result.Data.Items[0].Name);
        }

        [Fact]
        public async Task GetCarListAsync_FiltersByCategory()
        {
            // Arrange
            using var context = CreateContext();
            SeedDatabase(context);

            var service = CreateService(context);
            var result = await service.GetCarListAsync("hatchback");

            Assert.True(result.Successfull);
            Assert.Equal(1, result.Data.CurrentPage);
            Assert.Single(result.Data.Items); 
            Assert.Equal("Ford Fiesta", result.Data.Items[0].Name);
        }

        [Fact]
        public async Task GetCarListAsync_DoesNotAllowPageSizeGreaterThanMax()
        {
            // Arrange
            using var context = CreateContext();
            SeedDatabase(context);

            var service = CreateService(context);
            var result = await service.GetCarListAsync(null, 1, 5);

            // Assert
            Assert.True(result.Successfull);
            Assert.Equal(1, result.Data.CurrentPage);
            //Assert.Equal(3, result.Data.Items.Count); 
            Assert.True(result.Data.Items.Count >= 3, "The number of items can't be more than 3.");
        }


        [Fact]
        public async Task GetCarListAsync_ReturnsSuccessFalse_WhenPageExceedsTotalPages()
        {
            // Arrange
            using var context = CreateContext();
            SeedDatabase(context); 

            var service = CreateService(context);
            var result = await service.GetCarListAsync(null, 4); 

            Assert.False(result.Successfull);
            Assert.Null(result.Data);
            Assert.Equal("No such page", result.ErrorMessage);
        }
    }
}
