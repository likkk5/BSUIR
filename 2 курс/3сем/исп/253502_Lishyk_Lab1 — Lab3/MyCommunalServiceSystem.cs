using _253502_Lishyk_Lab1.Contracts;
using _253502_Lishyk_Lab1.Entities;
using _253502_Lishyk_Lab1.Interfaces;
using _253502_Lishyk_Lab1.Math;
using System.Collections.Generic;
using System.Linq;
//using GenericMath;

namespace _253502_Lishyk_Lab1
{
    public class MyCommunalServiceSystem : ICommunalServiceSystem<Tariff, Tenant>
    {
        private Dictionary<string, Tariff> tariffs = new Dictionary<string, Tariff>(); // Словарь тарифов
        private List<Tenant> tenants = new List<Tenant>(); // Список жильцов

        public event Action<string> TariffsChanged; // Событие изменения тарифов
        public event Action<string> TenantsChanged; // Событие изменения жильцов

        // Метод для вызова события TariffsChanged
        protected virtual void OnTariffsChanged(string eventName)
        {
            TariffsChanged?.Invoke(eventName);
        }

        // Метод для вызова события TenantsChanged
        protected virtual void OnTenantsChanged(string eventName)
        {
            TenantsChanged?.Invoke(eventName);
        }
        public void AddTariffs(Dictionary<string, Tariff> tariffs)
        {
            foreach (var tariff in tariffs)
            {
                this.tariffs.Add(tariff.Key, tariff.Value);
            }
            // Вызываем событие TariffsChanged при изменении списка тарифов
            OnTariffsChanged("Tariffs list has been changed.");
        }

        public void AddTenants(List<Tenant> tenants)
        {
            foreach (var tenant in tenants)
            {
                this.tenants.Add(tenant);
            }
            // Вызываем событие TenantsChanged при изменении списка жильцов
            OnTenantsChanged("Tenants list has been changed.");
        }

        //методы для выполнения заданий LINQ
        //использует LINQ-запрос, чтобы сначала отсортировать тарифы(по возрст) по стоимости за единицу услуги, а затем выбирает имена услуг и преобразует их в список.
        public List<string> GetServiceNamesSortedByCost()
        {
            var serviceNames = tariffs
                .OrderBy(t => t.Value.PricePerUnit)
                .Select(t => t.Key)
                .ToList();
            return serviceNames;
        }

        //использует LINQ-запрос для объединения данных об использовании услуг с соответствующими тарифами и вычисления общей стоимости.
        public double GetTotalCostForJEK()
        {
            var totalCost = tenants
                .SelectMany(t => t.ServiceUsages)//объед в одну послед-ть
                .Join(tariffs, usage => usage.ServiceName, tariff => tariff.Key, (usage, tariff) => usage.Usage * tariff.Value.PricePerUnit) //соединение данных
                .Sum();
            return totalCost;
        }

        //сначала фильтрует арендаторов по фамилии, а затем использует LINQ для подсчета общей стоимости услуг для выбранного арендатора.
        public double GetTotalCostForTenant(string lastName)
        {
            var tenantTotalCost = tenants
                .Where(t => t.LastName == lastName)//фильтр
                .SelectMany(t => t.ServiceUsages) 
                .Join(tariffs, usage => usage.ServiceName, tariff => tariff.Key, (usage, tariff) => usage.Usage * tariff.Value.PricePerUnit)
                .Sum();
            return tenantTotalCost;
        }

        //создает анонимные объекты, содержащие фамилию арендатора и общую стоимость его услуг, затем сортирует их в порядке убывания стоимости и возвращает фамилию арендатора с наибольшей стоимостью.
        public string GetTenantWithMaxPayment()
        {
            var maxPayment = tenants
                .Select(t => new
                {
                    TenantName = t.LastName,
                    TotalPayment = t.ServiceUsages
                        .Join(tariffs, usage => usage.ServiceName, tariff => tariff.Key, (usage, tariff) => usage.Usage * tariff.Value.PricePerUnit)
                        .Sum()
                })
                .OrderByDescending(t => t.TotalPayment)//по убыванию
                .FirstOrDefault();

            return maxPayment?.TenantName;
        }
        //использует метод Aggregate, чтобы подсчитать количество арендаторов, чьи общие платежи превышают порог (threshold).
        public int GetNumberOfTenantsWithPaymentGreaterThan(double threshold)
        {
            var numberOfTenants = tenants
                .Select(t => t.ServiceUsages
                    .Join(tariffs, usage => usage.ServiceName, tariff => tariff.Key, (usage, tariff) => usage.Usage * tariff.Value.PricePerUnit)
                    .Sum())//общ стоим-ть для каждого
                .Aggregate(0, (total, payment) => total + (payment > threshold ? 1 : 0));//кол-во превыш порог

            return numberOfTenants;
        }

