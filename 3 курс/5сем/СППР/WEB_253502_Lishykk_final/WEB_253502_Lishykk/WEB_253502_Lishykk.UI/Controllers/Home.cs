using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using System.Collections.Generic;
using WEB_253502_Lishykk.UI.Models;

namespace WEB_253502_Lishykk.UI.Controllers
{

    public class HomeController : Controller
    {
        public IActionResult Index()
        {
            // Используем ViewData для передачи заголовка
            ViewData["Title"] = "Лабораторная работа №2";

            // Создание списка элементов для select
            var items = new List<ListDemo>
            {
                new ListDemo { Id = 1, Name = "Item 1" },
                new ListDemo { Id = 2, Name = "Item 2" },
                new ListDemo { Id = 3, Name = "Item 3" }
            };

            // Передача списка через SelectList
            ViewBag.SelectList = new SelectList(items, "Id", "Name");

            return View();
        }

        [HttpPost]
        public IActionResult SubmitForm(int selectedItem)
        {
            // Обработка выбранного элемента
            return Content($"Вы выбрали элемент с ID: {selectedItem}");
        }

        [Route("/submit-form")]
        [HttpPost]
        public IActionResult SubmitForm(string inputLogin, string inputPassword, bool gridCheck1, bool gridCheck2, string gridRadios)
        {
            return Content("Форма успешно отправлена");
        }

    }
}
