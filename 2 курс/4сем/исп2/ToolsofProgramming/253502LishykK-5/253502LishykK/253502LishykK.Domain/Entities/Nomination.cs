using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _253502LishykK.Domain.Entities
{
    public class Nomination : Entity
    {
        public string Name { get; set; }
        public List<Participant> Participants { get; set; } = new List<Participant>();

        private Nomination() { }

        public Nomination(string name, int id)
        {
            Name = name;
            Id = id;
        }

        // Дополнительные бизнес-методы
        public void AddParticipant(string participantName, int mandatoryProperty, string additionalProperty1, string additionalProperty2)
        {
            var participant = new Participant(participantName, mandatoryProperty, additionalProperty1, additionalProperty2, this.Id, Id);
            Participants.Add(participant);
        }

        public void RemoveParticipant(int participantId)
        {
            var participant = Participants.FirstOrDefault(p => p.Id == participantId);
            if (participant != null)
            {
                Participants.Remove(participant);
            }
        }
        public void UpdateNomination(string newName)
        {
            // Проверки на валидность новых данных
            if (string.IsNullOrWhiteSpace(newName))
            {
                throw new ArgumentException("Invalid name");
            }

            Name = newName;
        }
    }
}
