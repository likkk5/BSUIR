using OpenQA.Selenium;
using OpenQA.Selenium.Firefox;
using System;

class SecurityTesting
{
    static void Main(string[] args)
    {
        while (true)
        {
            Console.WriteLine("\nВыберите сценарий тестирования безопасности:");
            Console.WriteLine("1: Проверка URL-доступа без авторизации");
            Console.WriteLine("2: Проверка изменения ID в URL");
            Console.WriteLine("3: Ввод неверных данных в форму авторизации");
            Console.WriteLine("4: Проверка недоступности каталогов и файлов");
            Console.WriteLine("5: Проверка SSL");
            Console.WriteLine("0: Выход");
            Console.Write("Введите номер сценария: ");

            string choice = Console.ReadLine();

            switch (choice)
            {
                case "1":
                    TestUnauthorizedAccess();
                    break;
                case "2":
                    TestURLIDChange();
                    break;
                case "3":
                    TestInvalidLogin();
                    break;
                case "4":
                    TestDirectoryAccess();
                    break;
                case "5":
                    TestSSLRedirection();
                    break;
                case "0":
                    Console.WriteLine("Завершение программы.");
                    return;
                default:
                    Console.WriteLine("Некорректный выбор. Попробуйте снова.");
                    break;
            }
        }
    }

    static void TestUnauthorizedAccess()
    {
        //using var driver = new FirefoxDriver();
        var driverService = FirefoxDriverService.CreateDefaultService(@"C:\Users\lishy\Downloads\geckodriver-v0.35.0-win64");
        driverService.HideCommandPromptWindow = true; // Скрывает консоль geckodriver

        var options = new FirefoxOptions();
        options.AddArgument("--start-maximized"); // Полноэкранный режим

        IWebDriver driver = new FirefoxDriver(driverService, options);
        try
        {
            Console.WriteLine("Тестирование URL-доступа без авторизации...");
            driver.Navigate().GoToUrl("https://example.com/internal-page");

            if (driver.Url.Contains("login"))
            {
                Console.WriteLine("Тест пройден: Доступ запрещен без авторизации.");
            }
            else
            {
                Console.WriteLine("Тест не пройден: Доступ открыт без авторизации.");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка: {ex.Message}");
        }
        finally
        {
            driver.Quit();
        }
    }

    static void TestURLIDChange()
    {
        var driverService = FirefoxDriverService.CreateDefaultService(@"C:\Users\lishy\Downloads\geckodriver-v0.35.0-win64");
        driverService.HideCommandPromptWindow = true; // Скрывает консоль geckodriver

        var options = new FirefoxOptions();
        options.AddArgument("--start-maximized"); // Полноэкранный режим

        IWebDriver driver = new FirefoxDriver(driverService, options);
        try
        {
            Console.WriteLine("Тестирование изменения ID в URL...");
            driver.Navigate().GoToUrl("https://example.com/stats?id=123");
            var originalContent = driver.PageSource;

            driver.Navigate().GoToUrl("https://example.com/stats?id=456");
            if (driver.PageSource == originalContent)
            {
                Console.WriteLine("Тест пройден: Нет доступа к данным другого пользователя.");
            }
            else
            {
                Console.WriteLine("Тест не пройден: Данные другого пользователя доступны.");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка: {ex.Message}");
        }
        finally
        {
            driver.Quit();
        }
    }

    static void TestInvalidLogin()
    {
        var driverService = FirefoxDriverService.CreateDefaultService(@"C:\Users\lishy\Downloads\geckodriver-v0.35.0-win64");
        driverService.HideCommandPromptWindow = true; // Скрывает консоль geckodriver

        var options = new FirefoxOptions();
        options.AddArgument("--start-maximized"); // Полноэкранный режим

        IWebDriver driver = new FirefoxDriver(driverService, options);
        try
        {
            Console.WriteLine("Тестирование ввода неверных данных в форму авторизации...");
            driver.Navigate().GoToUrl("https://example.com/login");

            driver.FindElement(By.Name("username")).SendKeys("wronguser");
            driver.FindElement(By.Name("password")).SendKeys("wrongpassword");
            driver.FindElement(By.Name("login")).Click();

            if (driver.PageSource.Contains("Неверный логин или пароль"))
            {
                Console.WriteLine("Тест пройден: Ошибка корректно отображается.");
            }
            else
            {
                Console.WriteLine("Тест не пройден: Ошибка не отображается.");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка: {ex.Message}");
        }
        finally
        {
            driver.Quit();
        }
    }

    static void TestDirectoryAccess()
    {
        var driverService = FirefoxDriverService.CreateDefaultService(@"C:\Users\lishy\Downloads\geckodriver-v0.35.0-win64");
        driverService.HideCommandPromptWindow = true; // Скрывает консоль geckodriver

        var options = new FirefoxOptions();
        options.AddArgument("--start-maximized"); // Полноэкранный режим

        IWebDriver driver = new FirefoxDriver(driverService, options);
        try
        {
            Console.WriteLine("Тестирование недоступности каталогов и файлов...");
            driver.Navigate().GoToUrl("https://example.com/hidden-folder/");

            if (driver.PageSource.Contains("403 Forbidden") || driver.PageSource.Contains("404 Not Found"))
            {
                Console.WriteLine("Тест пройден: Доступ к каталогу запрещен.");
            }
            else
            {
                Console.WriteLine("Тест не пройден: Доступ к каталогу открыт.");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка: {ex.Message}");
        }
        finally
        {
            driver.Quit();
        }
    }

    static void TestSSLRedirection()
    {
        var driverService = FirefoxDriverService.CreateDefaultService(@"C:\Users\lishy\Downloads\geckodriver-v0.35.0-win64");
        driverService.HideCommandPromptWindow = true; // Скрывает консоль geckodriver

        var options = new FirefoxOptions();
        options.AddArgument("--start-maximized"); // Полноэкранный режим

        IWebDriver driver = new FirefoxDriver(driverService, options);
        try
        {
            Console.WriteLine("Тестирование SSL...");
            driver.Navigate().GoToUrl("http://example.com");

            if (driver.Url.StartsWith("https://"))
            {
                Console.WriteLine("Тест пройден: HTTP автоматически перенаправлен на HTTPS.");
            }
            else
            {
                Console.WriteLine("Тест не пройден: HTTP не перенаправлен на HTTPS.");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка: {ex.Message}");
        }
        finally
        {
            driver.Quit();
        }
    }
}
