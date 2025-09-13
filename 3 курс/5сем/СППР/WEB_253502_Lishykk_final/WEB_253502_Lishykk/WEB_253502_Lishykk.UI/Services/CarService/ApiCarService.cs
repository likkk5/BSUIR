using System.Text.Json;
using System.Text;
using WEB_253502_Lishykk.Domain.Models;
using WEB_253502_Lishykk.Domain.Entities;
using WEB_253502_Lishykk.UI.Services.FileService;
using WEB_253502_Lishykk.UI.Services.Authentication;
using WEB_253502_Lishykk.UI.Domain.Models;

namespace WEB_253502_Lishykk.UI.Services.CarService
{
    public class ApiCarService : ICarService
    {
        private HttpClient _httpClient;
        private string? _pageSize;
        private JsonSerializerOptions _serializerOptions;
        private ILogger<ApiCarService> _logger;
        private readonly IFileService _fileService;
        private readonly ITokenAccessor _tokenAccessor;
        public ApiCarService(HttpClient httpClient, IConfiguration configuration, ILogger<ApiCarService> logger, IFileService fileService, ITokenAccessor tokenAccessor)
        {
            _httpClient = httpClient;
            _pageSize = configuration.GetSection("ItemsPerPage").Value;
            _serializerOptions = new JsonSerializerOptions()
            {
                PropertyNamingPolicy = JsonNamingPolicy.CamelCase
            };
            _logger = logger;
            _fileService = fileService;
            _tokenAccessor = tokenAccessor;
        }
        //public async Task<ResponseData<Car>> CreateCarAsync(Car car, IFormFile? formFile)
        //{
        //    var uri = new Uri(_httpClient.BaseAddress.AbsoluteUri + "Car");

        //    using (var content = new MultipartFormDataContent())
        //    {
        //        // Добавляем данные автомобиля
        //        var carJson = JsonSerializer.Serialize(car, _serializerOptions);
        //        content.Add(new StringContent(carJson, Encoding.UTF8, "application/json"), "car");

        //        // Добавляем файл изображения, если он есть
        //        if (formFile != null)
        //        {
        //            var fileContent = new StreamContent(formFile.OpenReadStream());
        //            fileContent.Headers.ContentType = new System.Net.Http.Headers.MediaTypeHeaderValue(formFile.ContentType);
        //            content.Add(fileContent, "ImageFile", formFile.FileName);
        //        }

        //        // Отправка запроса
        //        var response = await _httpClient.PostAsync(uri, content);

        //        if (response.IsSuccessStatusCode)
        //        {
        //            try
        //            {
        //                var data = await response.Content.ReadFromJsonAsync<ResponseData<Car>>(_serializerOptions);
        //                return data;
        //            }
        //            catch (JsonException ex)
        //            {
        //                _logger.LogError($"-----> Ошибка: {ex.Message}");
        //                return ResponseData<Car>.Error($"Ошибка: {ex.Message}");
        //            }
        //        }

        //        _logger.LogError($"Объект не добавлен. Error: {response.StatusCode}");
        //        return ResponseData<Car>.Error($"Объект не добавлен. Error: {response.StatusCode}");
        //    }
        //}
        public async Task<ResponseData<Car>> CreateCarAsync(Car car, IFormFile? formFile)
        {
            // Установка заголовка авторизации
            await _tokenAccessor.SetAuthorizationHeaderAsync(_httpClient);
            // Установка изображения по умолчанию
            car.ImagePath = "/Images/noimage.jpg";

            // Если файл изображения присутствует, сохраняем его
            if (formFile != null)
            {
                var imageUrl = await _fileService.SaveFileAsync(formFile);
                if (!string.IsNullOrEmpty(imageUrl))
                {
                    car.ImagePath = imageUrl; // Обновляем путь к изображению
                }
            }

            var uri = new Uri(_httpClient.BaseAddress.AbsoluteUri + "Car");

            // Сериализация объекта car в JSON
            var carJson = JsonSerializer.Serialize(car, _serializerOptions);

            // Создаем StringContent с типом "application/json"
            var content = new StringContent(carJson, Encoding.UTF8, "application/json");

            // Отправляем запрос POST с JSON в теле
            var response = await _httpClient.PostAsync(uri, content);

            if (response.IsSuccessStatusCode)
            {
                try
                {
                    var data = await response.Content.ReadFromJsonAsync<ResponseData<Car>>(_serializerOptions);
                    return data; // Вернуть успешно созданный автомобиль
                }
                catch (JsonException ex)
                {
                    _logger.LogError($"-----> Ошибка: {ex.Message}");
                    return ResponseData<Car>.Error($"Ошибка: {ex.Message}");
                }
            }

            _logger.LogError($"Объект не добавлен. Error: {response.StatusCode}");
            return ResponseData<Car>.Error($"Объект не добавлен. Error: {response.StatusCode}"); // Вернуть ошибку
        }



        public async Task<ResponseData<string>> DeleteCarAsync(int id)
        {
            // Установка заголовка авторизации
            await _tokenAccessor.SetAuthorizationHeaderAsync(_httpClient);

            var uri = new Uri(_httpClient.BaseAddress.AbsoluteUri + "Car/" + $"{id}");
            var response = await _httpClient.DeleteAsync(uri);
            if (response.IsSuccessStatusCode)
            {
                try
                {
                    return await response.Content.ReadFromJsonAsync<ResponseData<string>>(_serializerOptions);
                }
                catch (JsonException ex)
                {
                    _logger.LogError($"-----> Ошибка: {ex.Message}");
                    return ResponseData<string>.Error($"Ошибка: {ex.Message}");
                }
            }
            _logger.LogError($"-----> Объект не удален. Error: {response.StatusCode.ToString()}");
            return ResponseData<string>.Error($"Объект не удален. Error: {response.StatusCode}");
        }

