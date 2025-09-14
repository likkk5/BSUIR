using Bahdanau_153502.Domain.Abstractions;
using Bahdanau_153502.Domain.Entities;
using Bahdanau_153502.Persistence.Data;
using Bahdanau_153502.Persistence.Repository;

namespace Bahdanau_153502.Persistence.UnitOfWork
{
    public class EfUnitOfWork : IUnitOfWork
    {
        private readonly AppDbContext _context;
        private readonly Lazy<IRepository<Landmark>> _landmarkRepository;
        private readonly Lazy<IRepository<TouristRoute>> _touristRouteRepository;
        public EfUnitOfWork(AppDbContext context)
        {
            _context = context;
            _landmarkRepository = new(() => new EfRepository<Landmark>(context));
            _touristRouteRepository = new(() => new EfRepository<TouristRoute>(context));
        }

        public async Task CreateDatabaseAsync()
        {
            await _context.Database.EnsureCreatedAsync();
        }
        public async Task RemoveDatbaseAsync()
        {
            await _context.Database.EnsureDeletedAsync();
        }
        public async Task SaveAllAsync()
        {
            await _context.SaveChangesAsync();
        }

        public IRepository<Landmark> LandmarkRepository => _landmarkRepository.Value;

        public IRepository<TouristRoute> TouristRouteRepository => _touristRouteRepository.Value;

    }
}
