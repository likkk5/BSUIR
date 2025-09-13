using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SQLite;

namespace Lishyk253502Calculator.Entities
{
    [Table("SushiSets")]
    public class SushiSetEntity
    {
        [PrimaryKey, AutoIncrement, Indexed] //атрибут указывает, что поле является первичным ключом и автоматически увеличивается при добавлении новой записи
        public int Id { get; set; }

        public string Name { get; set; }
    }
    //PrimaryKey(первичный ключ) – это уникальный идентификатор записи в таблице базы данных
}
