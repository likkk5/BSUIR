using System;
using System.Linq;
using OpenQA.Selenium;
using OpenQA.Selenium.Firefox;
using OpenQA.Selenium.Support.UI;

class UsabilityTesting
{
    static void Main(string[] args)
    {
        var driverService = FirefoxDriverService.CreateDefaultService(@"C:\Users\lishy\Downloads\geckodriver-v0.35.0-win64");
        driverService.HideCommandPromptWindow = true; // Скрывает консоль geckodriver

        var options = new FirefoxOptions();
        options.AddArgument("--start-maximized"); // Полноэкранный режим

        IWebDriver driver = new FirefoxDriver(driverService, options);

        try
        {
            // Открываем сайт ТГУ
            driver.Navigate().GoToUrl("https://www.tsu.ru/");
            WebDriverWait wait = new WebDriverWait(driver, TimeSpan.FromSeconds(10));
            wait.Until(d => d.FindElement(By.TagName("body")));

            Console.WriteLine("Сайт успешно открыт для тестирования юзабилити.");

            // === Проверка навигации ===
            TestNavigation(driver);

            // === Проверка качества контента ===
            TestContent(driver);

            // === Проверка поиска по сайту ===
            TestSearchFunctionality(driver);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка: {ex.Message}");
        }
        finally
        {
            // Закрываем браузер
            driver.Quit();
        }
    }

    static void TestNavigation(IWebDriver driver)
    {
        Console.WriteLine("=== Проверка навигации ===");

        // Проверка доступности главного меню на всех страницах
        try
        {
            var menu = driver.FindElement(By.ClassName("main-menu")); // Замените на актуальный класс/ID меню
            Console.WriteLine("Главное меню доступно на главной странице.");

            // Переход по нескольким ссылкам из меню
            var menuItems = menu.FindElements(By.TagName("a"));

            foreach (var item in menuItems)
            {
                Console.WriteLine($"Проверка пункта меню: {item.Text}");
                item.Click();

                // Убедимся, что после перехода меню остается доступным
                if (driver.FindElements(By.ClassName("main-menu")).Count > 0)
                {
                    Console.WriteLine($"Меню доступно на странице {driver.Url}");
                }
                else
                {
                    Console.WriteLine($"Меню недоступно на странице {driver.Url}");
                }

                // Возвращаемся на главную страницу для дальнейших тестов
                driver.Navigate().Back();
            }
        }
        catch (NoSuchElementException)
        {
            Console.WriteLine("Главное меню не найдено.");
        }
    }

    static void TestContent(IWebDriver driver)
    {
        Console.WriteLine("=== Проверка качества контента ===");

        // Проверка наличия заголовков
        var headings = driver.FindElements(By.TagName("h1"));
        if (headings.Count > 0)
        {
            Console.WriteLine($"Найдено {headings.Count} заголовков H1.");
        }
        else
        {
            Console.WriteLine("Заголовки H1 отсутствуют.");
        }

        // Проверка наличия ошибок в тексте
        if (driver.PageSource.Contains("ошибка") || driver.PageSource.Contains("404"))
        {
            Console.WriteLine("На странице найдены ошибки.");
        }
        else
        {
            Console.WriteLine("Ошибки на странице не обнаружены.");
        }

        // Проверка цвета текста и фона (пример для CSS)
        var body = driver.FindElement(By.TagName("body"));
        string backgroundColor = body.GetCssValue("background-color");
        string textColor = body.GetCssValue("color");

        Console.WriteLine($"Цвет фона страницы: {backgroundColor}");
        Console.WriteLine($"Цвет текста: {textColor}");

        // Вывод предупреждения, если цвета не соответствуют стандартам
        if (backgroundColor == "rgb(0, 0, 0)" || textColor == "rgb(255, 255, 255)")
        {
            Console.WriteLine("Внимание: Темная тема может быть неудобной для пользователей.");
        }
    }

    static void TestSearchFunctionality(IWebDriver driver)
    {
        Console.WriteLine("=== Проверка поиска по сайту ===");

        try
        {
            // Найдите строку поиска
            var searchInput = driver.FindElement(By.Name("q")); // Замените на актуальный Name/ID
            var searchButton = driver.FindElement(By.CssSelector("button[type='submit']"));

            // Выполните поиск
            searchInput.SendKeys("образование");
            searchButton.Click();

            // Ожидаем результатов
            WebDriverWait wait = new WebDriverWait(driver, TimeSpan.FromSeconds(10));
            wait.Until(d => d.FindElement(By.ClassName("search-results"))); // Замените на актуальный класс

            // Проверка, что результаты поиска найдены
            var results = driver.FindElements(By.ClassName("result-item")); // Замените на актуальный класс
            if (results.Count > 0)
            {
                Console.WriteLine($"Найдено {results.Count} результатов поиска.");
            }
            else
            {
                Console.WriteLine("Результаты поиска не найдены.");
            }
        }
        catch (NoSuchElementException)
        {
            Console.WriteLine("Строка поиска или результаты не найдены.");
        }
    }
}
