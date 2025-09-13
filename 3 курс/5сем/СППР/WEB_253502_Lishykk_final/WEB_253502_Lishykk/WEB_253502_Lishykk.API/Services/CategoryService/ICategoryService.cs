using WEB_253502_Lishykk.Domain.Entities;
using WEB_253502_Lishykk.Domain.Models;

namespace WEB_253502_Lishykk.API.Services.CategoryService
{
    public interface ICategoryService
    {
        Task<ResponseData<List<Category>>> GetCategoryListAsync();
    }
}
