using Microsoft.AspNetCore.Authentication.JwtBearer;
using System.Configuration;
using Microsoft.EntityFrameworkCore;
using WEB_253502_Lishykk.API;
using WEB_253502_Lishykk.API.Data;
using WEB_253502_Lishykk.API.Extensions;
using WEB_253502_Lishykk.API.Models;
//using WEB_253502_Lishykk.API.Services;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
var connectionString = builder.Configuration.GetConnectionString("Default");
// ����������� ��������� ���� ������ � �������������� SQLite
builder.Services.AddDbContext<AppDbContext>(options =>
    options.UseSqlite(connectionString));

builder.Services.AddControllers();
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

//builder.Services.AddScoped<ICategoryService, CategoryService>();
//builder.Services.AddScoped<ICarService, CarService>();
builder.Services.Configure<AppSettings>(builder.Configuration.GetSection("AppSettings"));
builder.RegisterCustomServices();
//builder.Services.AddControllers().AddJsonOptions(options =>
//{
//    options.JsonSerializerOptions.ReferenceHandler = System.Text.Json.Serialization.ReferenceHandler.Preserve;
//});

var authServer = builder.Configuration
    .GetSection("AuthServer")
    .Get<AuthServerData>();

// �������� ������ �������������� 
builder.Services.AddAuthentication(JwtBearerDefaults.AuthenticationScheme)
    .AddJwtBearer(JwtBearerDefaults.AuthenticationScheme, o =>
    {
        // ����� ���������� ������������ OpenID 
        o.MetadataAddress = $"{authServer.Host}/realms/{authServer.Realm}/.well-known/openid-configuration"; 

        // Authority ������� �������������� 
        o.Authority = $"{authServer.Host}/realms/{authServer.Realm}";

        // Audience ��� ������ JWT 
        o.Audience = "account";
 
        o.RequireHttpsMetadata = false;
    });

builder.Services.AddAuthorization(opt =>
{
    opt.AddPolicy("admin", p => p.RequireRole("POWER-USER"));
    //opt.AddPolicy("admin", p =>
    //p.RequireClaim("resource_access.LishykUiClient.roles", "POWER-USER"));
});
builder.Services.AddCors(options =>
{
    options.AddPolicy("AllowBlazorApp", builder =>
    {
        builder.WithOrigins("https://localhost:7001") // URL ������ Blazor-����������
               .AllowAnyMethod()
               .AllowAnyHeader()
               .AllowCredentials(); // ���� ������������ �����������
    });
});

builder.Logging.ClearProviders();
builder.Logging.AddConsole();
builder.Logging.AddDebug();

var app = builder.Build();
// ��������� ������������� ������
await DbInitializer.SeedData(app);

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}
app.UseStaticFiles(); // ��� ������� � ����������� ������ �� wwwroot
app.UseHttpsRedirection();
app.UseCors("AllowBlazorApp");
app.UseAuthentication();
app.UseAuthorization();

app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Car}/{action=GetCars}/{category?}");


app.Run();
