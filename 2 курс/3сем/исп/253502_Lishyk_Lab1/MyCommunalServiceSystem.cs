using _253502_Lishyk_Lab1.Contracts;
using _253502_Lishyk_Lab1.Entities;
using _253502_Lishyk_Lab1.Interfaces;
using _253502_Lishyk_Lab1.Math;
using System.Linq;
//using GenericMath;

namespace _253502_Lishyk_Lab1
{
    public class MyCommunalServiceSystem : ICommunalServiceSystem
    {
        private MyCustomCollection<Tariff> tariffs = new MyCustomCollection<Tariff>(); //коллекция тарифов
        private MyCustomCollection<Tenant> tenants = new MyCustomCollection<Tenant>(); //коллекция жильцов

        public event Action<string> TariffsChanged;//возможность подписаться на изменения тарифов и изменения списка жильцов.
        public event Action<string> TenantsChanged; //опред событие кот использ делегаты

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
        public void AddTariffs(Tariff[] tariffs)
        {
            foreach (var tariff in tariffs)
            {
                this.tariffs.Add(tariff);
            }
            // Вызываем событие TariffsChanged при изменении списка тарифов
            OnTariffsChanged("Tariffs list has been changed.");
        }

        public void AddTenants(Tenant[] tenants)
        {
            foreach (var tenant in tenants)
            {
                this.tenants.Add(tenant);
            }
            // Вызываем событие TenantsChanged при изменении списка жильцов
            OnTenantsChanged("Tenants list has been changed.");
        }

        public void RecordServiceUsage(string lastName, string serviceName, double usage)
        {
            var tenant = tenants.Current();
            if (tenant.LastName == lastName)
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
                    var tariff = tariffs.FirstOrDefault(t => t.ServiceName == usage.ServiceName);
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
                    var tariff = tariffs.FirstOrDefault(t => t.ServiceName == usage.ServiceName);
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
                    var tariff = tariffs.FirstOrDefault(t => t.ServiceName == usage.ServiceName);
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
            tariffs.Remove(tariff);

            // Вызываем событие TariffsChanged при удалении тарифа
            OnTariffsChanged("Tariffs list has been changed.");
        }
        public void RemoveTenant(Tenant tenant)
        {
            tenants.Remove(tenant);

            // Вызываем событие TariffsChanged при удалении тарифа
            OnTenantsChanged("Tariffs list has been changed.");
        }

    }

}