        //группирует использование услуг по имени услуги, затем вычисляет общую стоимость для каждой группы и создает словарь, связывая имя услуги с её стоимостью для данного арендатора.
        public Dictionary<string, double> GetPaymentsByServiceForTenant(string lastName)
        {
            var paymentsByService = tenants
                .Where(t => t.LastName == lastName)
                .SelectMany(t => t.ServiceUsages)
                .GroupBy(usage => usage.ServiceName)
                .ToDictionary(
                    group => group.Key,
                    group => group.Sum(usage => usage.Usage * tariffs[group.Key].PricePerUnit)
                );

            return paymentsByService; //метод возвращает словарь, где key-имена услуг, значения-общ стоим услуг для арендатора (lastName)
        }

        public void RecordServiceUsage(string lastName, string serviceName, double usage)
        {
            var tenant = tenants.FirstOrDefault(t => t.LastName == lastName);
            if (tenant != null)
            {
                tenant.ServiceUsages.Add(new ServiceUsage { ServiceName = serviceName, Usage = usage });
            }
        }

        public double GetTotalCost<T>()
        {
            IGenericOperator<T> genericOperator = new GenericOperator<T>();

            T totalCost = genericOperator.Zero;

            foreach (var tenant in tenants)
            {
                foreach (var usage in tenant.ServiceUsages)
                {
                    var tariff = tariffs.FirstOrDefault(t => t.Key == usage.ServiceName).Value;
                    if (tariff != null)
                    {
                        T usageCost = genericOperator.Multiply(genericOperator.FromInt(Convert.ToInt32(usage.Usage)), genericOperator.FromDouble(tariff.PricePerUnit));
                        totalCost = genericOperator.Add(totalCost, usageCost);
                    }
                }
            }

            return genericOperator.ToDouble(totalCost);
        }

        public double GetTotalCost()
        {
            double totalCost = 0.0;
            foreach (var tenant in tenants)
            {
                foreach (var usage in tenant.ServiceUsages)
                {
                    var tariff = tariffs.FirstOrDefault(t => t.Key == usage.ServiceName).Value;
                    if (tariff != null)
                    {
                        totalCost += tariff.PricePerUnit * usage.Usage;
                    }
                }
            }
            return totalCost;
        }

        public int GetTotalOrdersForService(string serviceName)
        {
            int totalOrders = 0;
            foreach (var tenant in tenants)
            {
                totalOrders += tenant.ServiceUsages.Count(usage => usage.ServiceName == serviceName);
            }
            return totalOrders;
        }

        public double GetTotalUsageCost(string lastName)
        {
            double totalUsageCost = 0.0;
            var tenant = tenants.FirstOrDefault(t => t.LastName == lastName);
            if (tenant != null)
            {
                foreach (var usage in tenant.ServiceUsages)
                {
                    var tariff = tariffs.FirstOrDefault(t => t.Key == usage.ServiceName).Value;
                    if (tariff != null)
                    {
                        totalUsageCost += tariff.PricePerUnit * usage.Usage;
                    }
                }
            }
            return totalUsageCost;
        }

        public void RemoveTariff(Tariff tariff)
        {
            tariffs.Remove(tariff.ServiceName);

            // Вызываем событие TariffsChanged при удалении тарифа
            OnTariffsChanged("Tariffs list has been changed.");
        }

        public void RemoveTenant(Tenant tenant)
        {
            tenants.Remove(tenant);

            // Вызываем событие TenantsChanged при удалении жильца
            OnTenantsChanged("Tenants list has been changed.");
        }


    }
}
