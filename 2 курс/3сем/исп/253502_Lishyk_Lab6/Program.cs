using System;
using System.Collections.Generic;
using System.Reflection;
using _253502_Lishyk_Lab6;

class Program
{
    static void Main()
    {
        // Динамически загрузить библиотеку классов с помощью .NET Reflection
        Assembly asm = Assembly.LoadFile("C:\\учёба\\исп\\FileServiceLibrary\\bin\\Debug\\net6.0\\FileServiceLibrary.dll");//загружает сборку,неявно выполняет все классы и типы сборки и делает их доступными
        Type type = asm.GetType("FileServiceLibrary.FileService`1");//получает тип объекта в загруж сборке по его имени,сборка asm позвл получит тип ()
        //1 указывает на количество параметров типа, используемых в обобщенном типе.

        MethodInfo saveMethod = type.GetMethod("SaveData"); //извлекает информацию о методе по его имени, ссылки на методы из загруженной библиотеки классов.
        MethodInfo readMethod = type.GetMethod("ReadFile");

        if (saveMethod != null && readMethod != null)
        {
            Type genericType = type.MakeGenericType(typeof(Employee)); // созд конкретный тип FileService<Employee>

            object fileServiceInstance = Activator.CreateInstance(genericType);

            //коллекцию объектов Employee
            var employees = new List<Employee>
            {
                new Employee { EmployeeID = 1, IsManager = false, Name = "John Doe" },
                new Employee { EmployeeID = 2, IsManager = true, Name = "Becky Smith" },
                new Employee { EmployeeID = 3, IsManager = true, Name = "Jane Doe" },
                new Employee { EmployeeID = 4, IsManager = false, Name = "James Bond" },
                new Employee { EmployeeID = 5, IsManager = true, Name = "Lily Walker" },
            };

            // вызываем метод SaveData
            MethodInfo saveDataMethod = genericType.GetMethod("SaveData");
            saveDataMethod.Invoke(fileServiceInstance, new object[] { employees, "employees.json" });

            // вызываем метод ReadFile
            MethodInfo readFileMethod = genericType.GetMethod("ReadFile");
            var loadedEmployees = readFileMethod.Invoke(fileServiceInstance, new object[] { "employees.json" }) as IEnumerable<Employee>;

            // выводим данные из файла
            if (loadedEmployees != null)
            {
                foreach (var employee in loadedEmployees)
                {
                    Console.WriteLine($"EmployeeID: {employee.EmployeeID}, IsManager: {employee.IsManager}, Name: {employee.Name}");
                }
            }
            else
            {
                Console.WriteLine("File not found or empty.");
            }
        }
        else
        {
            Console.WriteLine("Methods not found in the loaded assembly.");
        }
    }
}
