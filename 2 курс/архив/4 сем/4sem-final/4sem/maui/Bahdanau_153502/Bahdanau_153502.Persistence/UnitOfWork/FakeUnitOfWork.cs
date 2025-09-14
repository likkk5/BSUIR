using Bahdanau_153502.Domain.Abstractions;
using Bahdanau_153502.Domain.Entities;
using Bahdanau_153502.Persistence.Repository;

namespace Bahdanau_153502.Persistence.UnitOfWork
{
    public class FakeUnitOfWork : IUnitOfWork
    {
        private readonly FakeLandmarkRepository _landmarkRepository;
        private readonly FakeTouristRouteRepository _touristRouteRepository;

        public FakeUnitOfWork()
        {
            _landmarkRepository = new();
            _touristRouteRepository = new();
        }
        public IRepository<Landmark> LandmarkRepository => _landmarkRepository;

        public IRepository<TouristRoute> TouristRouteRepository => _touristRouteRepository;

        public Task CreateDatabaseAsync()
        {
            throw new NotImplementedException();
        }

        public Task RemoveDatbaseAsync()
        {
            throw new NotImplementedException();
        }

        public Task SaveAllAsync()
        {
            throw new NotImplementedException();
        }
    }
}
