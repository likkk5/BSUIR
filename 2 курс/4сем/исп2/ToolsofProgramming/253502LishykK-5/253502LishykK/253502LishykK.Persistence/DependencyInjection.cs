using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _253502LishykK.Persistence.Data;
using _253502LishykK.Persistence.Repository;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;

namespace _253502LishykK.Persistence
{
    public static class DependencyInjection
    {
        public static IServiceCollection AddPersistence(this IServiceCollection services)
        {
            services.AddSingleton<IUnitOfWork, EfUnitOfWork>();
            services.AddScoped<IRepository<Participant>, EfRepository<Participant>>();
            services.AddScoped<IRepository<Nomination>, EfRepository<Nomination>>();

            // Замените реальными репозиториями, когда перейдете к использованию реальной базы данных
            //services.AddSingleton<IUnitOfWork, FakeUnitOfWork>();
            //services.AddSingleton<IUnitOfWork, EfUnitOfWork>();
            //services.AddScoped<IRepository<Participant>, FakeParticipantRepository>();
            //services.AddScoped<IRepository<Nomination>, FakeNominationRepository>();

            return services;
        }

        public static IServiceCollection AddPersistence(this IServiceCollection services, DbContextOptions options)
        {
            services.AddPersistence()
                    .AddSingleton(new AppDbContext((DbContextOptions<AppDbContext>)options));
            return services;
        }

    }
}
