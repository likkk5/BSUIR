using System;
using System.Net;
using RestSharp;
using OpenQA.Selenium;
using OpenQA.Selenium.Firefox;
using OpenQA.Selenium.Support.UI;

class InterfaceTesting
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
            // Тестирование интерфейса веб-сервера и приложения
            TestWebServerConnection(driver);

            // Тестирование связи между приложением и базой данных через API
            TestDatabaseServerConnection();

            // Проверка прерывания действий и повторного подключения
            TestUserInterruptions(driver);
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

    static void TestWebServerConnection(IWebDriver driver)
    {
        Console.WriteLine("=== Тестирование интерфейса веб-сервера и приложения ===");

        try
        {
            // Открываем тестируемый сайт
            driver.Navigate().GoToUrl("https://www.tsu.ru/");
            WebDriverWait wait = new WebDriverWait(driver, TimeSpan.FromSeconds(10));
            wait.Until(d => d.FindElement(By.TagName("body")));

            // Проверяем, доступен ли веб-сервер
            var statusCode = GetHttpResponseStatus("https://www.tsu.ru/");
            if (statusCode == HttpStatusCode.OK)
            {
                Console.WriteLine("Веб-сервер отвечает корректно (200 OK).");
            }
            else
            {
                Console.WriteLine($"Ошибка соединения с сервером: {statusCode}");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при проверке веб-сервера: {ex.Message}");
        }
    }

    static void TestDatabaseServerConnection()
    {
        Console.WriteLine("=== Тестирование интерфейса базы данных и сервера приложения ===");

        try
        {
            // Имитация запроса к API, связывающему приложение и базу данных
            var client = new RestClient("https://api.example.com/");
            var request = new RestRequest("data-endpoint", Method.Get);

            var response = client.Execute(request);

            if (response.StatusCode == HttpStatusCode.OK)
            {
                Console.WriteLine("Связь с сервером базы данных установлена успешно.");
                Console.WriteLine($"Полученные данные: {response.Content}");
            }
            else
            {
                Console.WriteLine($"Ошибка сервера базы данных: {response.StatusCode} - {response.ErrorMessage}");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при проверке сервера базы данных: {ex.Message}");
        }
    }

    static void TestUserInterruptions(IWebDriver driver)
    {
        Console.WriteLine("=== Тестирование прерывания действий и повторного подключения ===");

        try
        {
            // Начало длительной операции
            driver.Navigate().GoToUrl("https://www.tsu.ru/long-action-page");
            var actionButton = driver.FindElement(By.Id("start-long-action")); // Замените ID на реальный
            actionButton.Click();

            Console.WriteLine("Длительная операция начата.");

            // Прерывание пользователя
            Console.WriteLine("Прерывание операции...");
            driver.Navigate().Refresh();

            // Проверка, возобновляется ли действие или происходит сбой
            var statusMessage = driver.FindElement(By.Id("status-message")).Text; // Замените ID на реальный
            if (statusMessage.Contains("Operation interrupted"))
            {
                Console.WriteLine("Прерывание операции обработано корректно.");
            }
            else
            {
                Console.WriteLine($"Неожиданное поведение после прерывания: {statusMessage}");
            }

            // Повторное подключение
            Console.WriteLine("Попытка повторного подключения...");
            driver.Navigate().Refresh();

            var reconnectMessage = driver.FindElement(By.Id("status-message")).Text; // Замените ID на реальный
            if (reconnectMessage.Contains("Reconnected"))
            {
                Console.WriteLine("Повторное подключение прошло успешно.");
            }
            else
            {
                Console.WriteLine($"Неожиданное поведение при повторном подключении: {reconnectMessage}");
            }
        }
        catch (NoSuchElementException)
        {
            Console.WriteLine("Не найдены элементы интерфейса для тестирования прерывания действий.");
        }
    }

    static HttpStatusCode GetHttpResponseStatus(string url)
    {
        try
        {
            var request = WebRequest.Create(url) as HttpWebRequest;
            request.Method = "HEAD";

            using (var response = request.GetResponse() as HttpWebResponse)
            {
                return response.StatusCode;
            }
        }
        catch (WebException ex)
        {
            if (ex.Response is HttpWebResponse errorResponse)
            {
                return errorResponse.StatusCode;
            }

            return HttpStatusCode.ServiceUnavailable;
        }
    }
}
