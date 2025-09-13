using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using WEB_253502_Lishykk.Domain.Entities;
using WEB_253502_Lishykk.UI.Extensions;
using WEB_253502_Lishykk.UI.Services.CarService;

namespace WEB_253502_Lishykk.UI.Controllers
{
    [Authorize]
    public class CartController : Controller
    {
        private readonly ICarService _carService;
        private readonly Cart _cart;
        public CartController(ICarService carService, Cart cart)
        {
            _carService = carService;
            _cart = cart;
        }

        // Добавление товара в корзину
        [Route("[controller]/add/{id:int}")]
        public async Task<ActionResult> Add(int id, string returnUrl)
        {
            // Получаем корзину из сессии
            //var cart = HttpContext.Session.GetCart();

            var carResponse = await _carService.GetCarByIdAsync(id);
            if (carResponse.Successfull)
            {
                // Добавляем объект в корзину
                //cart.AddToCart(carResponse.Data);
                //HttpContext.Session.SetCart(cart); // Сохраняем корзину в сессии
                _cart.AddToCart(carResponse.Data); // Теперь работа с корзиной через DI
            }

            //if (string.IsNullOrEmpty(returnUrl))
            //{
            //    return RedirectToAction("Index", "Cart");
            //}
            //return Redirect(returnUrl);
            return RedirectToAction("Index", "Cart");
        }

        // Удаление товара из корзины
        [Route("[controller]/remove/{id:int}")]
        public ActionResult Remove(int id, string returnUrl)
        {
            //var cart = HttpContext.Session.GetCart();
            //cart.RemoveItems(id);
            //HttpContext.Session.SetCart(cart); // Обновляем корзину в сессии
            _cart.RemoveItems(id);

            return RedirectToAction("Index", "Cart");
        }

        // Просмотр корзины
        [HttpGet]
        public IActionResult Index()
        {
            //var cart = HttpContext.Session.GetCart();
            return View(_cart);
        }

        // Очистка корзины
        [Route("[controller]/clear")]
        public IActionResult Clear(string returnUrl)
        {
            //var cart = HttpContext.Session.GetCart();
            //cart.ClearAll();
            //HttpContext.Session.SetCart(cart);
            // Используем DI корзину для очистки
            _cart.ClearAll(); // Очистка текущей корзины
            HttpContext.Session.SetCart(_cart); // Сохраняем очищенную корзину в сессии
            return RedirectToAction("Index", "Cart");
        }
    }

}
