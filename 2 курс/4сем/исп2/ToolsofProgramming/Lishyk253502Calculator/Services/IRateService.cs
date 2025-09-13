using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lishyk253502Calculator.Entities;

namespace Lishyk253502Calculator.Services
{
    public interface IRateService
    {
        //IEnumerable<Rate> GetRates(DateTime date);
        Task<IEnumerable<Rate>> GetRates(DateTime date);
    }
}
