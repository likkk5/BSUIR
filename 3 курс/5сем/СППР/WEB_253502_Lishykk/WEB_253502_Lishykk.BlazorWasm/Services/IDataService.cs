using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using WEB_253502_Lishykk.BlazorWasm.Models;

namespace WEB_253502_Lishykk.BlazorWasm.Services
{
    public interface IDataService
    {
        // Событие, генерируемое при изменении данных
        event Action DataLoaded;

        // Список категорий объектов
        List<Category> Categories { get; set; }

        // Список объектов (автомобилей)
        List<Car> Cars { get; set; }

        // Признак успешного ответа на запрос к API
        bool Success { get; set; }

        // Сообщение об ошибке
        string ErrorMessage { get; set; }

        // Количество страниц списка
        int TotalPages { get; set; }

        // Номер текущей страницы
        int CurrentPage { get; set; }

        // Фильтр по категории
        Category SelectedCategory { get; set; }
        string ApiBaseUrl { get; }
        /// <summary>
        /// Получение списка всех автомобилей
        /// </summary>
        /// <param name="pageNo">номер страницы</param>
        /// <returns></returns>
        Task GetCarListAsync(string? categoryNormalizedName = null, int pageNo = 1);

        /// <summary>
        /// Получение списка категорий
        /// </summary>
        /// <returns></returns>
        Task GetCategoryListAsync();
    }
}
