using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WEB_253502_Lishykk.Domain.Entities;
using WEB_253502_Lishykk.UI.Services.CarService;
using WEB_253502_Lishykk.UI.Services.CategoryService; // Добавьте этот using
using WEB_253502_Lishykk.Domain.Models;
using Microsoft.AspNetCore.Mvc.Rendering; // Для SelectList

namespace WEB_253502_Lishykk.UI.Areas.Admin.Pages
{
    public class IndexModel : PageModel
    {
        private readonly ICarService _carService;
        private readonly ICategoryService _categoryService; 

        public IndexModel(ICarService carService, ICategoryService categoryService)
        {
            _carService = carService;
            _categoryService = categoryService; 
        }

        public List<Car> Car { get; set; } = new List<Car>();
        public ListModel<Car>? CarListModel { get; set; }

        public int PageNo { get; set; } = 1; // Текущая страница
        public string? CurrentCategory { get; set; }
        public List<Category> Categories { get; set; } = new List<Category>();

        public async Task OnGetAsync(int? pageNo, string? category)
        {
            // Если номер страницы передан, устанавливаем его
            if (pageNo.HasValue && pageNo.Value > 0)
            {
                PageNo = pageNo.Value;
            }
            // Сохраняем текущую категорию
            CurrentCategory = category;

            // Получаем список автомобилей через ICarService с фильтрацией по категории
            var response = await _carService.GetCarListAsync(category, PageNo);

            if (response.Successfull)
            {
                CarListModel = response.Data;
                Car = CarListModel.Items;
            }
            else
            {
                ModelState.AddModelError(string.Empty, "Не удалось загрузить список автомобилей.");
            }

            // Получение списка категорий
            var categoryResponse = await _categoryService.GetCategoryListAsync();
            if (categoryResponse.Successfull)
            {
                Categories = categoryResponse.Data;
            }
            else
            {
                ModelState.AddModelError(string.Empty, "Не удалось загрузить категории.");
            }

            // Устанавливаем текущее значение категории для использования в представлении
            ViewData["currentCategory"] = string.IsNullOrEmpty(category) ? "All" : category;
        
        }
    }
}
