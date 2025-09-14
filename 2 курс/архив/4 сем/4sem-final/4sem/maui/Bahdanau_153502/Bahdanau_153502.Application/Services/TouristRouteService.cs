using Bahdanau_153502.Application.Abstractions;
using Bahdanau_153502.Domain.Abstractions;
using Bahdanau_153502.Domain.Entities;

namespace Bahdanau_153502.Application.Services
{
    public class TouristRouteService : ITouristRouteService
    {
        private readonly IUnitOfWork _unitOfWork;
        private readonly IRepository<TouristRoute> _touristRouteRepository;

        public TouristRouteService(IUnitOfWork unitOfWork)
        {
            _unitOfWork = unitOfWork;
            _touristRouteRepository = unitOfWork.TouristRouteRepository;
        }
        public async Task<TouristRoute> AddAsync(TouristRoute item)
        {
            await _touristRouteRepository.AddAsync(item);
            await _unitOfWork.SaveAllAsync();
            return item;
        }

        public async Task<TouristRoute> DeleteAsync(int id)
        {
            TouristRoute item = await _touristRouteRepository.GetByIdAsync(id);
            await _touristRouteRepository.DeleteAsync(item);
            await _unitOfWork.SaveAllAsync();
            return item;
        }

        public async Task<IEnumerable<TouristRoute>> GetAllAsync()
        {
            return await _touristRouteRepository.ListAllAsync();
        }

        public Task<TouristRoute> GetByIdAsync(int id)
        {
            return _touristRouteRepository.GetByIdAsync(id);
        }

        public async Task<TouristRoute> UpdateAsync(TouristRoute item)
        {
            await _touristRouteRepository.UpdateAsync(item);
            await _unitOfWork.SaveAllAsync();
            return item;
        }
    }
}
