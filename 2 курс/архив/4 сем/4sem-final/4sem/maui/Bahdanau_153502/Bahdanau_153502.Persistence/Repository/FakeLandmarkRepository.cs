using Bahdanau_153502.Domain.Abstractions;
using Bahdanau_153502.Domain.Entities;
using System.Linq.Expressions;

namespace Bahdanau_153502.Persistence.Repository
{
    public class FakeLandmarkRepository : IRepository<Landmark>
    {
        List<Landmark> _landmarks;

        public FakeLandmarkRepository()
        {
            _landmarks = new List<Landmark>();
            for (int i = 1; i <= 2; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    _landmarks.Add(new Landmark
                    {
                        Id = ((i - 1) * 10) + j,
                        Description = $"Landmark-{i}-{j}",
                        TicketPrice = 100 * (Random.Shared.Next() % 2) + 100,
                        TouristRouteId = i,
                        City = $"City-{i}-{j}",
                    });
                }
            }
        }

        public Task AddAsync(Landmark entity, CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }

        public Task DeleteAsync(Landmark entity, CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }

        public Task<Landmark> FirstOrDefaultAsync(Expression<Func<Landmark, bool>> filter, CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }

        public Task<Landmark> GetByIdAsync(int id, CancellationToken cancellationToken = default, params Expression<Func<Landmark, object>>[]? includesProperties)
        {
            throw new NotImplementedException();
        }

        public Task<IReadOnlyList<Landmark>> ListAllAsync(CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }

        public Task<IReadOnlyList<Landmark>> ListAsync(Expression<Func<Landmark, bool>> filter, CancellationToken cancellationToken = default, params Expression<Func<Landmark, object>>[]? includesProperties)
        {
            IQueryable<Landmark> data = _landmarks.AsQueryable();
            return Task.Run(() => data.Where(filter).ToList() as IReadOnlyList<Landmark>);
        }

        public Task UpdateAsync(Landmark entity, CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }
    }
}
