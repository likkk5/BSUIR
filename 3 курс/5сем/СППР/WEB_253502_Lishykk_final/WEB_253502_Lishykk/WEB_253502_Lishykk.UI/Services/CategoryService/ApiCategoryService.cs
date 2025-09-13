using System.Text.Json;
using System.Text;
using WEB_253502_Lishykk.Domain.Entities;
using WEB_253502_Lishykk.Domain.Models;
using WEB_253502_Lishykk.UI.Services.CarService;

namespace WEB_253502_Lishykk.UI.Services.CategoryService
{
    public class ApiCategoryService : ICategoryService
    {
        private HttpClient _httpClient;
        private JsonSerializerOptions _serializerOptions;
        private ILogger<ApiCarService> _logger;

        public ApiCategoryService(HttpClient httpClient, IConfiguration configuration, ILogger<ApiCarService> logger)
        {
            _httpClient = httpClient;
            _serializerOptions = new JsonSerializerOptions()
            {
                PropertyNamingPolicy = JsonNamingPolicy.CamelCase
            };
            _logger = logger;
        }
        public async Task<ResponseData<List<Category>>> GetCategoryListAsync()
        {
            var urlString = new StringBuilder($"{_httpClient.BaseAddress.AbsoluteUri}Category");
            var response = await _httpClient.GetAsync(new Uri(urlString.ToString()));
            if (response.IsSuccessStatusCode)
            {
                try
                {
                    return await response.Content.ReadFromJsonAsync<ResponseData<List<Category>>>(_serializerOptions);
                    //var data = await response.Content.ReadFromJsonAsync<ResponseData<ApiResponse<List<Category>>>>(_serializerOptions);
                    //return data;
                }
                catch (JsonException ex)
                {
                    _logger.LogError($"-----> Ошибка: {ex.Message}");
                    return ResponseData<List<Category>>.Error($"Ошибка: {ex.Message}");
                }
            }
            _logger.LogError($"-----> Данные не получены от сервера. Error: {response.StatusCode.ToString()}");
            return ResponseData<List<Category>>.Error($"Данные не получены от сервера. Error: {response.StatusCode.ToString()}");
        }
    }
}
