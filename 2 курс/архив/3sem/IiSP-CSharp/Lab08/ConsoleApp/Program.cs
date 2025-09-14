using ClassLibrary;

class Program
{
    public static async Task Main(string[] args)
    {
        List<Car> cars = new List<Car>();

        var rnd = new Random();
        for (int i = 0; i < 1000; i++)
        {
            Car car = new Car();
            car.Id = i;
            car.Name = $"Car {i}";
            car.TechnicalInspectionYear = 2020 + rnd.Next(10);
            cars.Add(car);
        }

        StreamService<Car> streamService = new StreamService<Car>();

        MemoryStream memoryStream = new MemoryStream();

        streamService.WriteToStreamAsync(memoryStream, cars);
        Console.WriteLine("hey1");
        Thread.Sleep(100);
        streamService.CopyFromStreamAsync(memoryStream, "file.txt");
        Console.WriteLine("hey2");
        Console.WriteLine(await streamService.GetStatisticsAsync("file.txt", (Car car) => car.TechnicalInspectionYear == 2022));
    }
}


