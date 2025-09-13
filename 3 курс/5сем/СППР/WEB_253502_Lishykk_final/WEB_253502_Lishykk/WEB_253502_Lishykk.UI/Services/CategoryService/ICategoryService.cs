using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WEB_253502_Lishykk.Domain.Entities;
using WEB_253502_Lishykk.Domain.Models;

namespace WEB_253502_Lishykk.UI.Services.CategoryService
{
    public interface ICategoryService
    {
        Task<ResponseData<List<Category>>> GetCategoryListAsync();
    }
}
