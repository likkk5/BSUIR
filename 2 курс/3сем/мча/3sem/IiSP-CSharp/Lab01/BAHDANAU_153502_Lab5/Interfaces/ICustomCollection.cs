using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BAHDANAU_153502_Lab5.Interfaces
{
    public interface ICustomCollection<T>
    {
        public T this[int index] { get; set; }
        public void Add(T item);
        public void Remove(T item);
        public void Reset();
        public void Next();
        public T Current();
        public int Count { get; }
        public T RemoveCurrent();
    }
}
