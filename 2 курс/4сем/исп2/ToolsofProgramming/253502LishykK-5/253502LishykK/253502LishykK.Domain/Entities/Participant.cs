using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _253502LishykK.Domain.Entities
{
    public class Participant : Entity
    {
        public string Name { get; set; }
        public int MandatoryProperty { get; set; } // Количество баллов по итогам голосования
        public string AdditionalProperty1 { get; set; }
        public string AdditionalProperty2 { get; set; }
        public int NominationId { get; set; }
        public Nomination Nomination { get; set; }
        private Participant() { }

        public Participant(string name, int mandatoryProperty, string additionalProperty1, string additionalProperty2, int nominationId, int id)
        {
            Name = name;
            MandatoryProperty = mandatoryProperty;
            AdditionalProperty1 = additionalProperty1;
            AdditionalProperty2 = additionalProperty2;
            NominationId = nominationId;
            Id = id;
        }

        // Дополнительные бизнес-методы
        public void UpdateParticipantInfo(int newMandatoryProperty, string newAdditionalProperty1, string newAdditionalProperty2)
        {
            MandatoryProperty = newMandatoryProperty;
            AdditionalProperty1 = newAdditionalProperty1;
            AdditionalProperty2 = newAdditionalProperty2;
        }
        public void UpdateParticipant(string newName, int newMandatoryProperty, string newAdditionalProperty1, string newAdditionalProperty2)
        {
            // Логика обновления всей информации об участнике
            Name = newName;
            MandatoryProperty = newMandatoryProperty;
            AdditionalProperty1 = newAdditionalProperty1;
            AdditionalProperty2 = newAdditionalProperty2;
        }
    }
}
