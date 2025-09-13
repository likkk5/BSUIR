//$(document).ready(function () {
//    // Подписка на клики по элементам пагинации
//    $(document).on("click", ".pagination .page-link", function (event) {
//        event.preventDefault();
//        var page = $(this).data("page");
//        //var category = $('#carCatalog').data('category'); // Получаем категорию
//        // Если текущая категория - "All", то передаем null
//        var category = $('#carCatalog').data('category') === 'All' ? null : $('#carCatalog').data('category');
//        console.log("Page:", page, "Category:", category); // Логируем для отладки
//        if (page) {
//            loadPage(page); // Загружаем данные для выбранной страницы
//        }
//    });


//    function loadPage(pageNo) {
//        var category = $('#carCatalog').data('category'); // Используем data-атрибут
//        console.log("Loading page:", pageNo, "with category:", category); // Логируем параметры запроса
//        $.ajax({
//            url: '/Car', // URL для AJAX-запроса
//            type: 'GET',
//            data: {
//                category: category,
//                pageNo: pageNo // Передаем номер страницы
//            },
//            success: function (data) {
//                console.log(data); // Отладка: проверяем, что возвращается от сервера
//                $("#carCatalog").html(data); // Обновляем содержимое
//            },
//            error: function () {
//                alert("Error loading page.");
//            }
//        });
//    }

//});
document.querySelectorAll('.add-to-cart-btn').forEach(function (button) {
    button.addEventListener('click', function () {
        this.classList.add('btn-secondary');
        this.classList.remove('btn-success');
        this.innerHTML = '<i class="fa fa-check"></i> Added';
    });
});