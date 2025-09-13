using _253502_Lishyk_Lab5;
using static _253502_Lishyk_Lab5.Lab5_Domain;
class Program
{
    static void Main(string[] args)
    {
        List<Ticket> tickets = new List<Ticket>
        { 
            new Ticket
            {
                TicketNumber = 1,
                Price = 100.0,
                Passenger = new Passenger { Name = "John Doe", PassportNumber = "MP1234567" }

            },
            new Ticket
            {
                TicketNumber = 2,
                Price = 120.0,
                Passenger = new Passenger { Name = "Alice Smith", PassportNumber = "MP7654321" }
            },
            new Ticket
            {
                TicketNumber = 3,
                Price = 90.0,
                Passenger = new Passenger { Name = "Jane Doe", PassportNumber = "MC1357913" }
            },
            new Ticket
            {
                TicketNumber = 4,
                Price = 80.0,
                Passenger = new Passenger { Name = "Jack Smith", PassportNumber = "KB2468024" }
            },
            new Ticket
            {
                TicketNumber = 5,
                Price = 75.5,
                Passenger = new Passenger { Name = "Bob Johnson", PassportNumber = "PP0192837" }
            },

        };


        Serializer serializer = new Serializer();

        // Запись в файлы
        serializer.SerializeByLINQ(tickets, "ticketsByLINQ.xml");
        serializer.SerializeXML(tickets, "ticketsXML.xml");
        serializer.SerializeJSON(tickets, "ticketsJSON.json");

        // Чтение из файлов
        IEnumerable<Ticket> ticketsFromLINQ = serializer.DeSerializeByLINQ("ticketsByLINQ.xml");
        IEnumerable<Ticket> ticketsFromXML = serializer.DeSerializeXML("ticketsXML.xml");
        IEnumerable<Ticket> ticketsFromJSON = serializer.DeSerializeJSON("ticketsJSON.json");
    

        // Вывод результатов в консоль
        foreach (var ticket in ticketsFromLINQ)
        {
            Console.WriteLine($"Ticket Number: {ticket.TicketNumber}");
            Console.WriteLine($"Price: {ticket.Price}");
            Console.WriteLine($"Passenger Name: {ticket.Passenger.Name}");
            Console.WriteLine($"Passport Number: {ticket.Passenger.PassportNumber}");
            Console.WriteLine();
        }

        bool isDataEqualLINQ = tickets.SequenceEqual(ticketsFromLINQ);
        bool isDataEqualXML = tickets.SequenceEqual(ticketsFromXML);
        bool isDataEqualJSON = tickets.SequenceEqual(ticketsFromJSON);

        if (isDataEqualLINQ)
        {
            Console.WriteLine("Данные после десериализации из LINQ совпадают с исходными данными.");
        }
        else
        {
            Console.WriteLine("Данные после десериализации из LINQ не совпадают с исходными данными.");
        }

        if (isDataEqualXML)
        {
            Console.WriteLine("Данные после десериализации из XML совпадают с исходными данными.");
        }
        else
        {
            Console.WriteLine("Данные после десериализации из XML не совпадают с исходными данными.");
        }

        if (isDataEqualJSON)
        {
            Console.WriteLine("Данные после десериализации из JSON совпадают с исходными данными.");
        }
        else
        {
            Console.WriteLine("Данные после десериализации из JSON не совпадают с исходными данными.");
        }

    }
}