using Bahdanau_153502.Domain.Abstractions;
using Bahdanau_153502.Domain.Entities;
using System.Linq.Expressions;

namespace Bahdanau_153502.Persistence.Repository
{
    public class FakeTouristRouteRepository : IRepository<TouristRoute>
    {
        private readonly List<TouristRoute> _routes;

        public FakeTouristRouteRepository()
        {
            _routes = new List<TouristRoute>()
            {
                new TouristRoute()
                {
                    DistanceInKm = 1,
                    Id = 1,
                    Landmarks= new List<Landmark>(),
                    Title="Title1"
                },
                new TouristRoute()
                {
                    DistanceInKm = 2,
                    Id = 2,
                    Landmarks= new List<Landmark>(),
                    Title="Title2"
                },
            };
        }

        public Task AddAsync(TouristRoute entity, CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }

        public Task DeleteAsync(TouristRoute entity, CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }

        public Task<TouristRoute> FirstOrDefaultAsync(Expression<Func<TouristRoute, bool>> filter, CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }

        public Task<TouristRoute> GetByIdAsync(int id, CancellationToken cancellationToken = default, params Expression<Func<TouristRoute, object>>[]? includesProperties)
        {
            throw new NotImplementedException();
        }

        public Task<IReadOnlyList<TouristRoute>> ListAllAsync(CancellationToken cancellationToken = default)
        {
            return Task.Run(() => _routes as IReadOnlyList<TouristRoute>);
        }

        public Task<IReadOnlyList<TouristRoute>> ListAsync(Expression<Func<TouristRoute, bool>> filter, CancellationToken cancellationToken = default, params Expression<Func<TouristRoute, object>>[]? includesProperties)
        {
            throw new NotImplementedException();
        }

        public Task UpdateAsync(TouristRoute entity, CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }
    }
}
