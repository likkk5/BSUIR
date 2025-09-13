using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Extensions.DependencyInjection;
using WEB_253502_Lishykk.Domain.Entities;
using Microsoft.AspNetCore.Http;
using WEB_253502_Lishykk.UI.Extensions;

namespace WEB_253502_Lishykk.Domain.Entities
{
    public class SessionCart : Cart
    {
        private ISession _session;

        // Конструктор, принимающий сессию для управления данными
        public SessionCart(ISession session)
        {
            _session = session;
        }

        // Статический метод для создания объекта SessionCart с привязанной сессией
        public static SessionCart GetCart(IServiceProvider services)
        {
            var session = services.GetRequiredService<IHttpContextAccessor>()?.HttpContext.Session;
            var cart = session?.Get<SessionCart>("Cart") ?? new SessionCart(session);
            cart._session = session;
            return cart;
        }

        // Переопределение метода для добавления в корзину с сохранением в сессию
        public override void AddToCart(Car car)
        {
            base.AddToCart(car);
            SaveCart();
        }

        // Переопределение метода для удаления из корзины с сохранением в сессию
        public override void RemoveItems(int id)
        {
            base.RemoveItems(id);
            SaveCart();
        }

        // Переопределение метода для очистки корзины с сохранением в сессию
        public override void ClearAll()
        {
            base.ClearAll();
            SaveCart();
        }

        // Метод для сохранения корзины в сессию
        private void SaveCart()
        {
            _session?.Set("Cart", this);
        }
    }

}
