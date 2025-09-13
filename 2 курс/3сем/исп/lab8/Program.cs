using System;
using System.Diagnostics;
using _253502_Lishyk_Lab8;
using System.Threading.Tasks;

class Program
{
    public static async Task Main(string[] args)//абстракция более высокого уровня, т.к. он представляет параллельную операцию, которая может быть или не быть подкреплена потоком.
    //используется для определения того, что метод долж вызываться асинхронно автоматически
    {
        List<Biology> biologys = new List<Biology>();

        var rnd = new Random();
        for (int i = 0; i < 1000; i++)
        {
            Biology biology = new Biology();
            biology.Id = i;
            biology.Name = $"Biology {i}";
            biology.CanFly = rnd.Next(2) == 0; // Присваивает случайное значение true или false
            biologys.Add(biology);
        }

        StreamService<Biology> streamService = new StreamService<Biology>();
        var progress = new Progress<string>(message => Console.WriteLine($"{message}"));

        MemoryStream memoryStream = new MemoryStream();

        var task1 = streamService.WriteToStreamAsync(memoryStream, biologys, progress);

        await Task.Delay(1000);

        var task2 = streamService.CopyFromStreamAsync(memoryStream, "file.txt", progress);
        
        await Task.WhenAll(task1, task2);

        Console.WriteLine(await streamService.GetStatisticsAsync("file.txt", (Biology biology) => biology.CanFly));
        //await гарантирует, что асинхронные операции не блокируют основной поток, что позволяет выполнять другие операции во время ожидания завершения асинхронных задач
        //await, примененное к асинхронному методу, автоматически приостанавливает текущий поток, пока задача не будет завершена
    }

}
//Асинхронная операция выполняет (большую часть или всю) свою работу после возврата управления вызывающему коду.
