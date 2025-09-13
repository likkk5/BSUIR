using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.Mvc.Rendering;
using WEB_253502_Lishykk.Domain.Entities;
using WEB_253502_Lishykk.UI.Services.CarService;
using WEB_253502_Lishykk.UI.Services.CategoryService;
using Microsoft.AspNetCore.Http;

namespace WEB_253502_Lishykk.UI.Areas.Admin.Pages
{
    public class CreateModel : PageModel
    {
        private readonly ICarService _carService;
        private readonly ICategoryService _categoryService;

        public CreateModel(ICarService carService, ICategoryService categoryService)
        {
            _carService = carService;
            _categoryService = categoryService;
        }

        public SelectList CategorySelectList { get; set; }

        [BindProperty]
        public Car Car { get; set; } = default!;

        [BindProperty]
        public IFormFile? ImageFile { get; set; }

        // Метод для загрузки страницы с выбором категорий
        public async Task<IActionResult> OnGetAsync()
        {
            // Получение списка категорий
            var categoryResponse = await _categoryService.GetCategoryListAsync();
            if (!categoryResponse.Successfull)
            {
                ModelState.AddModelError(string.Empty, "Не удалось загрузить категории.");
                return Page();
            }

            // Формирование выпадающего списка категорий
            CategorySelectList = new SelectList(categoryResponse.Data, "Id", "Name");
            return Page();
        }

        // Метод для обработки формы создания автомобиля
        public async Task<IActionResult> OnPostAsync()
        {
            ModelState.Remove("Car.Category");
            //ModelState.Remove("Car.ImagePath");
            //ModelState.Remove("Car.ImageMimeType");
            // Вывод ошибок валидации
            foreach (var state in ModelState)
            {
                foreach (var error in state.Value.Errors)
                {
                    Console.WriteLine($"Ошибка в поле {state.Key}: {error.ErrorMessage}");
                }
            }
            if (!ModelState.IsValid)
            {
                // Повторная загрузка категорий, если модель не валидна
                var categoryResponse = await _categoryService.GetCategoryListAsync();
                if (categoryResponse.Successfull)
                {
                    CategorySelectList = new SelectList(categoryResponse.Data, "Id", "Name");
                }
                return Page();
            }

            // Вызов метода создания автомобиля
            var response = await _carService.CreateCarAsync(Car, ImageFile);

            if (!response.Successfull)
            {
                ModelState.AddModelError(string.Empty, "Не удалось создать автомобиль.");
                return Page();
            }

            return RedirectToPage("./Index");
        }
    }
}
