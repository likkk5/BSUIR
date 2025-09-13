using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WEB_253502_Lishykk.Domain.Entities;

namespace WEB_253502_Lishykk.Domain.Entities
{
    public class Car
    {
        public int Id { get; set; } // Уникальный идентификатор автомобиля
        public string Name { get; set; } // Название автомобиля
        public string Description { get; set; } // Дополнительное описание автомобиля
        public Category? Category { get; set; } // Категория автомобиля
        public decimal Price { get; set; } // Цена автомобиля
        public string? ImagePath { get; set; } // Путь к изображению автомобиля
        public string? ImageMimeType { get; set; } // MIME тип изображения
        public int? CategoryId { get; set; }
    }
}
