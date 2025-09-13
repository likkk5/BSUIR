using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static _253502_Lishyk_Lab5.Lab5_Domain;

namespace _253502_Lishyk_Lab5
{
    public class Lab5_Domain
    {
        public class Passenger : IEquatable<Passenger> //контейнеризируемый класс
        {
            public string Name { get; set; }
            public string PassportNumber { get; set; }

            public bool Equals(Passenger other)
            {
                if (other == null)
                    return false;

                return this.Name == other.Name && this.PassportNumber == other.PassportNumber;
            }

            public override bool Equals(object obj)
            {
                if (obj is Passenger passenger)
                {
                    return Equals(passenger);
                }

                return false;
            }

            public override int GetHashCode()
            {
                return (Name.GetHashCode() * 397) ^ PassportNumber.GetHashCode();
            }
        }
 

        public class Ticket : IEquatable<Ticket> //класс-контейнер
        {
            public int TicketNumber { get; set; }
            public double Price { get; set; }
            public Passenger Passenger { get; set; }

            public bool Equals(Ticket other)
            {
                if (other == null)
                    return false;

                return this.TicketNumber == other.TicketNumber && this.Price == other.Price && this.Passenger.Equals(other.Passenger);
            }

            public override bool Equals(object obj)
            {
                if (obj is Ticket ticket)
                {
                    return Equals(ticket);
                }

                return false;
            }

            public override int GetHashCode()
            {
                return (TicketNumber * 397) ^ Price.GetHashCode() ^ Passenger.GetHashCode();
            }
        }

    }
    public interface ISerializer
    {
        IEnumerable<Ticket> DeSerializeByLINQ(string fileName);
        IEnumerable<Ticket> DeSerializeXML(string fileName);
        IEnumerable<Ticket> DeSerializeJSON(string fileName);
        void SerializeByLINQ(IEnumerable<Ticket> tickets, string fileName);
        void SerializeXML(IEnumerable<Ticket> tickets, string fileName);
        void SerializeJSON(IEnumerable<Ticket> tickets, string fileName);
    }


}
