using Bahdanau_153502.Application.Abstractions;
using Bahdanau_153502.Application.Services;
using Bahdanau_153502.Domain.Abstractions;
using Bahdanau_153502.Domain.Entities;
using Bahdanau_153502.Persistence.Data;
using Bahdanau_153502.Persistence.UnitOfWork;
using Bahdanau_153502.UI.Pages;
using Bahdanau_153502.UI.ValueConverters;
using Bahdanau_153502.UI.ViewModels;
using CommunityToolkit.Maui;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Logging;
using Microsoft.Maui.Storage;
using System.Reflection;

namespace Bahdanau_153502.UI;

public static partial class MauiProgram
{
    public static MauiApp CreateMauiApp()
    {
        MauiAppBuilder builder = MauiApp.CreateBuilder();
        builder
            .UseMauiApp<App>()
            .UseMauiCommunityToolkit()
            .ConfigureFonts(fonts =>
            {
                fonts.AddFont("OpenSans-Regular.ttf", "OpenSansRegular");
                fonts.AddFont("OpenSans-Semibold.ttf", "OpenSansSemibold");
            });

#if DEBUG
        builder.Logging.AddDebug();
#endif

        SetupConfiguration(builder);

        return builder.Build();
    }

    private static void SetupConfiguration(MauiAppBuilder builder)
    {
        string path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), AppInfo.Current.Name);

        if (!Path.Exists(path))
        {
            Directory.CreateDirectory(path);
        }

        Preferences.Default.Set("LocalData", path);

        SetupDB(builder.Configuration);
        AddDbContext(builder);

        SetupServices(builder.Services);
        SetupViewModels(builder.Services);
        SetupPages(builder.Services);

        SeedData(builder.Services);

    }


    public static async void SeedData(IServiceCollection services)
    {
        using ServiceProvider provider = services.BuildServiceProvider();
        IUnitOfWork unitOfWork = provider.GetService<IUnitOfWork>();
        await unitOfWork.RemoveDatbaseAsync();
        await unitOfWork.CreateDatabaseAsync();

        IReadOnlyList<TouristRoute> touristRoutes = new List<TouristRoute>()
            {
            new (){Title="Мини-тур по Японии", DistanceInKm=4585 },
            new (){Title="Поход через Америку", DistanceInKm=4265 },
            };

        foreach (TouristRoute touristRoute in touristRoutes)
            await unitOfWork.TouristRouteRepository.AddAsync(touristRoute);

        await unitOfWork.SaveAllAsync();

        Random rand = new();

        List<string> cities = new()
        {
            "New York City",
            "Houston",
            "Chicago",
            "Washington DC",
            "Los Angeles",
        };

        foreach (TouristRoute touristRoute in touristRoutes)
        {
            for (int j = 0; j < 6; j++)
            {
                await unitOfWork.LandmarkRepository.AddAsync(new()
                {
                    TouristRoute = touristRoute,
                    City = cities[rand.Next(cities.Count)],
                    Description = $"Landmark-{j}",
                    TicketPrice = 145 + (rand.Next() % 10)
                });
            }
        }

        await unitOfWork.SaveAllAsync();
    }

    private static void SetupDB(IConfigurationBuilder configuration)
    {
        string settingsPath = "Bahdanau_153502.UI.appsettings.json";
        using Stream stream = Assembly.GetExecutingAssembly().GetManifestResourceStream(settingsPath);
        configuration.AddJsonStream(stream);
    }

    private static void AddDbContext(MauiAppBuilder builder)
    {
        string connectionString = builder.Configuration.GetConnectionString("SqliteConnection");
        string dataDirectory = string.Empty;

#if ANDROID
        dataDirectory = FileSystem.AppDataDirectory + "/";
#endif

        connectionString = string.Format(connectionString, dataDirectory);

        DbContextOptions<AppDbContext> options =
            new DbContextOptionsBuilder<AppDbContext>()
            .UseSqlite(connectionString)
            .Options;

        builder.Services.AddSingleton((s) => new AppDbContext(options));
    }

    private static void SetupServices(IServiceCollection services)
    {
        services.AddSingleton<IUnitOfWork, EfUnitOfWork>();
        services.AddSingleton<ILandmarkService, LandmarkService>();
        services.AddSingleton<ITouristRouteService, TouristRouteService>();
    }

    private static void SetupViewModels(IServiceCollection services)
    {
        services.AddSingleton<TouristRoutesViewModel>();
        services.AddTransient<LandmarkDetailsViewModel>();
        services.AddTransient<AddOrUpdateTouristRouteViewModel>();
        services.AddTransient<AddOrUpdateLandmarkViewModel>();
    }

    private static void SetupPages(IServiceCollection services)
    {
        services.AddSingleton<TouristRoutes>();
        services.AddTransient<LandmarkDetails>();
        services.AddTransient<AddOrUpdateTouristRoute>();
        services.AddTransient<AddOrUpdateLandmark>();
    }
}
