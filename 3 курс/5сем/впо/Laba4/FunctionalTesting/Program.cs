using System;
using System.Collections.Generic;
using System.Linq;
using OpenQA.Selenium;
using OpenQA.Selenium.Firefox;
using OpenQA.Selenium.Support.UI;

class FunctionalTesting
{
    static void Main(string[] args)
    {
        // Настройки Firefox WebDriver
        //var options = new FirefoxOptions();
        //options.AddArgument("--start-maximized"); // Полноэкранный режим
        //IWebDriver driver = new FirefoxDriver(options);

        var driverService = FirefoxDriverService.CreateDefaultService(@"C:\Users\lishy\Downloads\geckodriver-v0.35.0-win64");
        driverService.HideCommandPromptWindow = true; // Скрывает консоль geckodriver

        var options = new FirefoxOptions();
        options.AddArgument("--start-maximized");

        IWebDriver driver = new FirefoxDriver(driverService, options);


        try
        {
            // === Открываем сайт ТГУ ===
            driver.Navigate().GoToUrl("https://www.tsu.ru/");
            WebDriverWait wait = new WebDriverWait(driver, TimeSpan.FromSeconds(10));
            wait.Until(d => d.FindElement(By.TagName("body")));

            Console.WriteLine("Сайт открыт успешно.");

            // === Проверка всех ссылок ===
            TestAllLinks(driver);

            // === Проверка формы входа/обратной связи ===
            TestForms(driver);

            // === Тестирование cookies ===
            TestCookies(driver);

            // === Проверка HTML/CSS ===
            TestHtmlCss(driver);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка: {ex.Message}");
        }
        finally
        {
            // Закрытие браузера
            driver.Quit();
        }
    }

    static void TestAllLinks(IWebDriver driver)
    {
        Console.WriteLine("=== Проверка всех ссылок на сайте ===");

        var links = driver.FindElements(By.TagName("a"));
        Console.WriteLine($"Найдено {links.Count} ссылок.");

        foreach (var link in links)
        {
            string href = link.GetAttribute("href");

            if (!string.IsNullOrEmpty(href) && Uri.IsWellFormedUriString(href, UriKind.Absolute))
            {
                Console.WriteLine($"Проверка ссылки: {href}");

                try
                {
                    driver.Navigate().GoToUrl(href);
                    if (driver.Title.Contains("404") || driver.PageSource.Contains("404"))
                    {
                        Console.WriteLine($"Битая ссылка: {href}");
                    }
                    else
                    {
                        Console.WriteLine($"Ссылка работает корректно: {href}");
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Ошибка при проверке ссылки {href}: {ex.Message}");
                }
            }
        }

        // Возвращаемся на главную страницу
        driver.Navigate().GoToUrl("https://www.tsu.ru/");
    }

    static void TestForms(IWebDriver driver)
    {
        Console.WriteLine("=== Тестирование форм ===");

        try
        {
            // Найдите ссылку на страницу с формой, если доступно (например, "Обратная связь")
            var feedbackLink = driver.FindElement(By.LinkText("Обратная связь")); // Замените на текст ссылки
            feedbackLink.Click();

            // Найдите поля формы
            var nameField = driver.FindElement(By.Id("name")); // Замените на реальный ID
            var emailField = driver.FindElement(By.Id("email")); // Замените на реальный ID
            var messageField = driver.FindElement(By.Id("message")); // Замените на реальный ID
            var submitButton = driver.FindElement(By.CssSelector("button[type='submit']"));

            // Тест: вводим данные
            nameField.SendKeys("Тестовый пользователь");
            emailField.SendKeys("invalid_email"); // Тестируем некорректный ввод
            messageField.SendKeys("Это тестовое сообщение.");
            submitButton.Click();

            // Проверка сообщения об ошибке валидации
            var errorMessage = driver.FindElements(By.ClassName("error-message")); // Реальный класс замените
            if (errorMessage.Any())
            {
                Console.WriteLine($"Ошибка валидации: {errorMessage.First().Text}");
            }
            else
            {
                Console.WriteLine("Форма успешно отправлена или нет сообщений об ошибке.");
            }
        }
        catch (NoSuchElementException)
        {
            Console.WriteLine("Форма не найдена.");
        }
    }

    static void TestCookies(IWebDriver driver)
    {
        Console.WriteLine("=== Тестирование cookies ===");

        // Получаем все cookies
        var cookies = driver.Manage().Cookies.AllCookies;
        Console.WriteLine($"Найдено cookies: {cookies.Count}");

        foreach (var cookie in cookies)
        {
            Console.WriteLine($"Cookie: {cookie.Name} = {cookie.Value}");
        }

        // Удаляем все cookies и проверяем
        driver.Manage().Cookies.DeleteAllCookies();
        cookies = driver.Manage().Cookies.AllCookies;

        if (cookies.Count == 0)
        {
            Console.WriteLine("Все cookies удалены успешно.");
        }
        else
        {
            Console.WriteLine("Ошибка при удалении cookies.");
        }
    }

    static void TestHtmlCss(IWebDriver driver)
    {
        Console.WriteLine("=== Проверка HTML/CSS ===");

        // Пример: проверка наличия мета-тега description
        var metaTags = driver.FindElements(By.TagName("meta"));
        var descriptionTag = metaTags.FirstOrDefault(meta => meta.GetAttribute("name") == "description");

        if (descriptionTag != null)
        {
            Console.WriteLine($"Meta description найден: {descriptionTag.GetAttribute("content")}");
        }
        else
        {
            Console.WriteLine("Meta description отсутствует.");
        }

        // Проверка на ошибки в HTML-коде (на основе текста страницы)
        if (driver.PageSource.Contains("error") || driver.PageSource.Contains("invalid"))
        {
            Console.WriteLine("Найдены ошибки в HTML.");
        }
        else
        {
            Console.WriteLine("Ошибки в HTML не найдены.");
        }
    }
}
