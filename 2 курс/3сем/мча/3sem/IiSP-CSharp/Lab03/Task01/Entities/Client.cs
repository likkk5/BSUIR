namespace BAHDANAU_153502_Lab5.Entities
{
    public class Client
    {
        private string name;

        public Client(string name)
        {
            this.name = name;
        }

        public string Name
        {
            get
            {
                return name;
            }
        }
    }
}
