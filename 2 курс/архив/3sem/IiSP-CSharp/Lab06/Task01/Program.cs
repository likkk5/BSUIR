using Task01;
using System.Reflection;

List<Employee> employees = new List<Employee>();

employees.Add(new Employee(1, "1", true));
employees.Add(new Employee(2, "2", false));
employees.Add(new Employee(3, "3", true));
employees.Add(new Employee(4, "4", false));
employees.Add(new Employee(5, "5", true));
employees.Add(new Employee(6, "6", false));

string fileName = "file.json";

Assembly asm = Assembly.LoadFrom("Services.dll");
Type? type = asm.GetType("Services.FileService`1");
var genType = type.MakeGenericType(new[] { typeof(Employee) });
var instance = Activator.CreateInstance(genType);

genType.GetMethod("SaveData", BindingFlags.Instance | BindingFlags.Public)
                .Invoke(instance, new object[] { employees, fileName });
var list = (IEnumerable<Employee>)genType.GetMethod("ReadFile", BindingFlags.Instance | BindingFlags.Public)
                .Invoke(instance, new object[] { fileName });

foreach (var employee in list)
{
    Console.WriteLine($"{employee.Id} {employee.Name} {employee.IsDeleted}");
}
