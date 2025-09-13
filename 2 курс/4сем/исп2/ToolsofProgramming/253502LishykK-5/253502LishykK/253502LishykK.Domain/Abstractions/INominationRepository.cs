using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _253502LishykK.Domain.Entities;

namespace _253502LishykK.Domain.Abstractions
{
    public interface INominationRepository : IRepository<Nomination>
    {
        Task<List<Participant>> GetParticipantsAsync(int nominationId);
        Task AddParticipantAsync(int nominationId, string participantName, int mandatoryProperty, string additionalProperty1, string additionalProperty2);
        Task RemoveParticipantAsync(int nominationId, int participantId);
        Task UpdateNominationAsync(int nominationId, string newName);
    }
}
