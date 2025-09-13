using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _253502LishykK.Application.NominationUseCase.Queries
{
    //public sealed record GetNominationWithParticipantsQuery : IRequest<IEnumerable<Nomination>>
    //{
    //    public string NominationId { get; init; }

    //    public GetNominationWithParticipantsQuery(string nominationId)
    //    {
    //        NominationId = nominationId;
    //    }
    //}
    // Запрос на получение списка участников номинации
    public sealed record GetParticipantsByNominationQuery(string NominationId) : IRequest<IEnumerable<Participant>>
    { }

    // Обработчик запроса
    internal class GetParticipantsByNominationQueryHandler : IRequestHandler<GetParticipantsByNominationQuery, IEnumerable<Participant>>
    {
        private readonly IUnitOfWork _unitOfWork;

        public GetParticipantsByNominationQueryHandler(IUnitOfWork unitOfWork)
        {
            _unitOfWork = unitOfWork;
        }

        public async Task<IEnumerable<Participant>> Handle(GetParticipantsByNominationQuery request, CancellationToken cancellationToken)
        {
            // Получаем список участников номинации с помощью Unit of Work
            return await _unitOfWork.ParticipantRepository.GetParticipantsByNominationAsync(request.NominationId, cancellationToken);
        }
    }
    public sealed record GetNominationsRequest : IRequest<IEnumerable<Nomination>>
    { }

    // Обработчик запроса для получения списка всех номинаций
    internal class GetNominationsRequestHandler : IRequestHandler<GetNominationsRequest, IEnumerable<Nomination>>
    {
        private readonly IUnitOfWork _unitOfWork;

        public GetNominationsRequestHandler(IUnitOfWork unitOfWork)
        {
            _unitOfWork = unitOfWork;
        }

        public async Task<IEnumerable<Nomination>> Handle(GetNominationsRequest request, CancellationToken cancellationToken)
        {
            // Получаем список всех номинаций с помощью Unit of Work
            return await _unitOfWork.NominationRepository.GetAllAsync(cancellationToken);
        }
    }
}
