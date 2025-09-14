using Bahdanau_153502.Domain.Entities;
using Microsoft.EntityFrameworkCore;

namespace Bahdanau_153502.Persistence.Data
{
    public class AppDbContext : DbContext
    {
        DbSet<TouristRoute> TouristRoutes { get; }
        DbSet<Landmark> Landmarks { get; }

        public AppDbContext(DbContextOptions<AppDbContext> options) : base(options)
        {
            Database.EnsureCreated();
        }
    }
}
