using Microsoft.Extensions.Options;
using System.Text.Json;
using System.Text;
using WEB_253502_Lishykk.UI.HelperClasses;
using WEB_253502_Lishykk.UI.Services.FileService;
using WEB_253502_Lishykk.UI.Models;

namespace WEB_253502_Lishykk.UI.Services.Authentication
{
    public class KeycloakAuthService : IAuthService
    {
        private readonly HttpClient _httpClient;
        private readonly IFileService _fileService;
        private readonly ITokenAccessor _tokenAccessor;
        private readonly KeycloakData _keycloakData;

        public KeycloakAuthService(HttpClient httpClient, IOptions<KeycloakData> options, IFileService fileService, ITokenAccessor tokenAccessor)
        {
            _httpClient = httpClient;
            _fileService = fileService;
            _tokenAccessor = tokenAccessor;
            _keycloakData = options.Value;
        }

        public async Task<(bool Result, string ErrorMessage)> RegisterUserAsync(string email, string password, IFormFile? avatar)
        {
            // Получить токен для аутентификации в Keycloak Admin API
            try
            {
                await _tokenAccessor.SetAuthorizationHeaderAsync(_httpClient);
            }
            catch (Exception ex)
            {
                return (false, ex.Message);
            }

            // Установить стандартный URL аватара
            var avatarUrl = "/images/default-profile-picture.png";

            // Сохранить аватар, если он был передан
            if (avatar != null)
            {
                var result = await _fileService.SaveFileAsync(avatar);
                if (result != null)
                {
                    avatarUrl = result;
                }
            }

            // Подготовить данные нового пользователя
            var newUser = new CreateUserModel
            {
                Email = email,
                Username = email,
                Attributes = new Dictionary<string, string> { { "avatar", avatarUrl } },
                Credentials = new List<UserCredentials> { new UserCredentials { Value = password } }
            };

            // Подготовка запроса к Keycloak API
            var requestUri = $"{_keycloakData.Host}/admin/realms/{_keycloakData.Realm}/users";
            var userData = JsonSerializer.Serialize(newUser, new JsonSerializerOptions { PropertyNamingPolicy = JsonNamingPolicy.CamelCase });
            var content = new StringContent(userData, Encoding.UTF8, "application/json");

            // Выполнить запрос
            var response = await _httpClient.PostAsync(requestUri, content);

            if (response.IsSuccessStatusCode)
            {
                return (true, string.Empty);
            }
            return (false, response.StatusCode.ToString());
        }
    }

}
