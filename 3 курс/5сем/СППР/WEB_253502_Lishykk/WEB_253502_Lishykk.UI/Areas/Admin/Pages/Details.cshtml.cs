using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WEB_253502_Lishykk.Domain.Entities;
using WEB_253502_Lishykk.UI.Services.CarService;

namespace WEB_253502_Lishykk.UI.Areas.Admin.Pages
{
    public class DetailsModel : PageModel
    {
        private readonly ICarService _carService;

        public DetailsModel(ICarService carService)
        {
            _carService = carService;
        }

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
    }
}
