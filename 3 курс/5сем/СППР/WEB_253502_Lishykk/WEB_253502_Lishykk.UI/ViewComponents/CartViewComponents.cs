using Microsoft.AspNetCore.Mvc;
using System.Threading.Tasks;
using WEB_253502_Lishykk.Domain.Entities;
using WEB_253502_Lishykk.UI.Extensions;
using WEB_253502_Lishykk.UI.Models;

namespace WEB_253502_Lishykk.UI.ViewComponents
{
    public class CartViewComponent : ViewComponent
    {
        private readonly Cart _cart;
        public CartViewComponent(Cart cart)
        {
            _cart = cart;
        }

        public IViewComponentResult Invoke()
        {
            //var cart = HttpContext.Session.GetCart();
            var model = new CartViewModel
            {
                //TotalPrice = cart.CartItems.Sum(x => x.Value.Item.Price * x.Value.Count),
                //ItemsCount = cart.Count
                TotalPrice = _cart.CartItems.Sum(x => x.Value.Item.Price * x.Value.Count),
                ItemsCount = _cart.Count
            };

            return View(model);
        }
    }

}
