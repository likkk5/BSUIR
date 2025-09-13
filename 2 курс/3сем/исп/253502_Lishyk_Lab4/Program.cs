using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using _253502_Lishyk_Lab4;

class Program
{
    static void Main(string[] args)
    {
        string folderName = "Lishyk_Lab4";
        Directory.CreateDirectory(folderName);

        Random random = new Random();
        string[] extensions = { ".txt", ".rtf", ".dat", ".inf" };
        for (int i = 0; i < 10; i++)
        {
            string randomFileName = Path.Combine(folderName, $"File{i + 1}{extensions[random.Next(extensions.Length)]}");
            File.Create(randomFileName).Close();
        }

        string[] files = Directory.GetFiles(folderName);
        foreach (var file in files)
        {
            string fileName = Path.GetFileName(file);
            string extension = Path.GetExtension(file);
            Console.WriteLine($"Файл: {fileName} имеет расширение {extension}");
        }

        List<Mammal> mammals = new List<Mammal>
        {
            new Mammal { Name = "Lion", Age = 5, HasTail = true },
            new Mammal { Name = "Gorilla", Age = 10, HasTail = false },
            new Mammal { Name = "Tiger", Age = 3, HasTail = true },
            new Mammal { Name = "Giraffe", Age = 7, HasTail = true },
            new Mammal { Name = "Bear", Age = 6, HasTail = true },
        };

        FileService<Mammal> fileService = new FileService<Mammal>();
        fileService.SaveData("mammals.dat", mammals);

        File.Move("mammals.dat", "mammals_renamed.dat", true);

        List<Mammal> newMammals = fileService.ReadFile("mammals_renamed.dat").ToList();

        MyCustomComparer<Mammal> comparer = new MyCustomComparer<Mammal>();
        newMammals = newMammals.OrderBy(m => m, comparer).ToList();

        Console.WriteLine("Исходная коллекция:");
        foreach (var mammal in mammals)
        {
            Console.WriteLine($"Имя: {mammal.Name}, Возраст: {mammal.Age}, Есть хвост: {mammal.HasTail}");
        }

        newMammals = newMammals.OrderBy(m => m.Age).ToList();

        Console.WriteLine("Отсортированная коллекция по возрасту:");
        foreach (var mammal in newMammals)
        {
            Console.WriteLine($"Имя: {mammal.Name}, Возраст: {mammal.Age}, Есть хвост: {mammal.HasTail}");
        }
    }
}