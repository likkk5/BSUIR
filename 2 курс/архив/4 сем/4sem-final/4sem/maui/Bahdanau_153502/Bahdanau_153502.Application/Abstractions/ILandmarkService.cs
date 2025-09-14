using Bahdanau_153502.Domain.Entities;

namespace Bahdanau_153502.Application.Abstractions
{
    public interface ILandmarkService : IBaseService<Landmark>
    {
        Task<IEnumerable<Landmark>> GetLandmarksByTouristRoute(TouristRoute route);
    }
}
