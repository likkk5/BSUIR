using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WEB_253502_Lishykk.Domain.Models
{
    public class ListModel<T>
    {
        // Запрошенный список объектов
        public List<T> Items { get; set; } = new();

        // Номер текущей страницы
        public int CurrentPage { get; set; } = 1;

        // Общее количество страниц
        public int TotalPages { get; set; } = 1;
    }
}
