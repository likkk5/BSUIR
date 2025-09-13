using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _253502_Lishyk_Lab4
{
    class MyCustomComparer<T> : IComparer<T?> where T : Mammal
    {
        public int Compare(T? x, T? y)
        {
            if (x == null && y == null) return 0;
            if (x == null) return -1;
            if (y == null) return 1;

            return string.CompareOrdinal(x.Name, y.Name);
        }

    }

    //class MyCustomComparer<T> : IComparer<T> where T : Mammal
    //{
    //    public int Compare(T x, T y)
    //    {
    //        return string.Compare(x.Name, y.Name, StringComparison.OrdinalIgnoreCase);
    //    }
    //}

}
