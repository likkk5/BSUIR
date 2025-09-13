using System.Reflection;
using _253502LishykK.Application;
using _253502LishykK.Persistence;
using _253502LishykK.Persistence.Data;
using _253502LishykK.UI.Pages;
using _253502LishykK.UI.ViewModels;
using CommunityToolkit.Maui;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Logging;

namespace _253502LishykK.UI
{
    public static class MauiProgram
    {

        public static MauiApp CreateMauiApp()
        {
            string settingsStream = "_253502LishykK.UI.appsettings.json";

            var builder = MauiApp.CreateBuilder();
            builder
                .UseMauiApp<App>()
                .UseMauiCommunityToolkit()
                .ConfigureFonts(fonts =>
                {
                    fonts.AddFont("OpenSans-Regular.ttf", "OpenSansRegular");
                    fonts.AddFont("OpenSans-Semibold.ttf", "OpenSansSemibold");
                });

            var a = Assembly.GetExecutingAssembly();
            using var stream = a.GetManifestResourceStream(settingsStream);
            builder.Configuration.AddJsonStream(stream);

            var connStr = builder.Configuration.GetConnectionString("SqliteConnection");
            string dataDirectory = FileSystem.Current.AppDataDirectory + "/";
            connStr = String.Format(connStr, dataDirectory);

            var options = new DbContextOptionsBuilder<AppDbContext>()
                           .UseSqlite(connStr)
                           .Options;
            builder.Services
                  .AddApplication()
                  .AddPersistence(options);

            //Контейнер управления зависимостями (IoC container) позволяет управлять зависимостями между различными компонентами приложения
            //singleton создается только один раз во время выполнения приложения и используется повторно во всех запросах
            builder.Services.AddTransient<NominationPage>();//создается каждый раз, когда он запрашивается из контейнера IoC, что означает, что каждый запрос получает новый экземпляр этой зависимости
            builder.Services.AddTransient<NominationPageViewModel>();
            builder.Services.AddTransient<NominationAddEditPage>();
            builder.Services.AddTransient<ParticipantAddEditPage>();
            builder.Services.AddTransient<NominationAddEditPageViewModel>();
            builder.Services.AddTransient<ParticipantAddEditPageViewModel>();
            builder.Services.AddMediatR(cfg => cfg.RegisterServicesFromAssembly(typeof(App).Assembly));

            builder.Services.AddTransient<ParticipantDetailsPage>();
            builder.Services.AddTransient<ParticipantDetailsViewModel>();
            builder.Services.AddTransient<ParticipantDetailsViewModel>();

            DbInitializer
                   .Initialize(builder.Services.BuildServiceProvider())
                   .Wait();


#if DEBUG
            builder.Logging.AddDebug();
#endif

            return builder.Build();
        }
        //private static void ConfigureServices(IServiceCollection services)
        //{
        //    services.AddApplication(); // Регистрация сервисов слоя приложения
        //    services.AddPersistence(); // Регистрация сервисов доступа к данным


        //    services.AddMediatR(conf =>
        //    conf.RegisterServicesFromAssembly(typeof(MauiProgram).Assembly));
        //    services.AddMediatR(conf =>
        //    conf.RegisterServicesFromAssembly(typeof(NominationPage).Assembly));
        //}
    }
}
