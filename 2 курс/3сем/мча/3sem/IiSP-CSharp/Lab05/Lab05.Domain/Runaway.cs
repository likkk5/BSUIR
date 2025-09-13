namespace Lab05.Domain
{
    public class Runaway
    {
        public Runaway() { }
        public Runaway(int lenght, string name)
        {
            Lenght = lenght;
            Name = name;
        }

        public int Lenght { get; set; }
        public string Name { get; set; }


    }
}
