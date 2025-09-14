using Lab05.Domain;

List<Airoport> airoports = new List<Airoport>();
Airoport airoport1 = new Airoport("airoport1");
Airoport airoport2 = new Airoport("airoport2");
airoport1.AddRunaway(new Runaway(110, "runaway11"));
airoport1.AddRunaway(new Runaway(120, "runaway12"));
airoport2.AddRunaway(new Runaway(210, "runaway21"));
airoport2.AddRunaway(new Runaway(220, "runaway22"));
Serializer.Serializer serializer = new Serializer.Serializer();

airoports.Add(airoport1);
airoports.Add(airoport2);
serializer.SerializeJSON(airoports, "file.json");
serializer.SerializeByLINQ(airoports, "file.linq");
serializer.SerializeXML(airoports, "file.xml");

foreach (Airoport airoport in serializer.DeSerializeJSON("file.json"))
{
    Console.WriteLine(airoport.Name);
    foreach (var runaway in airoport.Runaways)
    {
        Console.WriteLine($"{runaway.Name} {runaway.Lenght}");
    }
    Console.WriteLine();
}

foreach (Airoport airoport in serializer.DeSerializeXML("file.xml"))
{
    Console.WriteLine(airoport.Name);
    foreach (var runaway in airoport.Runaways)
    {
        Console.WriteLine($"{runaway.Name} {runaway.Lenght}");
    }
    Console.WriteLine();
}

foreach (Airoport airoport in serializer.DeSerializeByLINQ("file.linq"))
{
    Console.WriteLine(airoport.Name);
    foreach (var runaway in airoport.Runaways)
    {
        Console.WriteLine($"{runaway.Name} {runaway.Lenght}");
    }
    Console.WriteLine();
}