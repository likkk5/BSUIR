using _253502_Lishyk_Lab1.Contracts;
using _253502_Lishyk_Lab1.Entities;
using System;
using System.Collections.Generic;

namespace _253502_Lishyk_Lab1
{
    class Program
    {
        static void Main(string[] args)
        {
            MyCommunalServiceSystem communalServiceSystem = new MyCommunalServiceSystem();

            // Adding tariffs
            var tariffs = new Dictionary<string, Tariff>
            {
                { "Electricity", new Tariff { ServiceName = "Electricity", PricePerUnit = 0.15 } },
                { "Water", new Tariff { ServiceName = "Water", PricePerUnit = 0.05 } }
            };
            communalServiceSystem.AddTariffs(tariffs);

            // Adding tenants
            var tenants = new List<Tenant>
            {
                new Tenant { LastName = "Smith" },
                new Tenant { LastName = "Doe" }
            };
            communalServiceSystem.AddTenants(tenants);

            // Recording service usage
            communalServiceSystem.RecordServiceUsage("Smith", "Electricity", 200);
            communalServiceSystem.RecordServiceUsage("Smith", "Water", 500);
            communalServiceSystem.RecordServiceUsage("Doe", "Electricity", 150);

            // Task 1: Service Names Sorted by Cost
            Console.WriteLine("Service Names Sorted by Cost:");
            var serviceNamesSortedByCost = communalServiceSystem.GetServiceNamesSortedByCost();
            foreach (var serviceName in serviceNamesSortedByCost)
            {
                Console.WriteLine(serviceName);
            }

            // Task 2: Total Cost for MyCommunalSystem
            Console.WriteLine($"Total Cost for MyCommunalSystem: {communalServiceSystem.GetTotalCostForJEK():C}");

            // Task 3: Total Cost for Smith and Doe
            Console.WriteLine($"Total Cost for Smith: {communalServiceSystem.GetTotalCostForTenant("Smith"):C}");
            Console.WriteLine($"Total Cost for Doe: {communalServiceSystem.GetTotalCostForTenant("Doe"):C}");

            // Task 4: Tenant with Max Payment
            Console.WriteLine($"Tenant with Max Payment: {communalServiceSystem.GetTenantWithMaxPayment()}");

            // Task 5: Number of Tenants with Payment Greater Than a Threshold
            double threshold = 100; // Replace with your desired threshold
            Console.WriteLine($"Number of Tenants with Payment > {threshold}: {communalServiceSystem.GetNumberOfTenantsWithPaymentGreaterThan(threshold)}");

            // Task 6: Payments by Service for Smith
            Console.WriteLine("Payments by Service for Smith:");
            var paymentsByServiceForSmith = communalServiceSystem.GetPaymentsByServiceForTenant("Smith");
            foreach (var kvp in paymentsByServiceForSmith)
            {
                Console.WriteLine($"{kvp.Key}: {kvp.Value:C}");
            }
        }
    }
}
