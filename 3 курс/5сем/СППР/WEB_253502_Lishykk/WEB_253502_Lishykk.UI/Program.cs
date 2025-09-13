using System.Configuration;
using System;
using WEB_253502_Lishykk.UI;
using WEB_253502_Lishykk.UI.Extensions;
using WEB_253502_Lishykk.UI.Services;
using WEB_253502_Lishykk.UI.Services.CarService;
using WEB_253502_Lishykk.UI.Services.CategoryService;
using Microsoft.EntityFrameworkCore;
using WEB_253502_Lishykk.UI.Services.FileService;
using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Authentication.OpenIdConnect;
using Microsoft.IdentityModel.Protocols.OpenIdConnect;
using WEB_253502_Lishykk.UI.HelperClasses;
using Microsoft.AspNetCore.Authentication;
using WEB_253502_Lishykk.Domain.Entities;
using Serilog;
using WEB_253502_Lishykk.UI.Middleware;

var builder = WebApplication.CreateBuilder(args);

// Чтение конфигурации из файла appsettings.json
builder.Host.UseSerilog((context, services, configuration) => configuration
    .ReadFrom.Configuration(context.Configuration)
    .Enrich.FromLogContext()
    .WriteTo.Console(outputTemplate: "{Timestamp:yyyy-MM-dd HH:mm:ss.fff zzz} [{Level:u3}] ---> {Message:lj}{NewLine}{Exception}")
    .WriteTo.File("logs/log-.txt", rollingInterval: RollingInterval.Day, outputTemplate: "{Timestamp:yyyy-MM-dd HH:mm:ss.fff zzz} [{Level:u3}] ---> {Message:lj}{NewLine}{Exception}")
);

// Вызов расширяющего метода для регистрации сервисов
builder.RegisterCustomServices();

//builder.Services.AddControllers()
//    .AddJsonOptions(options =>
//        options.JsonSerializerOptions.ReferenceHandler = System.Text.Json.Serialization.ReferenceHandler.IgnoreCycles);
builder.Configuration.AddJsonFile("appsettings.json");
builder.Services.AddControllersWithViews();
builder.Services.AddRazorPages();
builder.Services.AddDistributedMemoryCache();
builder.Services.AddSession(); 

builder.Services.Configure<UriData>(builder.Configuration.GetSection("UriData"));
var uriData = builder.Configuration.GetSection("UriData").Get<UriData>();

builder.Services.AddHttpClient<ICategoryService, ApiCategoryService>(opt =>
    opt.BaseAddress = new Uri(uriData.ApiUri));

builder.Services.AddHttpClient<ICarService, ApiCarService>(opt =>
    opt.BaseAddress = new Uri(uriData.ApiUri));

builder.Services.AddHttpClient<IFileService, ApiFileService>(opt =>
    opt.BaseAddress = new Uri($"{uriData.ApiUri}Files"));

var keycloakData =
builder.Configuration.GetSection("Keycloak").Get<KeycloakData>();

// Регистрируем Cart как Scoped сервис
builder.Services.AddScoped<Cart>(sp => SessionCart.GetCart(sp));
builder.Services.AddSingleton<IHttpContextAccessor, HttpContextAccessor>();

//builder.Services.AddSession(options =>
//{
//    options.IdleTimeout = TimeSpan.FromMinutes(30); // Время хранения сессии
//});

builder.Services
    .AddAuthentication(options =>
    {
        options.DefaultScheme = CookieAuthenticationDefaults.AuthenticationScheme;
        options.DefaultChallengeScheme = OpenIdConnectDefaults.AuthenticationScheme;
    })
    .AddCookie()
    .AddJwtBearer()
    .AddOpenIdConnect(options =>
    {
        options.Authority =$"{keycloakData.Host}/auth/realms/{keycloakData.Realm}";
        options.ClientId = keycloakData.ClientId;
        options.ClientSecret = keycloakData.ClientSecret;
        options.ResponseType = OpenIdConnectResponseType.Code;
        options.Scope.Add("openid"); // Customize scopes as needed 
        options.SaveTokens = true;
        options.RequireHttpsMetadata = false; // позволяет обращаться к локальному Keycloak по http
        options.MetadataAddress = $"{keycloakData.Host}/realms/{keycloakData.Realm}/.well-known/openid-configuration";
        options.Events = new OpenIdConnectEvents
        {
            OnRedirectToIdentityProviderForSignOut = async context =>
            {
                // Получаем ID токен из сохраненных токенов
                var idToken = await context.HttpContext.GetTokenAsync("id_token");

                // Формируем URL для логаута
                var logoutUri = $"{keycloakData.Host}/realms/{keycloakData.Realm}/protocol/openid-connect/logout";

                // Если у нас есть ID токен, добавляем его в запрос
                if (!string.IsNullOrEmpty(idToken))
                {
                    logoutUri += $"?id_token_hint={idToken}";
                }

                // Формируем URL для возврата после логаута
                var postLogoutRedirectUri = "https://localhost:7001";

                // Добавляем параметр post_logout_redirect_uri для возврата в приложение
                logoutUri += $"&post_logout_redirect_uri={postLogoutRedirectUri}";
                // Дополнительный параметр postLogoutRedirectUri
                logoutUri += $"&postLogoutRedirectUri={context.Properties.RedirectUri}";

                // Перенаправляем пользователя на логаут в Keycloak
                context.Response.Redirect(logoutUri);
                context.HandleResponse();
            }
        };
    });
//builder.Services.AddHttpContextAccessor();
//var connectionString = builder.Configuration.GetConnectionString("DefaultConnection");
//builder.Services.AddDbContext<TemporaryDbContext>(options =>
//    options.UseSqlite(connectionString));

//// Добавление TempDataProvider (для поддержки TempData)
//builder.Services.AddSingleton<Microsoft.AspNetCore.Mvc.ViewFeatures.ITempDataProvider, Microsoft.AspNetCore.Mvc.ViewFeatures.CookieTempDataProvider>();
//builder.Services.AddSingleton<Microsoft.AspNetCore.Mvc.ViewFeatures.ITempDataDictionaryFactory, Microsoft.AspNetCore.Mvc.ViewFeatures.TempDataDictionaryFactory>();
builder.Services.AddHttpContextAccessor();
//builder.Services.AddSingleton<LinkGenerator>();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Home/Error");
    // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
    app.UseHsts();
}

app.UseHttpsRedirection();
app.UseStaticFiles();
app.UseSession();

app.UseRouting();

app.UseAuthentication();
app.UseAuthorization();

app.UseMiddleware<LoggingMiddleware>();


app.MapRazorPages();
app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Home}/{action=Index}/{id?}");

app.MapControllerRoute(
    name: "car",
    pattern: "{controller=Car}/{action=Index}/{id?}");
//app.MapControllerRoute(
//    name: "car",
//    pattern: "{controller=Car}/{action=Index}/{pageNo?}");

app.MapControllerRoute(
        name: "areas",
        pattern: "{area:exists}/{controller=Home}/{action=Index}/{id?}");

app.Run();
