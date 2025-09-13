using BAHDANAU_153502_Lab5.Collections;

namespace BAHDANAU_153502_Lab5.Entities
{
    public class Client
    {
        private string name;
        private MyCustomCollection<Deposit> deposits;
        public delegate void AddDepositDelegate(string message);
        public event AddDepositDelegate? AddDepositEvent;

        public Client(string name)
        {
            this.name = name;
            deposits = new MyCustomCollection<Deposit>();
        }

        public void AddDeposit(Deposit deposit)
        {
            deposits.Add(deposit);
            AddDepositEvent?.Invoke($"New deposit by {Name}");
        } 

        public string Name 
        {
            get 
            {
                return name;
            } 
        }
        public decimal Payment { 
            get 
            {
                decimal result = 0;
                int numDeposits = deposits.Count;
                while (numDeposits-- > 0)
                {
                    result += deposits.Current().Payment;
                    deposits.Next();
                }
                deposits.Reset();
                return result;
            } 
        }
    }
}
