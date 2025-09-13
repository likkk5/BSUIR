namespace _253502_Lishyk_Lab1
{
    namespace Entities
    {
        public class Tariff
        {
            public string ServiceName { get; set; } 
            public double PricePerUnit { get; set; } //цена за потребление услуги
        }

        public class Tenant //арендатор, жилец
        {
            public string LastName { get; set; }
            public List<ServiceUsage> ServiceUsages { get; set; } = new List<ServiceUsage>(); //список записей о потреблении услуг
        }

        public class ServiceUsage
        {
            public Tariff Tariff { get; set; }
            public string ServiceName { get; set; }
            public double Usage { get; set; } //колво потрбл услуг

            public double TotalCost
            {
                get => Tariff.PricePerUnit * Usage;
            }
        }
        public class Journal
        {
            private List<string> eventsLog = new List<string>();

            public void RegisterEvent(string eventName)
            {
                eventsLog.Add(eventName);
            }

            public void DisplayEvents()
            {
                Console.WriteLine("Registered Events:");
                foreach (var eventName in eventsLog)
                {
                    Console.WriteLine(eventName);
                }
            }
        }
    }

}
