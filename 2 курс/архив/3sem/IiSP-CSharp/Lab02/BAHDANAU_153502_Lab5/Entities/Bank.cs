using BAHDANAU_153502_Lab5.Collections;

namespace BAHDANAU_153502_Lab5.Entities
{
    public class Bank
    {
        private MyCustomCollection<Client> clients;
        private string bankName;
        public delegate void AddClientDelegate(string message);
        public event AddClientDelegate? AddClientEvent;
        public Bank(string bankName)
        {
            this.bankName = bankName;
            clients = new MyCustomCollection<Client>();
        }

        public string BankName
        {
            get { return bankName; }
        }

        public void AddClient(Client newClient)
        {
            clients.Add(newClient);
            AddClientEvent?.Invoke($"New client {newClient.Name}");
        }

        public decimal PayoutAmount
        {
            get
            {
                decimal payoutAmount = 0;
                int numClients = clients.Count;
                while (numClients-- > 0)
                {
                    payoutAmount += clients.Current().Payment;
                    clients.Next();
                }
                clients.Reset();
                return payoutAmount;
            }
        }
    }
}
