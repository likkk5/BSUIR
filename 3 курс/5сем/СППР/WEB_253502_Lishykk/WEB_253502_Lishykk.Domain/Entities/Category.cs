using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;
using WEB_253502_Lishykk.Domain.Entities;

namespace WEB_253502_Lishykk.Domain.Entities
{
    public class Category
    {
        public int Id { get; set; } // Уникальный идентификатор категории
        public string Name { get; set; } // Название категории
        public string NormalizedName { get; set; } // Название категории в нотации kebab для фильтрации
        [JsonIgnore]
        public List<Car> Cars { get; set; } // Список автомобилей, принадлежащих данной категории
    }
}
