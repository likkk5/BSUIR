using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WEB_253502_Lishykk.Domain.Entities;
using WEB_253502_Lishykk.Domain.Models;
using WEB_253502_Lishykk.UI.Services.CategoryService;

namespace WEB_253502_Lishykk.UI.Services.CategoryService
{
    public class MemoryCategoryService : ICategoryService
    {
        public Task<ResponseData<List<Category>>> GetCategoryListAsync()
        {
            var categories = new List<Category>
            {
                new Category { Id = 1, Name = "SUV", NormalizedName = "suv" },
                new Category { Id = 2, Name = "Sedan", NormalizedName = "sedan" },
                new Category { Id = 3, Name = "Hatchback", NormalizedName = "hatchback" },
                new Category { Id = 4, Name = "Coupe", NormalizedName = "coupe" },
                new Category { Id = 5, Name = "Truck", NormalizedName = "truck" }, 
                new Category { Id = 6, Name = "Convertible", NormalizedName = "convertible" } 
            };

            var result = ResponseData<List<Category>>.Success(categories);
            return Task.FromResult(result);
        }
    }
}
