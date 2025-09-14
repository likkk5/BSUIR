namespace BAHDANAU_153502_Lab5.Entities
{
    public class Bank
    {
        private List<Client> clients;
        private List<Deposit> deposits;
        private Dictionary<string, int> tarrifs;

        private string bankName;
        public delegate void AddClientDelegate(string message);
        public event AddClientDelegate? AddClientEvent;
        public delegate void AddDepositDelegate(string message);
        public event AddDepositDelegate? AddDepositEvent;

        public Bank(string bankName)
        {
            this.bankName = bankName;
            clients = new List<Client>();
            tarrifs = new Dictionary<string, int>();
            deposits = new List<Deposit>();
        }

        public string BankName
        {
            get { return bankName; }
        }

        public void AddClient(string clientName)
        {
            clients.Add(new Client(clientName));
            AddClientEvent?.Invoke($"New client {clientName}");
        }

        public void AddDeposit(decimal price, string tarrifName, string clientName)
        {
            Client? client = null;
            foreach (var c in clients)
            {
                if (c.Name == clientName)
                {
                    client = c;
                    break;
                }
            }

            if (client == null)
            {
                throw new Exception("Client does not exist");
            }

            if (!tarrifs.ContainsKey(tarrifName))
            {
                throw new Exception("Tarrif does not exist");
            }

            deposits.Add(new Deposit(client, price, tarrifs[tarrifName]));
            AddDepositEvent?.Invoke($"New deposit by {clientName}");
        }

        public decimal PayoutAmount()
        {
            throw new NotImplementedException();
        }

        public void AddTarrif(string tarrifName, int percent)
        {
            tarrifs[tarrifName] = percent;
        }

        public List<string> GetTarrifsSortedByPercent()
        {
            return (from tarrif in tarrifs
                    orderby tarrif.Value descending
                    select tarrif.Key).ToList();
        }

        public int GetSumPercents()
        {
            return (from deposit in deposits
                    select deposit.Percent).Sum();
        }

        public decimal GetSumDeposits()
        {
            return (from deposit in deposits
                    select deposit.Price).Sum();
        }

        public string GetClientNameWithMaxPercent()
        {
            return (string)(from deposit in deposits
                            group deposit.Percent by deposit.client into g
                            orderby g.Sum()
                            select g.Key.Name).First();
        }

        public int GetClientCountGreaterSum(decimal sum)
        {
            return (from deposit in deposits
                    group deposit.Price by deposit.client into g
                    where g.Sum() > sum
                    select g).Count();
        }
        public IEnumerable<(string Name, decimal Total)> GetSumListByClient()
        {
            return (from deposit in deposits
                    group deposit.Price by deposit.client into g
                    select (g.Key.Name, g.Sum()));
                    //.ToDictionary((p) => p.Name, (p) => p.Price);

        }
    }
}
