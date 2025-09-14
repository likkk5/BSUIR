using Lab05.Domain;
using System.Text.Json;
using System.Xml.Linq;
using System.Xml.Serialization;

namespace Serializer
{
    public class Serializer : ISerializer
    {
        public IEnumerable<Airoport> DeSerializeByLINQ(string fileName)
        {
            XDocument xDocument = XDocument.Load(fileName);
            return (from airoport in xDocument.Descendants("airoport")
                    select new Airoport(
                           (string)airoport.Element("name"),
                           (from runaway in airoport.Descendants("runaway")
                            select new Runaway(
                                    (int)runaway.Element("lenght"),
                                    (string)runaway.Element("name")
                                )).ToList()
                        ));
        }

        public IEnumerable<Airoport> DeSerializeJSON(string fileName)
        {
            string jsonString = File.ReadAllText(fileName);
            var list = JsonSerializer.Deserialize<List<Airoport>>(jsonString);
            foreach (var item in list)
            {
                yield return item;
            }
        }

        public IEnumerable<Airoport> DeSerializeXML(string fileName)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(List<Airoport>));
            using (FileStream fs = new FileStream(fileName, FileMode.OpenOrCreate))
            {
                var list = (List<Airoport>)serializer.Deserialize(fs);
                foreach (var item in list)
                {
                    yield return item;
                }
            }
        }

        public void SerializeByLINQ(IEnumerable<Airoport> list, string fileName)
        {
            XDocument xDocument = new XDocument();
            XElement xAiroports = new XElement("airoports");
            foreach (Airoport airoport in list)
            {
                XElement xAiroport = new XElement("airoport");
                xAiroport.Add(new XElement("name", airoport.Name));
                XElement xRunaways = new XElement("runaways");
                foreach (Runaway runaway in airoport.Runaways)
                {
                    XElement xRunaway = new XElement("runaway");
                    xRunaway.Add(new XElement("name", runaway.Name));
                    xRunaway.Add(new XElement("lenght", runaway.Lenght));
                    xRunaways.Add(xRunaway);
                }
                xAiroport.Add(xRunaways);
                xAiroports.Add(xAiroport);
            }
            xDocument.Add(xAiroports);
            xDocument.Save(fileName);
        }

        public void SerializeJSON(IEnumerable<Airoport> list, string fileName)
        {
            string jsonString = JsonSerializer.Serialize(list);
            File.WriteAllText(fileName, jsonString);
        }

        public void SerializeXML(IEnumerable<Airoport> list, string fileName)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(List<Airoport>));
            using (FileStream fs = new FileStream(fileName, FileMode.OpenOrCreate))
            {
                serializer.Serialize(fs, list);
            }
        }
    }
}