using System;
using System.Linq;
using _253502_Lishyk_Lab1;
using _253502_Lishyk_Lab1.Contracts;
using _253502_Lishyk_Lab1.Entities;
using _253502_Lishyk_Lab1.Interfaces;


class Program
{
    static void Main(string[] args)
    {
        ICommunalServiceSystem communalServiceSystem = new MyCommunalServiceSystem();

        // Добавление тарифов
        var tariffs = new Tariff[]
        {
            new Tariff { ServiceName = "Electricity", PricePerUnit = 0.15 },
            new Tariff { ServiceName = "Water", PricePerUnit = 0.05 },
        };
        communalServiceSystem.AddTariffs(tariffs);

        // Добавление жильцов
        var tenants = new Tenant[]
        {
            new Tenant { LastName = "Smith" },
            new Tenant { LastName = "Doe" },
        };
        communalServiceSystem.AddTenants(tenants);

        // Запись потребления услуг
        communalServiceSystem.RecordServiceUsage("Smith", "Electricity", 200);
        communalServiceSystem.RecordServiceUsage("Smith", "Water", 500);
        communalServiceSystem.RecordServiceUsage("Doe", "Electricity", 150);
        

        // Вывод информации в консоль
        Console.WriteLine($"Total Cost: {communalServiceSystem.GetTotalCost():C}");
        Console.WriteLine($"Total Usage Cost for Smith: {communalServiceSystem.GetTotalUsageCost("Smith"):C}");
        Console.WriteLine($"Total Usage Cost for Doe: {communalServiceSystem.GetTotalUsageCost("Doe"):C}");
        Console.WriteLine($"Total Orders for Electricity: {communalServiceSystem.GetTotalOrdersForService("Electricity")}");
        Console.WriteLine($"Total Orders for Water: {communalServiceSystem.GetTotalOrdersForService("Water")}");


        Journal journal = new Journal();

        // Подписываем журнал на события
        communalServiceSystem.TariffsChanged += journal.RegisterEvent;
        communalServiceSystem.TenantsChanged += eventName => journal.RegisterEvent(eventName);

        // Создаем обработчик события для программы
        communalServiceSystem.TariffsChanged += eventName => Console.WriteLine($"TariffsChanged Event: {eventName}");
        communalServiceSystem.TenantsChanged += eventName => Console.WriteLine($"TenantsChanged Event: {eventName}");

        // Моделируем изменение списков тарифов и жильцов
        communalServiceSystem.AddTariffs(tariffs: new Tariff[] { });
        communalServiceSystem.AddTenants(tenants: new Tenant[] { });

        // Выводим информацию о событиях
        journal.DisplayEvents();
    }
}
//// Создаем экземпляры тарифов
//Tariff tariff1 = new Tariff { ServiceName = "Электроэнергия", PricePerUnit = 0.15 };
//Tariff tariff2 = new Tariff { ServiceName = "Газ", PricePerUnit = 0.30 };
//Tariff tariff3 = new Tariff { ServiceName = "Вода", PricePerUnit = 0.05 };

//// Создаем экземпляры жильцов
//Tenant tenant1 = new Tenant { LastName = "Иванов", FirstName = "Иван" };
//Tenant tenant2 = new Tenant { LastName = "Петров", FirstName = "Петр" };
//Tenant tenant3 = new Tenant { LastName = "Сидорова", FirstName = "Анна" };

//// Моделируем изменение списков тарифов и жильцов
//communalServiceSystem.AddTariffs(new Tariff[] { tariff1, tariff2, tariff3 });
//communalServiceSystem.AddTenants(new Tenant[] { tenant1, tenant2, tenant3 });
