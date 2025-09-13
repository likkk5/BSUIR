using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _253502LishykK.Domain.Entities;

namespace _253502LishykK.Domain.Abstractions
{
    public interface IParticipantRepository : IRepository<Participant>
    {
        Task UpdateParticipantInfoAsync(int participantId, int newMandatoryProperty, string newAdditionalProperty1, string newAdditionalProperty2);
        Task UpdateParticipantAsync(int participantId, string newName, int newMandatoryProperty, string newAdditionalProperty1, string newAdditionalProperty2);
    }
}
