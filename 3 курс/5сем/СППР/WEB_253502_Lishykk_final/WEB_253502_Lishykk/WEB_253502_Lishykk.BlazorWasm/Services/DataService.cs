using System;
using System.Collections.Generic;
using System.Net.Http;
using System.Text.Json;
using System.Text;
using System.Threading.Tasks;
using WEB_253502_Lishykk.BlazorWasm.Models;
using Microsoft.AspNetCore.Components.WebAssembly.Authentication;

namespace WEB_253502_Lishykk.BlazorWasm.Services
{
    public class DataService : IDataService
    {
        private readonly HttpClient _httpClient;
        private readonly string _apiBaseUrl;
        private readonly int _pageSize;
        private readonly IAccessTokenProvider _tokenProvider;
        public string ApiBaseUrl => _apiBaseUrl;
        public event Action DataLoaded;

        public List<Category> Categories { get; set; } = new();
        public List<Car> Cars { get; set; } = new();
        public bool Success { get; set; }
        public string ErrorMessage { get; set; }
        public int TotalPages { get; set; }
        public int CurrentPage { get; set; }
        public Category SelectedCategory { get; set; }

        public DataService(HttpClient httpClient, AppSettings appSettings,IAccessTokenProvider tokenProvider)
        {
            _httpClient = httpClient;
            _apiBaseUrl = appSettings.ApiSettings.ApiBaseUrl;
            _pageSize = int.Parse(appSettings.ApiSettings.PageSize);
            _tokenProvider = tokenProvider;
        }

        // Метод для авторизованного запроса
        private async Task AddAuthorizationHeaderAsync()
        {
            var tokenRequest = await _tokenProvider.RequestAccessToken();
            if (tokenRequest.TryGetToken(out var token))
            {
                _httpClient.DefaultRequestHeaders.Authorization =
                    new System.Net.Http.Headers.AuthenticationHeaderValue("Bearer", token.Value);
            }
        }
        public async Task GetCarListAsync(string? categoryNormalizedName = null, int pageNo = 1)
        {
            try
            {
                await AddAuthorizationHeaderAsync();
                CurrentPage = pageNo;

                // Формирование маршрута
                var route = new StringBuilder($"{_apiBaseUrl}/car");

                if (!string.IsNullOrEmpty(categoryNormalizedName) && categoryNormalizedName != "All")
                {
                    route.Append($"/{categoryNormalizedName}");
                }

                var queryData = new List<string>
                {
                    $"pageNo={pageNo}",
                    $"pageSize={_pageSize}"
                };

                if (queryData.Count > 0)
                {
                    route.Append("?" + string.Join("&", queryData));
                }

                // HTTP-запрос
                var response = await _httpClient.GetAsync(route.ToString());
                response.EnsureSuccessStatusCode();

                var json = await response.Content.ReadAsStringAsync();

                // Десериализация
                var apiResponse = JsonSerializer.Deserialize<ApiResponse<PagedResult<Car>>>(json, new JsonSerializerOptions
                {
                    PropertyNameCaseInsensitive = true
                });

                if (apiResponse != null && apiResponse.Successfull)
                {
                    Cars = apiResponse.Data.Items;
                    TotalPages = apiResponse.Data.TotalPages;
                    Success = true;
                }
                else
                {
                    Success = false;
                    ErrorMessage = apiResponse?.ErrorMessage ?? "Неизвестная ошибка.";
                }
            }
            catch (Exception ex)
            {
                Success = false;
                ErrorMessage = ex.Message;
            }
            finally
            {
                DataLoaded?.Invoke();
            }
        }

        public async Task GetCategoryListAsync()
        {
            try
            {
                await AddAuthorizationHeaderAsync();
                var response = await _httpClient.GetAsync($"{_apiBaseUrl}/category");
                response.EnsureSuccessStatusCode();

                var json = await response.Content.ReadAsStringAsync();

                // Десериализация с учетом обертки
                var result = JsonSerializer.Deserialize<ApiResponse<List<Category>>>(json, new JsonSerializerOptions
                {
                    PropertyNameCaseInsensitive = true
                });

                if (result != null && result.Successfull)
                {
                    Categories = result.Data ?? new List<Category>();
                    Success = true;
                }
                else
                {
                    Success = false;
                    ErrorMessage = result?.ErrorMessage ?? "Неизвестная ошибка.";
                }
            }
            catch (Exception ex)
            {
                Success = false;
                ErrorMessage = $"Ошибка при загрузке категорий: {ex.Message}";
            }
            finally
            {
                DataLoaded?.Invoke();
            }
        }

    }

    // Вспомогательные модели
    public class ApiResponse<T>
    {
        public T Data { get; set; }
        public bool Successfull { get; set; }
        public string ErrorMessage { get; set; }
    }

    public class PagedResult<T>
    {
        public List<T> Items { get; set; } = new();
        public int CurrentPage { get; set; }
        public int TotalPages { get; set; }
    }

    public class Category
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string NormalizedName { get; set; }
    }

}
