namespace WEB_253502_Lishykk.API.Models
{
    public class CarDTO
    {
        public int Id { get; set; }  // Идентификатор автомобиля
        public string Name { get; set; }  // Название автомобиля
        public string Description { get; set; }  // Описание автомобиля
        public int? CategoryId { get; set; }  // Идентификатор категории
        public decimal Price { get; set; }  // Цена автомобиля
        public string ImagePath { get; set; }  // Полный URL к изображению
        public string ImageMimeType { get; set; }  // MIME-тип изображения
        public object Category { get; set; } = null;  // Категория будет null
    }
}
