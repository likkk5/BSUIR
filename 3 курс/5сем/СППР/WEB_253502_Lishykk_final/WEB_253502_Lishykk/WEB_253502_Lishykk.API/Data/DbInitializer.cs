using Microsoft.EntityFrameworkCore;
using WEB_253502_Lishykk.Domain.Entities;

namespace WEB_253502_Lishykk.API.Data
{
    public static class DbInitializer
    {
        public static async Task SeedData(WebApplication app)
        {
            // Создаем скоуп для получения сервиса контекста БД
            using var scope = app.Services.CreateScope();
            var context = scope.ServiceProvider.GetRequiredService<AppDbContext>();

            // Выполнение миграций
            await context.Database.MigrateAsync();
            context.Cars.RemoveRange(context.Cars);
            context.Categories.RemoveRange(context.Categories);
            await context.SaveChangesAsync();
            // Проверяем, если уже есть данные, ничего не делаем
            //if (!context.Cars.Any() && !context.Categories.Any())
            //{
            // Получение адреса приложения из конфигурации
            var appUrl = app.Configuration["AppUrl"];

            // Добавление категорий
            //    var categories = new List<Category>
            //{
            //    new Category { Name = "SUV", NormalizedName = "suv" },
            //    new Category { Name = "Sedan", NormalizedName = "sedan" },
            //    new Category { Name = "Hatchback", NormalizedName = "hatchback" },
            //    new Category { Name = "Coupe", NormalizedName = "coupe" },
            //    new Category { Name = "Truck", NormalizedName = "truck" },
            //    new Category { Name = "Convertible", NormalizedName = "convertible" },
            //    new Category { Name = "Electric", NormalizedName = "electric" }
            //};
            var categories = new List<Category>
                {
                    new Category { Name = "Антибиотики", NormalizedName = "antibiotics" },
                    new Category { Name = "Обезболивающие", NormalizedName = "painkillers" },
                    new Category { Name = "Противовирусные", NormalizedName = "antivirals" },
                    new Category { Name = "Витамины", NormalizedName = "vitamins" },
                    new Category { Name = "Антисептики", NormalizedName = "antiseptics" },
                    new Category { Name = "Противоаллергические", NormalizedName = "antiallergic" },
                    new Category { Name = "Гормональные", NormalizedName = "hormonal" }
                };

            context.Categories.AddRange(categories);
            await context.SaveChangesAsync();

            //// Получаем созданные категории для сопоставления с автомобилями
            //var suvCategory = categories.First(c => c.NormalizedName == "suv");
            //var sedanCategory = categories.First(c => c.NormalizedName == "sedan");
            //var hatchbackCategory = categories.First(c => c.NormalizedName == "hatchback");
            //var coupeCategory = categories.First(c => c.NormalizedName == "coupe");
            //var truckCategory = categories.First(c => c.NormalizedName == "truck");
            //var convertibleCategory = categories.First(c => c.NormalizedName == "convertible");
            //var electricCategory = categories.First(c => c.NormalizedName == "electric");
            //// Получение ID созданных категорий для использования в автомобилях
            //var suvCategoryId = categories.First(c => c.NormalizedName == "suv").Id;
            //var sedanCategoryId = categories.First(c => c.NormalizedName == "sedan").Id;
            //var hatchbackCategoryId = categories.First(c => c.NormalizedName == "hatchback").Id;
            //var coupeCategoryId = categories.First(c => c.NormalizedName == "coupe").Id;
            //var truckCategoryId = categories.First(c => c.NormalizedName == "truck").Id;
            //var convertibleCategoryId = categories.First(c => c.NormalizedName == "convertible").Id;
            //var electricCategoryId = categories.First(c => c.NormalizedName == "electric").Id;

            //    // Добавление автомобилей
            //    var cars = new List<Car>
            //{
            //    new Car { Name = "Toyota RAV4", Description = "Compact SUV", Price = 30000,
            //              ImagePath = $"{appUrl}/Images/toyota_rav4.jpg", ImageMimeType = "image/jpeg", Category = suvCategory },
            //    new Car { Name = "Honda Accord", Description = "Mid-size sedan", Price = 25000,
            //              ImagePath = $"{appUrl}/Images/honda_accord.jpg", ImageMimeType = "image/jpeg", Category = sedanCategory },
            //    new Car { Name = "Ford Fiesta", Description = "Compact hatchback", Price = 18000,
            //              ImagePath = $"{appUrl}/Images/ford_fiesta.jpg", ImageMimeType = "image/jpeg", Category = hatchbackCategory },
            //    new Car { Name = "BMW 4 Series", Description = "Luxury coupe", Price = 45000,
            //              ImagePath = $"{appUrl}/Images/bmw_4_series.jpg", ImageMimeType = "image/jpeg", Category = coupeCategory },
            //    new Car { Name = "Ford F-150", Description = "Full-size pickup truck", Price = 40000,
            //              ImagePath = $"{appUrl}/Images/ford_f150.jpg", ImageMimeType = "image/jpeg", Category = truckCategory },
            //    new Car { Name = "Mazda MX-5 Miata", Description = "Sporty convertible", Price = 35000,
            //              ImagePath = $"{appUrl}/Images/mazda_mx5.jpg", ImageMimeType = "image/jpeg", Category = convertibleCategory },
            //    new Car { Name = "Tesla Model S", Description = "Luxury electric sedan", Price = 80000,
            //              ImagePath = $"{appUrl}/Images/tesla_model_s.jpg", ImageMimeType = "image/jpeg", Category = electricCategory },
            //    new Car { Name = "Chevrolet Tahoe", Description = "Full-size SUV", Price = 60000,
            //              ImagePath = $"{appUrl}/Images/chevrolet_tahoe.jpg", ImageMimeType = "image/jpeg", Category = suvCategory },
            //    new Car { Name = "Volkswagen Golf", Description = "Compact hatchback", Price = 22000,
            //              ImagePath = $"{appUrl}/Images/vw_golf.jpg", ImageMimeType = "image/jpeg", Category = hatchbackCategory }
            //};


            // Добавление автомобилей с использованием CategoryId (верно)
            //var cars = new List<Car>
            //{
            //    new Car { Name = "Toyota RAV4", Description = "Compact SUV", Price = 30000,
            //              ImagePath = $"{appUrl}/Images/toyota_rav4.jpg", ImageMimeType = "image/jpeg", Category = suvCategory, CategoryId = suvCategoryId },
            //    new Car { Name = "Honda Accord", Description = "Mid-size sedan", Price = 25000,
            //              ImagePath = $"{appUrl}/Images/honda_accord.jpg", ImageMimeType = "image/jpeg", Category = sedanCategory, CategoryId = sedanCategoryId },
            //    new Car { Name = "Ford Fiesta", Description = "Compact hatchback", Price = 18000,
            //              ImagePath = $"{appUrl}/Images/ford_fiesta.jpg", ImageMimeType = "image/jpeg", Category = hatchbackCategory, CategoryId = hatchbackCategoryId },
            //    new Car { Name = "BMW 4 Series", Description = "Luxury coupe", Price = 45000,
            //              ImagePath = $"{appUrl}/Images/bmw_4_series.jpg", ImageMimeType = "image/jpeg", Category = coupeCategory, CategoryId = coupeCategoryId },
            //    new Car { Name = "Ford F-150", Description = "Full-size pickup truck", Price = 40000,
            //              ImagePath = $"{appUrl}/Images/ford_f150.jpg", ImageMimeType = "image/jpeg", Category = truckCategory, CategoryId = truckCategoryId },
            //    new Car { Name = "Mazda MX-5 Miata", Description = "Sporty convertible", Price = 35000,
            //              ImagePath = $"{appUrl}/Images/mazda_mx5.jpg", ImageMimeType = "image/jpeg", Category = convertibleCategory, CategoryId = convertibleCategoryId },
            //    new Car { Name = "Tesla Model S", Description = "Luxury electric sedan", Price = 80000,
            //              ImagePath = $"{appUrl}/Images/tesla_model_s.jpg", ImageMimeType = "image/jpeg", Category = electricCategory, CategoryId = electricCategoryId },
            //    new Car { Name = "Chevrolet Tahoe", Description = "Full-size SUV", Price = 60000,
            //              ImagePath = $"{appUrl}/Images/chevrolet_tahoe.jpg", ImageMimeType = "image/jpeg", Category = suvCategory, CategoryId = suvCategoryId },
            //    new Car { Name = "Volkswagen Golf", Description = "Compact hatchback", Price = 22000,
            //              ImagePath = $"{appUrl}/Images/vw_golf.jpg", ImageMimeType = "image/jpeg", Category = hatchbackCategory, CategoryId = hatchbackCategoryId }
            //};

            // Получаем созданные категории для сопоставления с медикаментами
            var antibioticsCategory = categories.First(c => c.NormalizedName == "antibiotics");
            var painkillersCategory = categories.First(c => c.NormalizedName == "painkillers");
            var antiviralsCategory = categories.First(c => c.NormalizedName == "antivirals");
            var vitaminsCategory = categories.First(c => c.NormalizedName == "vitamins");
            var antisepticsCategory = categories.First(c => c.NormalizedName == "antiseptics");
            var antiallergicCategory = categories.First(c => c.NormalizedName == "antiallergic");
            var hormonalCategory = categories.First(c => c.NormalizedName == "hormonal");

            // Получение ID созданных категорий для использования в медикаментах
            var antibioticsCategoryId = antibioticsCategory.Id;
            var painkillersCategoryId = painkillersCategory.Id;
            var antiviralsCategoryId = antiviralsCategory.Id;
            var vitaminsCategoryId = vitaminsCategory.Id;
            var antisepticsCategoryId = antisepticsCategory.Id;
            var antiallergicCategoryId = antiallergicCategory.Id;
            var hormonalCategoryId = hormonalCategory.Id;

            //медикаменты
            var cars = new List<Car>
            {
                // Антибиотики
                new Car
                {
                    Name = "Амоксициллин",
                    Description = "Антибиотик широкого спектра действия",
                    Price = 12,
                    ImagePath = $"{appUrl}/Images/amoxicillin.jpg",
                    ImageMimeType = "image/jpeg",
                    Category = antibioticsCategory,
                    CategoryId = antibioticsCategoryId
                },
                new Car
                {
                    Name = "Азитромицин",
                    Description = "Антибиотик-азалид для лечения респираторных инфекций",
                    Price = 15,
                    ImagePath = $"{appUrl}/Images/azithromycin.jpg",
                    ImageMimeType = "image/jpeg",
                    Category = antibioticsCategory,
                    CategoryId = antibioticsCategoryId
                },
                new Car
                {
                    Name = "Цефтриаксон",
                    Description = "Цефалоспориновый антибиотик III поколения",
                    Price = 20,
                    ImagePath = $"{appUrl}/Images/ceftriaxone.jpg",
                    ImageMimeType = "image/jpeg",
                    Category = antibioticsCategory,
                    CategoryId = antibioticsCategoryId
                },

                // Обезболивающие 
                new Car
                {
                    Name = "Парацетамол",
                    Description = "Обезболивающее и жаропонижающее средство",
                    Price = 5,
                    ImagePath = $"{appUrl}/Images/paracetamol.jpg",
                    ImageMimeType = "image/jpeg",
                    Category = painkillersCategory,
                    CategoryId = painkillersCategoryId
                },
                new Car
                {
                    Name = "Ибупрофен",
                    Description = "Нестероидное противовоспалительное средство",
                    Price = 8,
                    ImagePath = $"{appUrl}/Images/ibuprofen.jpg",
                    ImageMimeType = "image/jpeg",
                    Category = painkillersCategory,
                    CategoryId = painkillersCategoryId
                },
                new Car
                {
                    Name = "Кеторолак",
                    Description = "Сильное обезболивающее средство",
                    Price = 10,
                    ImagePath = $"{appUrl}/Images/ketorolac.jpg",
                    ImageMimeType = "image/jpeg",
                    Category = painkillersCategory,
                    CategoryId = painkillersCategoryId
                },

                // Противовирусные 
                new Car
                {
                    Name = "Арбидол",
                    Description = "Противовирусное средство",
                    Price = 10,
                    ImagePath = $"{appUrl}/Images/arbidol.jpg",
                    ImageMimeType = "image/jpeg",
                    Category = antiviralsCategory,
                    CategoryId = antiviralsCategoryId
                },
                new Car
                {
                    Name = "Ингавирин",
                    Description = "Противовирусный препарат для лечения гриппа",
                    Price = 12,
                    ImagePath = $"{appUrl}/Images/ingavirin.jpg",
                    ImageMimeType = "image/jpeg",
                    Category = antiviralsCategory,
                    CategoryId = antiviralsCategoryId
                },
                new Car
                {
                    Name = "Осельтамивир",
                    Description = "Противовирусное средство (Тамифлю)",
                    Price = 25,
                    ImagePath = $"{appUrl}/Images/oseltamivir.jpg",
                    ImageMimeType = "image/jpeg",
                    Category = antiviralsCategory,
                    CategoryId = antiviralsCategoryId
                },

                // Витамины 
                new Car
                {
                    Name = "Витамин C",
                    Description = "Поддержка иммунитета",
                    Price = 3,
                    ImagePath = $"{appUrl}/Images/vitamin_c.jpg",
                    ImageMimeType = "image/jpeg",
                    Category = vitaminsCategory,
                    CategoryId = vitaminsCategoryId
                },
                new Car
                {
                    Name = "Витамин D",
                    Description = "Для здоровья костей и иммунитета",
                    Price = 4,
                    ImagePath = $"{appUrl}/Images/vitamin_d.jpg",
                    ImageMimeType = "image/jpeg",
                    Category = vitaminsCategory,
                    CategoryId = vitaminsCategoryId
                },
                new Car
                {
                    Name = "Компливит",
                    Description = "Поливитаминный комплекс",
                    Price = 7,
                    ImagePath = $"{appUrl}/Images/complivit.jpg",
                    ImageMimeType = "image/jpeg",
                    Category = vitaminsCategory,
                    CategoryId = vitaminsCategoryId
                },

                // Антисептики 
                new Car
                {
                    Name = "Хлоргексидин",
                    Description = "Антисептик для наружного применения",
                    Price = 2,
                    ImagePath = $"{appUrl}/Images/chlorhexidine.jpg",
                    ImageMimeType = "image/jpeg",
                    Category = antisepticsCategory,
                    CategoryId = antisepticsCategoryId
                },
                new Car
                {
                    Name = "Мирамистин",
                    Description = "Антисептик широкого спектра",
                    Price = 5,
                    ImagePath = $"{appUrl}/Images/miramistin.jpg",
                    ImageMimeType = "image/jpeg",
                    Category = antisepticsCategory,
                    CategoryId = antisepticsCategoryId
                },
                new Car
                {
                    Name = "Перекись водорода",
                    Description = "Для обработки ран и царапин",
                    Price = 1,
                    ImagePath = $"{appUrl}/Images/hydrogen_peroxide.jpg",
                    ImageMimeType = "image/jpeg",
                    Category = antisepticsCategory,
                    CategoryId = antisepticsCategoryId
                },

                // Противоаллергические 
                new Car
                {
                    Name = "Цетрин",
                    Description = "Противоаллергическое средство",
                    Price = 7,
                    ImagePath = $"{appUrl}/Images/cetrine.jpg",
                    ImageMimeType = "image/jpeg",
                    Category = antiallergicCategory,
                    CategoryId = antiallergicCategoryId
                },
                new Car
                {
                    Name = "Лоратадин",
                    Description = "Антигистаминный препарат",
                    Price = 5,
                    ImagePath = $"{appUrl}/Images/loratadine.jpg",
                    ImageMimeType = "image/jpeg",
                    Category = antiallergicCategory,
                    CategoryId = antiallergicCategoryId
                },
                new Car
                {
                    Name = "Супрастин",
                    Description = "Блокатор гистаминовых рецепторов",
                    Price = 6,
                    ImagePath = $"{appUrl}/Images/suprastin.jpg",
                    ImageMimeType = "image/jpeg",
                    Category = antiallergicCategory,
                    CategoryId = antiallergicCategoryId
                },

                // Гормональные 
                new Car
                {
                    Name = "Дексаметазон",
                    Description = "Гормональное противовоспалительное средство",
                    Price = 6,
                    ImagePath = $"{appUrl}/Images/dexamethasone.jpg",
                    ImageMimeType = "image/jpeg",
                    Category = hormonalCategory,
                    CategoryId = hormonalCategoryId
                },
                new Car
                {
                    Name = "Преднизолон",
                    Description = "Кортикостероидный препарат",
                    Price = 8,
                    ImagePath = $"{appUrl}/Images/prednisolone.jpg",
                    ImageMimeType = "image/jpeg",
                    Category = hormonalCategory,
                    CategoryId = hormonalCategoryId
                },
                new Car
                {
                    Name = "Гидрокортизон",
                    Description = "Кортикостероид для наружного применения",
                    Price = 5,
                    ImagePath = $"{appUrl}/Images/hydrocortisone.jpg",
                    ImageMimeType = "image/jpeg",
                    Category = hormonalCategory,
                    CategoryId = hormonalCategoryId
                }
            };

            context.Cars.AddRange(cars);
            await context.SaveChangesAsync();
            //}
        }
    }
}
