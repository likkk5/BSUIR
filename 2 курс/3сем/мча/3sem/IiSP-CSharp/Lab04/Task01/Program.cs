using Task01.Entities;
using Task01.IO;
using Task01.Comparers;

List<Car> cars1 = new List<Car>();

cars1.Add(new Car(100, false, "Car1"));
cars1.Add(new Car(300, false, "Car4"));
cars1.Add(new Car(200, true, "Car6"));
cars1.Add(new Car(400, false, "Car5"));
cars1.Add(new Car(600, true, "Car2"));
cars1.Add(new Car(500, false, "Car3"));

Console.WriteLine("DEFAULT CARS");
foreach (Car car in cars1)
{
    Console.WriteLine($"{car.Price} {car.Sold} {car.Name}");
}

FileService fs = new FileService();

string fileName = "file.txt";

fs.SaveData(cars1, fileName);

List<Car> cars2 = new List<Car>();

string newFileName = "newfile.txt";
File.Move(fileName, newFileName);


foreach (var car in fs.ReadFile(newFileName))
{
    cars2.Add(car);
}

File.Delete(newFileName);
Console.WriteLine("\nREADED CARS");
foreach (Car car in cars2)
{
    Console.WriteLine($"{car.Price} {car.Sold} {car.Name}");
}


Console.WriteLine("\nSORTED CARS");
var sortedCars = cars1.OrderBy(car => car, new MyCustomComparer()).ToList();

foreach (var car in sortedCars)
{
    Console.WriteLine($"{car.Price} {car.Sold} {car.Name}");
}

Console.WriteLine("\nCUSTOM SORTED CARS");

var customSortedCars = cars1.OrderBy(car => car.Price).ToList();

foreach (var car in customSortedCars)
{
    Console.WriteLine($"{car.Price} {car.Sold} {car.Name}");
}