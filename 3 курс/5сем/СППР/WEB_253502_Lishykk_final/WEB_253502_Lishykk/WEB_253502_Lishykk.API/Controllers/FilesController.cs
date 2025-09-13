using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Hosting;
using System.IO;
using System.Threading.Tasks;

namespace WEB_253502_Lishykk.API.Controllers
{

    [Route("api/[controller]")]
    [ApiController]
    public class FilesController : ControllerBase
    {
        // Путь к папке wwwroot/Images
        private readonly string _imagePath;

        public FilesController(IWebHostEnvironment webHost)
        {
            _imagePath = Path.Combine(webHost.WebRootPath, "Images");
        }

        [HttpPost]
        public async Task<IActionResult> SaveFile(IFormFile file)
        {
            if (file is null)
            {
                return BadRequest("File is null");
            }

            // путь к сохраняемому файлу
            var filePath = Path.Combine(_imagePath, file.FileName);
            var fileInfo = new FileInfo(filePath);

            // если такой файл существует, удалить его
            if (fileInfo.Exists)
            {
                fileInfo.Delete();
            }

            // копировать файл в поток
            using var fileStream = fileInfo.Create();
            await file.CopyToAsync(fileStream);

            // получить Url файла
            var host = HttpContext.Request.Host;
            var fileUrl = $"https://{host}/Images/{file.FileName}";

            return Ok(fileUrl);
        }

        [HttpDelete("{fileName}")]
        public IActionResult DeleteFile(string fileName)
        {
            var filePath = Path.Combine(_imagePath, fileName);
            var fileInfo = new FileInfo(filePath);

            if (fileInfo.Exists)
            {
                fileInfo.Delete();
                return Ok();
            }
            return NotFound("File not found");
        }
    }


}
