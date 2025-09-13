using System.Net.Http.Json;
using Blazored.LocalStorage;
using Microsoft.AspNetCore.Components.Web;
using Microsoft.AspNetCore.Components.WebAssembly.Hosting;
using WEB_253502_Lishykk.BlazorWasm;
using WEB_253502_Lishykk.BlazorWasm.Services;

var builder = WebAssemblyHostBuilder.CreateDefault(args);
builder.RootComponents.Add<App>("#app");
builder.RootComponents.Add<HeadOutlet>("head::after");

//builder.Services.AddScoped(sp => new HttpClient { BaseAddress = new Uri(builder.HostEnvironment.BaseAddress) });
// Чтение appsettings.json
var http = new HttpClient { BaseAddress = new Uri(builder.HostEnvironment.BaseAddress) };
var appSettings = await http.GetFromJsonAsync<AppSettings>("appsettings.json");

if (appSettings == null || appSettings.ApiSettings == null)
{
    throw new Exception("Failed to load API settings from appsettings.json.");
}

builder.Services.AddSingleton(appSettings);
builder.Services.AddScoped(sp => new HttpClient
{
    BaseAddress = new Uri(appSettings.ApiSettings.ApiBaseUrl)
});

builder.Services.AddSingleton(appSettings);
builder.Services.AddScoped<IDataService, DataService>();
builder.Services.AddScoped<CartService>();
builder.Services.AddBlazoredLocalStorage();

//builder.Services.AddOidcAuthentication(options =>
//{
//    // Configure your authentication provider options here.
//    // For more information, see https://aka.ms/blazor-standalone-auth
//    builder.Configuration.Bind("Local", options.ProviderOptions);
//});
builder.Services.AddOidcAuthentication(options =>
{
    // Configure your authentication provider options here. 
    // For more information, see https://aka.ms/blazor-standalone-auth 
    builder.Configuration.Bind("Keycloak", options.ProviderOptions);
    //options.ProviderOptions.DefaultScopes.Add("openid");
    //options.ProviderOptions.DefaultScopes.Add("profile");
    //options.ProviderOptions.DefaultScopes.Add("email");
});
await builder.Build().RunAsync();
