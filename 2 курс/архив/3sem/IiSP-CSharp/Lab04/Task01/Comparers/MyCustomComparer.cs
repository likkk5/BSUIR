using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Task01.Entities;

namespace Task01.Comparers
{
    public class MyCustomComparer : IComparer<Car>
    {
        public int Compare(Car? x, Car? y)
        {
            return string.Compare(x.Name, y.Name);
        }
    }
}
