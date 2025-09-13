using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;

namespace _253502LishykK.Persistence.Data
{
    public class AppDbContext : DbContext
    {
        public AppDbContext(DbContextOptions<AppDbContext> options) : base(options)
        {
            Database.EnsureCreated();
        }

        // Определите DbSet для ваших сущностей
        public DbSet<Nomination> Nominations { get; set; }
        public DbSet<Participant> Participants { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            // Настройте связи и владение объектами, если необходимо
            modelBuilder.Entity<Nomination>()
                .HasMany(n => n.Participants)
                .WithOne(p => p.Nomination)
                .HasForeignKey(p => p.NominationId);

            // Добавьте другие конфигурации по мере необходимости
        }
    }
}
