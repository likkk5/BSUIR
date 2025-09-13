using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.AspNetCore.Http;
using WEB_253502_Lishykk.Domain.Entities;
using WEB_253502_Lishykk.UI.Services.CarService;
using WEB_253502_Lishykk.UI.Services.CategoryService;

namespace WEB_253502_Lishykk.UI.Areas.Admin.Pages
{
    public class EditModel : PageModel
    {
        private readonly ICarService _carService;
        private readonly ICategoryService _categoryService;

        public EditModel(ICarService carService, ICategoryService categoryService)
        {
            _carService = carService;
            _categoryService = categoryService;
        }

        [BindProperty]
        public Car Car { get; set; } = default!;

        [BindProperty]
        public IFormFile? ImageFile { get; set; }

        public async Task<IActionResult> OnGetAsync(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var response = await _carService.GetCarByIdAsync(id.Value);
            if (!response.Successfull || response.Data == null)
            {
                return NotFound();
            }

            Car = response.Data;
            var categories = await _categoryService.GetCategoryListAsync();
            ViewData["CategoryId"] = new SelectList(categories.Data, "Id", "Name");
            return Page();
        }

        public async Task<IActionResult> OnPostAsync()
        {
            ModelState.Remove("Car.Category");
            ModelState.Remove("Car.ImagePath");
            ModelState.Remove("Car.ImageMimeType");
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
                var categories = await _categoryService.GetCategoryListAsync();
                ViewData["CategoryId"] = new SelectList(categories.Data, "Id", "Name");
                return Page();
            }

            var result = await _carService.UpdateCarAsync(Car.Id, Car, ImageFile);
            if (!result.Successfull)
            {
                ModelState.AddModelError(string.Empty, "Не удалось обновить данные автомобиля.");

                var categories = await _categoryService.GetCategoryListAsync();
                ViewData["CategoryId"] = new SelectList(categories.Data, "Id", "Name");
                return Page();
            }

            return RedirectToPage("./Index");
        }
    }
}
