using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _253502LishykK.Persistence.Repository
{
    public class FakeUnitOfWork : IUnitOfWork
    {
        private readonly Lazy<IRepository<Nomination>> _nominationRepository;
        private readonly Lazy<IRepository<Participant>> _participantRepository;

        public FakeUnitOfWork()
        {
            _nominationRepository = new Lazy<IRepository<Nomination>>(() =>
                new FakeNominationRepository());

            _participantRepository = new Lazy<IRepository<Participant>>(() =>
                new FakeParticipantRepository());
        }

        public IRepository<Nomination> NominationRepository => _nominationRepository.Value;
        public IRepository<Participant> ParticipantRepository => _participantRepository.Value;

        // Добавьте свойства для других репозиториев по аналогии

        public async Task CreateDataBaseAsync() => await Task.CompletedTask;

        public async Task DeleteDataBaseAsync() => await Task.CompletedTask;

        public async Task SaveAllAsync() => await Task.CompletedTask;
    }
}
