using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WEB_253502_Lishykk.Domain.Entities;
using WEB_253502_Lishykk.UI.Services.CarService;

namespace WEB_253502_Lishykk.UI.Areas.Admin.Pages
{
    public class DeleteModel : PageModel
    {
        private readonly ICarService _carService;

        public DeleteModel(ICarService carService)
        {
            _carService = carService;
        }

        [BindProperty]
        public Car Car { get; set; } = default!;

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
            return Page();
        }

        public async Task<IActionResult> OnPostAsync(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var deleteResult = await _carService.DeleteCarAsync(id.Value);
            if (!deleteResult.Successfull)
            {
                ModelState.AddModelError(string.Empty, "Не удалось удалить автомобиль.");
                return Page();
            }

            return RedirectToPage("./Index");
        }
    }
}
