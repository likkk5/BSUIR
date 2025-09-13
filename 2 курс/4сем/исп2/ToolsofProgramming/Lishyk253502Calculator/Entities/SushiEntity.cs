using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SQLite;

namespace Lishyk253502Calculator.Entities
{
    [Table("Sushis")]
    public class SushiEntity
    {
        [PrimaryKey, AutoIncrement, Indexed]
        public int Id { get; set; }

        public string Name { get; set; }

        [Indexed]
        public int SushiSetId { get; set; }
    }
}
