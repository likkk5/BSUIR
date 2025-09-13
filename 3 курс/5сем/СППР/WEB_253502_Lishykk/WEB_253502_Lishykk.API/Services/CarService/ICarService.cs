using WEB_253502_Lishykk.API.Models;
using WEB_253502_Lishykk.Domain.Entities;
using WEB_253502_Lishykk.Domain.Models;
using WEB_253502_Lishykk.UI.Domain.Models;

namespace WEB_253502_Lishykk.API.Services.CarService
{
    public interface ICarService
    {
        /// <summary>
        /// Получение списка всех автомобилей
        /// </summary>
        /// <param name="categoryNormalizedName">Нормализованное имя категории для фильтрации</param>
        /// <param name="pageNo">Номер страницы списка</param>
        /// <returns></returns>
        Task<ResponseData<ListModel<CarDTO>>> GetCarListAsync(string? categoryNormalizedName, int pageNo = 1, int pageSize = 3);

        /// <summary>
        /// Поиск автомобиля по Id
        /// </summary>
        /// <param name="id">Идентификатор автомобиля</param>
        /// <returns>Найденный автомобиль или null, если не найден</returns>
        Task<ResponseData<CarDTO>> GetCarByIdAsync(int id);

        /// <summary>
        /// Обновление информации об автомобиле
        /// </summary>
        /// <param name="id">Id изменяемого автомобиля</param>
        /// <param name="car">Объект автомобиля с новыми параметрами</param>
        /// <param name="formFile">Файл изображения</param>
        /// <returns></returns>
        Task<ResponseData<Car>> UpdateCarAsync(int id, Car car);

        /// <summary>
        /// Удаление автомобиля
        /// </summary>
        /// <param name="id">Id удаляемого автомобиля</param>
        /// <returns></returns>
        Task<ResponseData<string>> DeleteCarAsync(int id);

        /// <summary>
        /// Создание нового автомобиля
        /// </summary>
        /// <param name="car">Новый объект автомобиля</param>
        /// <param name="formFile">Файл изображения</param>
        /// <returns>Созданный объект</returns>
        Task<ResponseData<Car>> CreateCarAsync(Car car);
        public Task<ResponseData<string>> SaveImageAsync(int id, IFormFile formFile);
    }
}
