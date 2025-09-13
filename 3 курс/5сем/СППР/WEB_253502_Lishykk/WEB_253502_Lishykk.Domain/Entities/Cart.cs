using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WEB_253502_Lishykk.Domain.Entities;

namespace WEB_253502_Lishykk.Domain.Entities
{
        public class Cart
        {
            // Список объектов в корзине, где ключ — это ID объекта
            public Dictionary<int, CartItem> CartItems { get; set; } = new();

            // Метод для добавления объекта в корзину
            public virtual void AddToCart(Car car)
            {
                if (CartItems.ContainsKey(car.Id))
                {
                    CartItems[car.Id].Count++;
                }
                else
                {
                    CartItems[car.Id] = new CartItem { Item = car, Count = 1 };
                }
            }

            // Метод для удаления объекта из корзины
            public virtual void RemoveItems(int id)
            {
                if (CartItems.ContainsKey(id))
                {
                    CartItems[id].Count--;

                    if (CartItems[id].Count <= 0)
                    {
                        CartItems.Remove(id);
                    }
                }
            }

            // Метод для очистки корзины
            public virtual void ClearAll()
            {
                CartItems.Clear();
            }

            // Общее количество объектов в корзине
            public int Count => CartItems.Sum(item => item.Value.Count);

            // Общее количество калорий (или другая характеристика)
            //public double TotalCalories => CartItems.Sum(item => item.Value.Item.Calories * item.Value.Count);
        }

}