        public async Task<ResponseData<Car>> GetCarByIdAsync(int id)
        {
            // Установка заголовка авторизации
            await _tokenAccessor.SetAuthorizationHeaderAsync(_httpClient);
            var uri = new Uri(_httpClient.BaseAddress.AbsoluteUri + "Car/" + $"{id}");
            var response = await _httpClient.GetAsync(uri);
            if (response.IsSuccessStatusCode)
            {
                try
                {
                    return await response.Content.ReadFromJsonAsync<ResponseData<Car>>(_serializerOptions);
                }
                catch (JsonException ex)
                {
                    _logger.LogError($"-----> Ошибка: {ex.Message}");
                    return ResponseData<Car>.Error($"Ошибка: {ex.Message}");
                }
            }
            _logger.LogError($"-----> Данные не получены от сервера. Error: {response.StatusCode.ToString()}");
            return ResponseData<Car>.Error($"Данные не получены от сервера. Error: {response.StatusCode}");
        }

        public async Task<ResponseData<ListModel<Car>>> GetCarListAsync(string? categoryNormalizedName, int pageNo = 1)
        {
            // Установка заголовка авторизации
            await _tokenAccessor.SetAuthorizationHeaderAsync(_httpClient);
            // подготовка URL запроса
            var urlString = new StringBuilder($"{_httpClient.BaseAddress.AbsoluteUri}Car");
            // добавить категорию в маршрут
            if (categoryNormalizedName != null && categoryNormalizedName != "All")
            {
                urlString.Append($"/{categoryNormalizedName}/");
            }
            var queryString = new List<string>();
            if (pageNo > 1)
            {
                queryString.Add($"pageNo={pageNo}");
            }
            if (!_pageSize.Equals(3))
            {
                queryString.Add($"pageSize={_pageSize}");
            }
            if (queryString.Count > 0)
            {
                urlString.Append("?" + string.Join("&", queryString));
            }
            // выполнение запроса
            var response = await _httpClient.GetAsync(new Uri(urlString.ToString()));
            if (response.IsSuccessStatusCode)
            {
                try
                {
                    return await response.Content.ReadFromJsonAsync<ResponseData<ListModel<Car>>>(_serializerOptions);
                }
                catch (JsonException ex)
                {
                    _logger.LogError($"-----> Ошибка: {ex.Message}");
                    return ResponseData<ListModel<Car>>.Error($"Ошибка: {ex.Message}");
                }

            }
            _logger.LogError($"-----> Данные не получены от сервера. Error: {response.StatusCode.ToString()}");
            return ResponseData<ListModel<Car>>.Error($"Данные не получены от сервера. Error: {response.StatusCode.ToString()}, url: {urlString}");
        }

        //public async Task<ResponseData<Car>> UpdateCarAsync(int id, Car car, IFormFile? formFile)
        //{
        //    var uri = new Uri(_httpClient.BaseAddress.AbsoluteUri + "Car/" + $"{id}");
        //    var response = await _httpClient.PutAsJsonAsync(uri, car, _serializerOptions);
        //    if (response.IsSuccessStatusCode)
        //    {
        //        try
        //        {
        //            var data = await response.Content.ReadFromJsonAsync<ResponseData<Car>>(_serializerOptions);
        //            if (formFile != null)
        //                return data;
        //        }
        //        catch (JsonException ex)
        //        {
        //            _logger.LogError($"-----> Ошибка: {ex.Message}");
        //            return ResponseData<Car>.Error($"Ошибка: {ex.Message}");
        //        }
        //    }
        //    _logger.LogError($"Объект не обновлен. Error: {response.StatusCode.ToString()}");
        //    return ResponseData<Car>.Error($"Объект не обновлен. Error:{response.StatusCode}");
        //}
        public async Task<ResponseData<Car>> UpdateCarAsync(int id, Car car, IFormFile? formFile)
        {
            // Установка заголовка авторизации
            await _tokenAccessor.SetAuthorizationHeaderAsync(_httpClient);
            var uri = new Uri(_httpClient.BaseAddress.AbsoluteUri + "Car/" + $"{id}");

            // Если предоставлен новый файл изображения, сначала загружаем его
            if (formFile != null)
            {
                var imageUrl = await _fileService.SaveFileAsync(formFile);
                if (!string.IsNullOrEmpty(imageUrl))
                {
                    car.ImagePath = imageUrl; // Обновляем путь к изображению
                }
            }

            // Сериализация объекта car в JSON
            var carJson = JsonSerializer.Serialize(car, _serializerOptions);

            // Создаем StringContent с типом "application/json"
            var content = new StringContent(carJson, Encoding.UTF8, "application/json");

            // Отправляем запрос PUT с JSON в теле
            var response = await _httpClient.PutAsync(uri, content);

            if (response.IsSuccessStatusCode)
            {
                try
                {
                    var data = await response.Content.ReadFromJsonAsync<ResponseData<Car>>(_serializerOptions);
                    return data;
                }
                catch (JsonException ex)
                {
                    _logger.LogError($"-----> Ошибка: {ex.Message}");
                    return ResponseData<Car>.Error($"Ошибка: {ex.Message}");
                }
            }

            _logger.LogError($"Объект не обновлен. Error: {response.StatusCode}");
            return ResponseData<Car>.Error($"Объект не обновлен. Error:{response.StatusCode}");
        }

    }
}
