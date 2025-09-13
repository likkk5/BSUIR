using _253502_Lishyk_Lab8;
class Program
{
    //static async Task Main(string[] args)
    //{
    //    Console.WriteLine($"Main thread id: {Thread.CurrentThread.ManagedThreadId}");

    //    var biologyCollection = GenerateBiologyCollection(1000);

    //    var streamService = new StreamService<Biology>();
    //    var stream = new MemoryStream();
    //    var progress = new Progress<string>(message => Console.WriteLine(message));

    //    Console.WriteLine($"Main thread id: {Thread.CurrentThread.ManagedThreadId}");

    //    // Подписка на событие до запуска асинхронных операций
    //    streamService.ProgressEvent += (sender, eventArgs) =>
    //    {
    //        Console.WriteLine($"Thread {eventArgs.ThreadId}: {eventArgs.Message}");
    //    };

    //    streamService.WriteToStreamAsync(stream, biologyCollection, progress);
    //    Thread.Sleep(200); // Introduce delay between method calls

    //    //// Запуск набора асинхронных методов с использованием Task.Run
    //    //await Task.WhenAll(Task.Run(() => streamService.WriteToStreamAsync(new MemoryStream(), biologyCollection, progress)),
    //    //                   Task.Run(() => streamService.CopyFromStreamAsync(new MemoryStream(), "output.txt", progress)));

    //    //// Ожидание завершения выполнения всех асинхронных задач
    //    //await Task.WhenAll(streamService.WriteToStreamAsync(new MemoryStream(), biologyCollection, progress),
    //    //                   streamService.CopyFromStreamAsync(new MemoryStream(), "output.txt", progress));

    //    // Запуск набора асинхронных методов без Task.Run
    //    await Task.WhenAll(
    //        streamService.WriteToStreamAsync(new MemoryStream(), biologyCollection, progress),
    //        streamService.CopyFromStreamAsync(new MemoryStream(), "output.txt", progress)
    //    );

    //    // Assume that the above methods have completed, and now we can get statistics asynchronously
    //    var filter = new Func<Biology, bool>(item => item.CanFly.ToLower() == "yes");
    //    var statistics = await streamService.GetStatisticsAsync("output.txt", filter);

    //    Console.WriteLine($"Statistics: {statistics} biologies can fly");
    //}

    static async Task Main(string[] args)
    {
        Console.WriteLine($"Main thread id: {Thread.CurrentThread.ManagedThreadId}");

        var biologyCollection = GenerateBiologyCollection(1000);

        var streamService = new StreamService<Biology>();
        var progress = new Progress<string>(message => Console.WriteLine(message));

        Console.WriteLine($"Main thread id: {Thread.CurrentThread.ManagedThreadId}");

        // Подписка на событие до запуска асинхронных операций
        streamService.ProgressEvent += (sender, eventArgs) =>
        {
            Console.WriteLine($"Thread {eventArgs.ThreadId}: {eventArgs.Message}");
        };

        // Отдельные экземпляры MemoryStream
        using (var streamForWriting = new MemoryStream())
        using (var streamForCopying = new MemoryStream())
        {
            // Запуск асинхронных методов с использованием Task.Run
            var writeTask = Task.Run(async () =>
            {
                await streamService.WriteToStreamAsync(streamForWriting, biologyCollection, progress);
            });

            var copyTask = Task.Run(() => streamService.CopyFromStreamAsync(streamForCopying, "output.txt", progress));

            // Wait for both tasks to complete
            await Task.WhenAll(writeTask, copyTask);

            //streamForWriting.Position = 0;
            //streamForCopying.Position = 0;

            // Assume that the above methods have completed, and now we can get statistics asynchronously
            var filter = new Func<Biology, bool>(item => item.CanFly.ToLower() == "yes");
            var statistics = await streamService.GetStatisticsAsync("output.txt", filter);

            Console.WriteLine($"Statistics: {statistics} biologies can fly");
        }
    }

    static IEnumerable<Biology> GenerateBiologyCollection(int count)
    {
        var biologyCollection = new List<Biology>();
        for (int i = 0; i < count; i++)
        {
            biologyCollection.Add(new Biology { Id = i, Name = $"Organism_{i}", CanFly = i % 2 == 0 ? "Yes" : "No" });
        }
        return biologyCollection;
    }
}