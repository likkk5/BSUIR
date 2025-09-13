using Microsoft.EntityFrameworkCore;
using WEB_253502_Lishykk.API.Data;
using WEB_253502_Lishykk.Domain.Entities;
using WEB_253502_Lishykk.Domain.Models;

namespace WEB_253502_Lishykk.API.Services.CategoryService
{
    public class CategoryService(AppDbContext _context) : ICategoryService
    {
        public async Task<ResponseData<List<Category>>> GetCategoryListAsync()
        {
            var query = await _context.Categories.ToListAsync();
            return ResponseData<List<Category>>.Success(query);
        }
    }
}
