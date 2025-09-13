using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _253502LishykK.Domain.Entities;

namespace _253502LishykK.Domain.Abstractions
{
    public interface IUnitOfWork
    {
        IRepository<Nomination> NominationRepository { get; }
        IRepository<Participant> ParticipantRepository { get; }
        Task SaveAllAsync();
        Task DeleteDataBaseAsync();
        Task CreateDataBaseAsync();
    }
}
