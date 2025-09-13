using WEB_253502_Lishykk.API.Services.CarService;
using WEB_253502_Lishykk.API.Services.CategoryService;

namespace WEB_253502_Lishykk.API.Extensions
{
    public static class HostingExtensions
    {
        public static void RegisterCustomServices(this WebApplicationBuilder builder)
        {
            builder.Services.AddScoped<ICategoryService, CategoryService>();
            builder.Services.AddScoped<ICarService, CarService>();
        }
    }
}
