using Bahdanau_153502.Application.Abstractions;
using Bahdanau_153502.Domain.Abstractions;
using Bahdanau_153502.Domain.Entities;


namespace Bahdanau_153502.Application.Services
{
    public class LandmarkService : ILandmarkService
    {
        private readonly IUnitOfWork _unitOfWork;
        private readonly IRepository<Landmark> _landmarksRepository;

        public LandmarkService(IUnitOfWork unitOfWork)
        {
            _unitOfWork = unitOfWork;
            _landmarksRepository = unitOfWork.LandmarkRepository;
        }

        public async Task<Landmark> AddAsync(Landmark item)
        {
            await _unitOfWork.LandmarkRepository.AddAsync(item);
            await _unitOfWork.SaveAllAsync();
            return item;
        }

        public async Task<Landmark> DeleteAsync(int id)
        {
            Landmark item = await _landmarksRepository.GetByIdAsync(id);
            await _landmarksRepository.DeleteAsync(item);
            await _unitOfWork.SaveAllAsync();
            return item;
        }

        public async Task<IEnumerable<Landmark>> GetAllAsync()
        {
            return await _landmarksRepository.ListAllAsync();
        }

        public Task<Landmark> GetByIdAsync(int id)
        {
            return _landmarksRepository.GetByIdAsync(id);
        }

        public async Task<IEnumerable<Landmark>> GetLandmarksByTouristRoute(TouristRoute route)
        {
            return await _landmarksRepository.ListAsync((landmark) => landmark.TouristRouteId == route.Id);
        }

        public async Task<Landmark> UpdateAsync(Landmark item)
        {
            await _landmarksRepository.UpdateAsync(item);
            await _unitOfWork.SaveAllAsync();
            return item;
        }
    }
}
