using System.Net.Http.Headers;
using System.Net.Http.Json;
using WEB_253502_Lishykk.UI.Services.Authentication;
using WEB_253502_Lishykk.UI.Services.FileService;

public class ApiFileService : IFileService
{
    private readonly HttpClient _httpClient;
    private readonly ITokenAccessor _tokenAccessor;

    public ApiFileService(HttpClient httpClient, ITokenAccessor tokenAccessor)
    {
        _httpClient = httpClient;
        _tokenAccessor = tokenAccessor;
    }

    public async Task<string> SaveFileAsync(IFormFile formFile)
    {
        // Установка заголовка авторизации
        await _tokenAccessor.SetAuthorizationHeaderAsync(_httpClient);
        var request = new HttpRequestMessage
        {
            Method = HttpMethod.Post,
            RequestUri = new Uri(_httpClient.BaseAddress, "Files")
        };

        // Создать контент, содержащий поток загруженного файла
        var content = new MultipartFormDataContent();
        var streamContent = new StreamContent(formFile.OpenReadStream())
        {
            Headers =
            {
                ContentLength = formFile.Length,
                ContentType = new MediaTypeHeaderValue(formFile.ContentType)
            }
        };
        content.Add(streamContent, "file", formFile.FileName);

        // Поместить контент в запрос
        request.Content = content;

        // Отправить запрос к API
        var response = await _httpClient.SendAsync(request);
        if (response.IsSuccessStatusCode)
        {
            // Вернуть полученный Url сохраненного файла
            return await response.Content.ReadAsStringAsync();
        }
        return string.Empty; // или выбросить исключение
    }

    public async Task DeleteFileAsync(string fileName)
    {
        // Установка заголовка авторизации
        await _tokenAccessor.SetAuthorizationHeaderAsync(_httpClient);
        var response = await _httpClient.DeleteAsync($"Files/{fileName}");
        response.EnsureSuccessStatusCode();
    }
}
