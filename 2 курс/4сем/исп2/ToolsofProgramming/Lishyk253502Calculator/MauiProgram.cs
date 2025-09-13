using Microsoft.Extensions.DependencyInjection;
using Microsoft.Maui;
using Microsoft.Maui.Controls.Hosting;
using Microsoft.Maui.Hosting;
using Microsoft.Extensions.Logging;
using Lishyk253502Calculator.Services;
using Lishyk253502Calculator.Service;
using Lishyk253502Calculator.View;
using System;

namespace Lishyk253502Calculator
{
    public static class MauiProgram
    {
        public static MauiApp CreateMauiApp()
        {
            var builder = MauiApp.CreateBuilder();
            builder
                .UseMauiApp<App>()
                .ConfigureFonts(fonts =>
                {
                    fonts.AddFont("OpenSans-Regular.ttf", "OpenSansRegular");
                    fonts.AddFont("OpenSans-Semibold.ttf", "OpenSansSemibold");
                });

            //builder.Services.AddHttpClient();
            builder.Services.AddHttpClient<IRateService,RateService>(client =>
            {
                client.BaseAddress = new Uri("https://www.nbrb.by/api/exrates/rates");//регистрация сервиса
            });

            builder.Services.AddTransient<SQLiteDemoPage>(); //создается каждый раз при запросе
            builder.Services.AddTransient<IDbService, SQLiteService>();
            //builder.Services.AddTransient<IRateService, RateService>();
            builder.Services.AddTransient<CurrencyConverterPage>();

#if DEBUG
            builder.Logging.AddDebug();
#endif
            return builder.Build();
        }
    }
}
