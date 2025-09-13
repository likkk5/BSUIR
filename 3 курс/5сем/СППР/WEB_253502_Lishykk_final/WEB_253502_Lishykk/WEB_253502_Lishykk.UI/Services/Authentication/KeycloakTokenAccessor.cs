using Microsoft.AspNetCore.Authentication;
using Microsoft.Extensions.Options;
using System.Net.Http.Headers;
using System.Text.Json;
using WEB_253502_Lishykk.UI.HelperClasses;

namespace WEB_253502_Lishykk.UI.Services.Authentication
{
    public class KeycloakTokenAccessor : ITokenAccessor
    {
        private readonly KeycloakData _keycloakData;
        private readonly HttpContext? _httpContext;
        private readonly HttpClient _httpClient;

        public KeycloakTokenAccessor(IOptions<KeycloakData> options,
                                     IHttpContextAccessor httpContextAccessor,
                                     HttpClient httpClient)
        {
            _keycloakData = options.Value;
            _httpContext = httpContextAccessor.HttpContext;
            _httpClient = httpClient;
        }

        public async Task<string> GetAccessTokenAsync()
        {
            // Если пользователь аутентифицирован, получить его токен
            if (_httpContext != null && _httpContext.User.Identity.IsAuthenticated)
            {
                return await _httpContext.GetTokenAsync("access_token");
            }

            // Если пользователь не аутентифицирован, запросить клиентский токен
            var requestUri = $"{_keycloakData.Host}/realms/{_keycloakData.Realm}/protocol/openid-connect/token";

            var content = new FormUrlEncodedContent(new[]
            {
                new KeyValuePair<string, string>("client_id", _keycloakData.ClientId),
                new KeyValuePair<string, string>("grant_type", "client_credentials"),
                new KeyValuePair<string, string>("client_secret", _keycloakData.ClientSecret)
            });

            var response = await _httpClient.PostAsync(requestUri, content);

            if (!response.IsSuccessStatusCode)
            {
                throw new HttpRequestException($"Ошибка получения токена: {response.StatusCode}");
            }

            //var jsonString = await response.Content.ReadAsStringAsync();
            //var jsonObject = JsonDocument.Parse(jsonString);

            //return jsonObject.RootElement.GetProperty("access_token").GetString();
            var jsonString = await response.Content.ReadAsStringAsync();
            var jsonObject = JsonDocument.Parse(jsonString).RootElement;

            return jsonObject.GetProperty("access_token").GetString();
        }

        public async Task SetAuthorizationHeaderAsync(HttpClient httpClient)
        {
            var token = await GetAccessTokenAsync();
            httpClient.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("Bearer", token);
        }
    }
}
