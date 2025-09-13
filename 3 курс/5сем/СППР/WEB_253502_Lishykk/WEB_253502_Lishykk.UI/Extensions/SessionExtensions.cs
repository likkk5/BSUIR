using Newtonsoft.Json;
using WEB_253502_Lishykk.Domain.Entities;

namespace WEB_253502_Lishykk.UI.Extensions
{
    public static class SessionExtensions
    {
        private const string CartSessionKey = "cart";

        // Метод для сохранения объекта в сессии
        public static void Set<T>(this ISession session, string key, T value)
        {
            session.SetString(key, JsonConvert.SerializeObject(value));
        }

        // Метод для получения объекта из сессии
        public static T Get<T>(this ISession session, string key)
        {
            var value = session.GetString(key);
            return value == null ? default : JsonConvert.DeserializeObject<T>(value);
        }

        public static Cart GetCart(this ISession session)
        {
            return session.Get<Cart>(CartSessionKey) ?? new Cart();
        }

        public static void SetCart(this ISession session, Cart cart)
        {
            session.Set(CartSessionKey, cart);
        }
    }

}
