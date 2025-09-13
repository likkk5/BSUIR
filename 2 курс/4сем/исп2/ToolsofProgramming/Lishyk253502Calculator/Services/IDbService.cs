using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lishyk253502Calculator.Entities;

namespace Lishyk253502Calculator.Services
{
    public interface IDbService
    {
        IEnumerable<SushiSetEntity> GetAllSushiSets();
        IEnumerable<SushiEntity> GetSushisInSet(int sushiSetId);
        void Init();
        void ClearDatabase();
    }
}
