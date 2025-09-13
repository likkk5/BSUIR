using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task01.Entities
{
    public class Car
    {
        public Car(int price, bool sold, string name)
        {
            Price = price;
            Sold = sold;
            Name = name;
        }

        public int Price { get; set; }
        public bool Sold { get; set; }

        public string Name { get; set; }

        public void Deconstruct(out int price, out bool sold, out string name)
        {
            price = Price;
            sold = Sold;
            name = Name;
        }
    }
}
