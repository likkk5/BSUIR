using System.ComponentModel.DataAnnotations;
namespace WEB_253502_Lishykk.BlazorWasm.Models
{
    public class Cart
    {
        public Dictionary<int, CartItem> Items { get; set; } = new();

        public void AddItem(Car car)
        {
            if (Items.ContainsKey(car.Id))
                Items[car.Id].Count++;
            else
                Items.Add(car.Id, new CartItem { Item = car, Count = 1 });
        }

        public void RemoveItem(int id)
        {
            if (!Items.ContainsKey(id)) return;

            Items[id].Count--;
            if (Items[id].Count <= 0)
                Items.Remove(id);
        }

        public void Clear() => Items.Clear();

        public int TotalCount => Items.Sum(i => i.Value.Count);
        public decimal TotalPrice => Items.Sum(i => i.Value.Item.Price * i.Value.Count);
    }
}
