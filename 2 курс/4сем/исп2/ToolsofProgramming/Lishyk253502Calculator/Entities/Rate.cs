using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lishyk253502Calculator.Entities
{
    public class Rate
    {
        public string? Cur_Abbreviation { get; set; }
        public double Cur_OfficialRate { get; set; }

        public override string ToString()
        {
            return $"{Cur_Abbreviation} - {Cur_OfficialRate}";
        }
    }
}
