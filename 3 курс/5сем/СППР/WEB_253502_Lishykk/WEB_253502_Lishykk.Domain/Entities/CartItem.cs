using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WEB_253502_Lishykk.Domain.Entities;

namespace WEB_253502_Lishykk.Domain.Entities
{
    public class CartItem
    {
        public Car Item { get; set; }  // Объект, например, автомобиль
        public int Count { get; set; } // Количество объектов
    }
}
