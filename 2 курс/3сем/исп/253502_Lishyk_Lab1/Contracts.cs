using _253502_Lishyk_Lab1.Entities;

namespace _253502_Lishyk_Lab1
{
    namespace Contracts
    {
        public interface ICommunalServiceSystem
        {
            event Action<string> TariffsChanged; //объявление событий
            event Action<string> TenantsChanged;

            void AddTariffs(Tariff[] tariffs);
            void AddTenants(Tenant[] tenants);
            void RecordServiceUsage(string lastName, string serviceName, double usage); //записывает потребляемые услуги по фамилии
            double GetTotalCost();//рассчитывает и возвращ общую стоимость потребл услг для всех жильцов, перебирает
            double GetTotalCost<T>();//использ обобщенные опреации для вычисл
            int GetTotalOrdersForService(string serviceName); //вовращ общее колво заказов для указанной услуги для всех жильцов
            double GetTotalUsageCost(string lastName); //записывает и возвращает общую стоимость потребл услуг по фамилии

            public void RemoveTariff(Tariff tariff);
            public void RemoveTenant(Tenant tenant);

        }
    }
}
