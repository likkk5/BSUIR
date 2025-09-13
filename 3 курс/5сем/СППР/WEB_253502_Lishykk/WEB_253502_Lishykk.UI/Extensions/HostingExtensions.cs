using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Cors.Infrastructure;
using WEB_253502_Lishykk.UI.HelperClasses;
using WEB_253502_Lishykk.UI.Services.Authentication;
using WEB_253502_Lishykk.UI.Services.CarService;
using WEB_253502_Lishykk.UI.Services.CategoryService;

namespace WEB_253502_Lishykk.UI.Extensions
{
    public static class HostingExtensions
    {
        /// <summary>
        /// Расширяющий метод для регистрации кастомных сервисов
        /// </summary>
        /// <param name="builder">WebApplicationBuilder</param>
        public static void RegisterCustomServices(this WebApplicationBuilder builder)
        {
            //builder.Services.AddScoped<ICategoryService, MemoryCategoryService>();
            //builder.Services.AddScoped<ICarService, MemoryCarService>();
            builder.Services.Configure<KeycloakData>(builder.Configuration.GetSection("Keycloak"));
            builder.Services.AddHttpClient<ITokenAccessor, KeycloakTokenAccessor>();
            builder.Services.AddHttpContextAccessor();
            builder.Services.AddHttpClient<IAuthService, KeycloakAuthService>();
        }
    }
}
