using OpenQA.Selenium;
using OpenQA.Selenium.Firefox;
using OpenQA.Selenium.Chrome;
using OpenQA.Selenium.Edge;
using System;

class WebTesting
{
    static void Main(string[] args)
    {
        Console.WriteLine("Выберите сценарий тестирования:");
        Console.WriteLine("1: Совместимость браузеров");
        Console.WriteLine("2: Адаптивность мобильной версии");
        Console.WriteLine("3: Проверка печати");
        Console.Write("Введите номер сценария: ");

        string choice = Console.ReadLine();

        switch (choice)
        {
            case "1":
                TestBrowserCompatibility();
                break;
            case "2":
                TestMobileView();
                break;
            case "3":
                TestPrintFunctionality();
                break;
            default:
                Console.WriteLine("Некорректный выбор. Завершение программы.");
                break;
        }
    }

    // Проверка совместимости браузеров
    static void TestBrowserCompatibility()
    {
        // Добавьте драйверы для нужных браузеров
        IWebDriver[] drivers = new IWebDriver[]
        {
            CreateFirefoxDriver(),
            CreateChromeDriver(),
            CreateEdgeDriver()
        };

        try
        {
            foreach (var driver in drivers)
            {
                Console.WriteLine($"Тестирование в браузере: {driver.GetType().Name}");

                driver.Navigate().GoToUrl("https://www.tsu.ru/");
                driver.Manage().Window.Maximize();

                // Проверка корректности загрузки страницы
                var title = driver.Title;
                Console.WriteLine($"Заголовок страницы: {title}");

                if (!string.IsNullOrEmpty(title))
                {
                    Console.WriteLine("Сайт загружается корректно.");
                }
                else
                {
                    Console.WriteLine("Ошибка загрузки сайта.");
                }

                driver.Quit();
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка: {ex.Message}");
        }
    }

    // Проверка адаптивности
    static void TestMobileView()
    {
        IWebDriver driver = CreateChromeDriver(); // Лучше использовать Chrome для эмуляции мобильных устройств
        try
        {
            driver.Navigate().GoToUrl("https://www.tsu.ru/");

            // Установим параметры для мобильной эмуляции
            var mobileEmulation = new ChromeOptions();
            mobileEmulation.AddArgument("--window-size=375,812"); // iPhone X
            Console.WriteLine("Проверка адаптивности сайта в эмуляции мобильного устройства.");

            driver.Manage().Window.Size = new System.Drawing.Size(375, 812); // Изменение размера окна

            // Проверка загрузки страницы
            var body = driver.FindElement(By.TagName("body"));
            if (body.Displayed)
            {
                Console.WriteLine("Сайт корректно отображается на мобильном устройстве.");
            }
            else
            {
                Console.WriteLine("Ошибка в адаптивности сайта.");
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

    // Проверка печати
    static void TestPrintFunctionality()
    {
        IWebDriver driver = CreateFirefoxDriver();
        try
        {
            driver.Navigate().GoToUrl("https://www.tsu.ru/");
            Console.WriteLine("Проверка печати страницы...");

            // Выполнение команды печати
            ((IJavaScriptExecutor)driver).ExecuteScript("window.print();");
            Console.WriteLine("Печать инициирована. Проверьте визуальный вывод.");
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

    // Создание FirefoxDriver
    static IWebDriver CreateFirefoxDriver()
    {
        var service = FirefoxDriverService.CreateDefaultService();
        service.HideCommandPromptWindow = true; // Скрыть консольный вывод Geckodriver

        var options = new FirefoxOptions();
        options.AddArgument("--headless"); // Без графического интерфейса

        return new FirefoxDriver(service, options);
    }

    // Создание ChromeDriver
    static IWebDriver CreateChromeDriver()
    {
        var options = new ChromeOptions();
        options.AddArgument("--start-maximized");
        return new ChromeDriver(options);
    }

    // Создание EdgeDriver
    static IWebDriver CreateEdgeDriver()
    {
        return new EdgeDriver();
    }
}
