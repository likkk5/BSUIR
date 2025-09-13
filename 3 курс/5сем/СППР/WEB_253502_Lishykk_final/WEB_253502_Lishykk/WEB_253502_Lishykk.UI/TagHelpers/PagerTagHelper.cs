using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.AspNetCore.Razor.TagHelpers;
using Microsoft.AspNetCore.Routing;
namespace WEB_253502_Lishykk.UI.Extensions
{
    [HtmlTargetElement("pager", Attributes = "current-page,total-pages")]
    public class PagerTagHelper : TagHelper
    {
        private readonly LinkGenerator _linkGenerator;
        private readonly IHttpContextAccessor _httpContextAccessor;

        public PagerTagHelper(LinkGenerator linkGenerator, IHttpContextAccessor httpContextAccessor)
        {
            _linkGenerator = linkGenerator;
            _httpContextAccessor = httpContextAccessor;
        }

        [HtmlAttributeName("current-page")]
        public int CurrentPage { get; set; }

        [HtmlAttributeName("total-pages")]
        public int TotalPages { get; set; }

        [HtmlAttributeName("category")]
        public string? Category { get; set; }

        [HtmlAttributeName("admin")]
        public bool Admin { get; set; }

        public override void Process(TagHelperContext context, TagHelperOutput output)
        {
            // Устанавливаем тег <nav>
            output.TagName = "nav";
            output.TagMode = TagMode.StartTagAndEndTag;

            // Создаем <ul> с классом "pagination"
            var ulTag = new TagBuilder("ul");
            ulTag.AddCssClass("pagination");

            // Кнопка "Previous"
            if (CurrentPage > 1)
            {
                var prevLiTag = CreatePageItem(CurrentPage - 1, "Previous", false);
                ulTag.InnerHtml.AppendHtml(prevLiTag);
            }

            // Генерация страниц
            for (int i = 1; i <= TotalPages; i++)
            {
                var liTag = CreatePageItem(i, i.ToString(), i == CurrentPage);
                ulTag.InnerHtml.AppendHtml(liTag);
            }

            // Кнопка "Next"
            if (CurrentPage < TotalPages)
            {
                var nextLiTag = CreatePageItem(CurrentPage + 1, "Next", false);
                ulTag.InnerHtml.AppendHtml(nextLiTag);
            }

            output.Content.AppendHtml(ulTag);
        }

        // Метод для создания элемента пагинации
        private TagBuilder CreatePageItem(int pageNumber, string text, bool isActive)
        {
            var liTag = new TagBuilder("li");
            liTag.AddCssClass("page-item");
            if (isActive) liTag.AddCssClass("active");

            var aTag = new TagBuilder("a");
            aTag.AddCssClass("page-link");

            // Генерация ссылки в зависимости от режима (Admin или обычный)
            string href;
            if (Admin)
            {
                href = $"/Admin/Index?pageNo={pageNumber}&category={Category}";
            }
            else
            {
                href = _linkGenerator.GetPathByAction(
                    action: "Index",
                    controller: "Car",
                    values: new { pageNo = pageNumber, category = Category }
                );
            }

            aTag.Attributes.Add("href", href);
            aTag.Attributes.Add("data-page", pageNumber.ToString()); // Добавляем data-page атрибут
            aTag.InnerHtml.Append(text);

            liTag.InnerHtml.AppendHtml(aTag);

            return liTag;
        }

    }
}