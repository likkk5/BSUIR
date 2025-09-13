using OpenQA.Selenium;
using OpenQA.Selenium.Firefox;
using System;
using System.Diagnostics;
using System.IO;
using System.Threading.Tasks;

class LoadTesting
{
    static void Main(string[] args)
    {
        Console.WriteLine("Введите количество пользователей для тестирования:");
        if (!int.TryParse(Console.ReadLine(), out int numberOfUsers) || numberOfUsers <= 0)
        {
            Console.WriteLine("Некорректное значение. Используется значение по умолчанию: 50.");
            numberOfUsers = 50;
        }

        Console.WriteLine("Введите URL для тестирования (по умолчанию: https://www.tsu.ru/):");
        string url = Console.ReadLine();
        if (string.IsNullOrEmpty(url))
        {
            url = "https://www.tsu.ru/";
        }

        Console.WriteLine($"Начинается нагрузочное тестирование для {numberOfUsers} пользователей на URL: {url}\n");

        // Запись заголовка в CSV файл
        File.AppendAllText("load_test_results.csv", "User,PageTitle,LoadTimeMs,LogoPresent\n");

        Parallel.For(0, numberOfUsers, i =>
        {
            var driverService = FirefoxDriverService.CreateDefaultService();
            driverService.HideCommandPromptWindow = true; // Скрыть консольный вывод geckodriver
            var options = new FirefoxOptions();
            var driver = new FirefoxDriver(driverService, options);

            try
            {
                // Замер времени загрузки страницы
                var stopwatch = Stopwatch.StartNew();
                driver.Navigate().GoToUrl(url);
                stopwatch.Stop();

                string title = driver.Title;
                Console.WriteLine($"Пользователь {i + 1}: Заголовок страницы: {title}");
                Console.WriteLine($"Пользователь {i + 1}: Время загрузки: {stopwatch.ElapsedMilliseconds} мс");

                // Проверка доступности элемента (например, логотипа сайта)
                bool isElementPresent = IsElementPresent(driver, By.CssSelector("img"));
                Console.WriteLine($"Пользователь {i + 1}: Логотип доступен: {isElementPresent}");

                // Запись результатов в CSV файл
                File.AppendAllText("load_test_results.csv", $"{i + 1},{title},{stopwatch.ElapsedMilliseconds},{isElementPresent}\n");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Пользователь {i + 1}: Ошибка - {ex.Message}");
            }
            finally
            {
                driver.Quit();
            }

            // Задержка между запросами (симуляция реального пользователя)
            Task.Delay(100).Wait(); // 100 мс задержка
        });

        Console.WriteLine("\nНагрузочное тестирование завершено.");
    }

    // Проверка наличия элемента на странице
    static bool IsElementPresent(IWebDriver driver, By by)
    {
        try
        {
            driver.FindElement(by);
            return true;
        }
        catch (NoSuchElementException)
        {
            return false;
        }
    }
}
