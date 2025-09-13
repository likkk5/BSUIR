using Microsoft.EntityFrameworkCore;
using WEB_253502_Lishykk.Domain.Entities;

namespace WEB_253502_Lishykk.API.Data
{
    public class AppDbContext : DbContext
    {
        // Конструктор контекста, который принимает параметры конфигурации
        public AppDbContext(DbContextOptions<AppDbContext> options)
            : base(options)
        {
        }

        // Коллекции сущностей
        public DbSet<Car> Cars { get; set; } // Коллекция автомобилей
        public DbSet<Category> Categories { get; set; } // Коллекция категорий

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);

            // Дополнительная конфигурация моделей (опционально)
        }
    }
}
