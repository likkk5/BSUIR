namespace BAHDANAU_153502_Lab5.Entities
{
    public class Deposit
    {

        public Deposit(decimal price, int percent)
        {
            this.price = price;
            this.percent = percent;
        }

        private decimal price;
        private int percent;

        public void IncreaseDeposit(decimal price)
        {
            this.price += price;
        }

        public decimal Payment 
        { 
            get { return price * percent / 100; } 
        }
    }
}
