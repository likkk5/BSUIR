using Bahdanau_153502.Domain.Entities;

namespace Bahdanau_153502.Domain.Abstractions
{
    public interface IUnitOfWork
    {

        IRepository<Landmark> LandmarkRepository { get; }
        IRepository<TouristRoute> TouristRouteRepository { get; }
        public Task RemoveDatbaseAsync();
        public Task CreateDatabaseAsync();
        public Task SaveAllAsync();
    }
}
