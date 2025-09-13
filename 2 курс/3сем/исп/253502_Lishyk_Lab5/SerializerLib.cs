using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Xml;
using System.Xml.Linq;
using System.Xml.Serialization;
using Newtonsoft.Json; //NewtonSoft.Json
using static _253502_Lishyk_Lab5.Lab5_Domain;

namespace _253502_Lishyk_Lab5
{
    public class Serializer : ISerializer
    {
        public IEnumerable<Ticket> DeSerializeByLINQ(string fileName)
        {
            if (!File.Exists(fileName))
            {
                throw new FileNotFoundException("Файл не найден.", fileName);
            }

            XDocument doc = XDocument.Load(fileName); //метод загружает содержимое файла в объект XDocument, который представляет XML-документ
            return doc.Descendants("Ticket")//коллекция объектов Ticket, представляющих данные, считанные из файла.
                .Select(t => new Ticket //выполняет LINQ-запрос к элементам XML с тегом Ticket и создает объекты типа Ticket, используя значения из XML
                {
                    TicketNumber = (int)t.Element("TicketNumber"),
                    Price = (double)t.Element("Price"),
                    Passenger = new Passenger
                    {
                        Name = (string)t.Element("Passenger").Element("Name"),
                        PassportNumber = (string)t.Element("Passenger").Element("PassportNumber")
                    }
                });
        }

        public IEnumerable<Ticket> DeSerializeXML(string fileName)
        {
            if (!File.Exists(fileName))
            {
                throw new FileNotFoundException("Файл не найден.", fileName);
            }

            XmlSerializer serializer = new XmlSerializer(typeof(List<Ticket>));//создает объект, который используется для десериализации XML-данных.
            using (FileStream fileStream = new FileStream(fileName, FileMode.Open))//открывает файл для чтения и выполняет десериализацию данных в объекты типа Ticket из XML-файла.
            {
                return (List<Ticket>)serializer.Deserialize(fileStream);
            }
        }

        public IEnumerable<Ticket> DeSerializeJSON(string fileName)
        {
            if (!File.Exists(fileName))
            {
                throw new FileNotFoundException("Файл не найден.", fileName);
            }

            string json = File.ReadAllText(fileName);
            return JsonConvert.DeserializeObject<List<Ticket>>(json); //десериализации JSON в коллекцию объектов типа Ticket.
        }

        public void SerializeByLINQ(IEnumerable<Ticket> tickets, string fileName) //метод выполняет LINQ-запрос, чтобы создать XML-структуру, соответствующую коллекции объектов Ticket
        {
            XDocument doc = new XDocument(
                new XElement("Tickets",
                    from ticket in tickets
                    select new XElement("Ticket",
                        new XElement("TicketNumber", ticket.TicketNumber),
                        new XElement("Price", ticket.Price),
                        new XElement("Passenger",
                            new XElement("Name", ticket.Passenger.Name),
                            new XElement("PassportNumber", ticket.Passenger.PassportNumber)
                        )
                    )
                )
            );
            doc.Save(fileName);
        }

        public void SerializeXML(IEnumerable<Ticket> tickets, string fileName)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(List<Ticket>));
            using (FileStream fileStream = new FileStream(fileName, FileMode.Create))
            {
                serializer.Serialize(fileStream, tickets.ToList());
            }
        }

        public void SerializeJSON(IEnumerable<Ticket> tickets, string fileName)
        {
            string json = JsonConvert.SerializeObject(tickets, Newtonsoft.Json.Formatting.Indented);
            File.WriteAllText(fileName, json);
        }

    }

}
