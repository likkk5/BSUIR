namespace Lab05.Domain
{
    public class Airoport
    {
        public Airoport() { }
        public Airoport(string name)
        {
            Name = name;
            Runaways = new List<Runaway>();
        }
        public Airoport(string name, List<Runaway> list)
        {
            Name = name;
            Runaways = list;
        }

        public string Name { get; set; }
        public List<Runaway> Runaways { get; set; }

        public void AddRunaway(Runaway runaway)
        {
            Runaways.Add(runaway);
        }

    }
}
