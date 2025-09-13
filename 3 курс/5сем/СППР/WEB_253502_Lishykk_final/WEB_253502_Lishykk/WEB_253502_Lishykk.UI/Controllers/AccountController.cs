using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Authentication.OpenIdConnect;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using WEB_253502_Lishykk.UI.Models;
using WEB_253502_Lishykk.UI.Services.Authentication;
using WEB_253502_Lishykk.UI.HelperClasses;

namespace WEB_253502_Lishykk.UI.Controllers
{
    public class AccountController : Controller
    {
        [HttpGet]
        public IActionResult Register()
        {
            return View(new RegisterUserViewModel());
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Register(RegisterUserViewModel user, [FromServices] IAuthService authService)
        {
            if (ModelState.IsValid)
            {
                if (user == null)
                {
                    return BadRequest();
                }

                var result = await authService.RegisterUserAsync(user.Email, user.Password, user.Avatar);
                if (result.Result)
                {
                    return RedirectToAction("Index", "Home");
                }
                else
                {
                    ModelState.AddModelError("", result.ErrorMessage);
                }
            }
            return View(user);
        }
        public async Task Login()
        {
            await HttpContext.ChallengeAsync(OpenIdConnectDefaults.AuthenticationScheme,
            new AuthenticationProperties
            {
                RedirectUri = Url.Action("Index", "Home")
            });
        }

        //[HttpPost]
        //[ValidateAntiForgeryToken]
        //public async Task<IActionResult> Logout()
        //{
        //    // Выход из куки аутентификации
        //    await HttpContext.SignOutAsync(CookieAuthenticationDefaults.AuthenticationScheme);
        //    // Выход из OpenID Connect с завершением сессии на стороне провайдера
        //    await HttpContext.SignOutAsync(OpenIdConnectDefaults.AuthenticationScheme, new AuthenticationProperties
        //    {
        //        // Убедитесь, что происходит редирект на страницу logout у провайдера
        //        RedirectUri = Url.Action("Index", "Home")
        //    });

        //    // Удаление куки
        //    Response.Cookies.Delete(".AspNetCore.Cookies");
        //    Response.Cookies.Delete("KeycloakCookie");
        //    HttpContext.Session.Clear();
        //    return RedirectToAction("Index", "Home");
        //}

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Logout()
        {
            // Выполняем локальный выход (выход из локальной куки сессии)
            await HttpContext.SignOutAsync(CookieAuthenticationDefaults.AuthenticationScheme);

            // Настраиваем выход из Keycloak
            var keycloakData = new KeycloakData
            {
                Host = "http://localhost:8080", 
                Realm = "BSUIR_LAB"
            };

            // Формируем URL для выхода из Keycloak
            var logoutUrl = $"{keycloakData.Host}/realms/{keycloakData.Realm}/protocol/openid-connect/logout";

            // Формируем URL возврата в приложение 
            var postLogoutRedirectUri = Url.Action("Index", "Home", null, Request.Scheme);

            // Удаляем куки приложения
            Response.Cookies.Delete(".AspNetCore.Cookies");
            Response.Cookies.Delete("KeycloakCookie");
            HttpContext.Session.Clear();

            // Перенаправляем на Keycloak для завершения сессии
            return Redirect($"{logoutUrl}?post_logout_redirect_uri={postLogoutRedirectUri}&client_id=LishykUiClient");
        }

    }
}
