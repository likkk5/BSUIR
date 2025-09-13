using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _253502LishykK.Persistence.Data;

namespace _253502LishykK.Persistence.Repository
{
    public class EfUnitOfWork : IUnitOfWork
    {
        private readonly AppDbContext _context;
        private readonly Lazy<IRepository<Nomination>> _nominationRepository;
        private readonly Lazy<IRepository<Participant>> _participantRepository;
        // Добавьте репозитории для других сущностей по аналогии

        public EfUnitOfWork(AppDbContext context)
        {
            _context = context;
            _nominationRepository = new Lazy<IRepository<Nomination>>(() =>
                new EfRepository<Nomination>(context));
            _participantRepository = new Lazy<IRepository<Participant>>(() =>
                new EfRepository<Participant>(context));
            // Инициализируйте репозитории для других сущностей по аналогии
        }

        public IRepository<Nomination> NominationRepository => _nominationRepository.Value;
        public IRepository<Participant> ParticipantRepository => _participantRepository.Value;
        // Добавьте свойства для других репозиториев по аналогии

        public async Task CreateDataBaseAsync() => await _context.Database.EnsureCreatedAsync();

        public async Task DeleteDataBaseAsync() => await _context.Database.EnsureDeletedAsync();

        public async Task SaveAllAsync() => await _context.SaveChangesAsync();
    }
}
