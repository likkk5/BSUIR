namespace BAHDANAU_153502_Lab5.Entities
{
    public class Deposit
    {

        public Deposit(Client client, decimal price, int percent)
        {
            this.client = client;
            this.price = price;
            this.percent = percent;
        }

        public Client client;
        private decimal price;
        private int percent;

        public void IncreaseDeposit(decimal price)
        {
            this.price += price;
        }

        public int Percent
        {
            get
            {
                return percent;
            }
        }
        public string GetName()
        {
            return client.Name;
        }


        public decimal Price
        {
            get { return price; }
        }
    }
}
