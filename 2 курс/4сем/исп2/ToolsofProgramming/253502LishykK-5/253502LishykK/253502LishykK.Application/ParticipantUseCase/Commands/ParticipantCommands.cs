using System.Threading;
using System.Threading.Tasks;
using MediatR;
using _253502LishykK.Domain.Abstractions;

namespace _253502LishykK.Application.ParticipantUseCase.Commands
{
    public record CreateParticipantCommand(string Name, int MandatoryProperty, string AdditionalProperty1, string AdditionalProperty2, int NominationId, int Id) : IRequest<int>;

    public record UpdateParticipantCommand(int ParticipantId, string Name, int MandatoryProperty, string AdditionalProperty1, string AdditionalProperty2, int NominationId) : IRequest<Unit>;

    public record MoveParticipantCommand(int ParticipantId, int TargetNominationId) : IRequest<Unit>;

    public class CreateParticipantCommandHandler : IRequestHandler<CreateParticipantCommand, int>
    {
        private readonly IUnitOfWork _unitOfWork;

        public CreateParticipantCommandHandler(IUnitOfWork unitOfWork)
        {
            _unitOfWork = unitOfWork;
        }

        public async Task<int> Handle(CreateParticipantCommand request, CancellationToken cancellationToken)
        {
            var participant = new Participant(request.Name, request.MandatoryProperty, request.AdditionalProperty1, request.AdditionalProperty2, request.NominationId, request.Id);
            await _unitOfWork.ParticipantRepository.AddAsync(participant);
            await _unitOfWork.SaveAllAsync();
            return participant.Id;
        }
    }

    public class UpdateParticipantCommandHandler : IRequestHandler<UpdateParticipantCommand, Unit>
    {
        private readonly IUnitOfWork _unitOfWork;

        public UpdateParticipantCommandHandler(IUnitOfWork unitOfWork)
        {
            _unitOfWork = unitOfWork;
        }

        public async Task<Unit> Handle(UpdateParticipantCommand request, CancellationToken cancellationToken)
        {
            var participant = await _unitOfWork.ParticipantRepository.GetByIdAsync(request.ParticipantId);
            if (participant != null)
            {
                participant.Name = request.Name;
                participant.MandatoryProperty = request.MandatoryProperty;
                participant.AdditionalProperty1 = request.AdditionalProperty1;
                participant.AdditionalProperty2 = request.AdditionalProperty2;
                participant.NominationId = request.NominationId;

                await _unitOfWork.ParticipantRepository.UpdateAsync(participant);
                await _unitOfWork.SaveAllAsync();
            }
            return Unit.Value;
        }
    }

    public class MoveParticipantCommandHandler : IRequestHandler<MoveParticipantCommand, Unit>
    {
        private readonly IUnitOfWork _unitOfWork;

        public MoveParticipantCommandHandler(IUnitOfWork unitOfWork)
        {
            _unitOfWork = unitOfWork;
        }

        public async Task<Unit> Handle(MoveParticipantCommand request, CancellationToken cancellationToken)
        {
            var participant = await _unitOfWork.ParticipantRepository.GetByIdAsync(request.ParticipantId);
            if (participant != null)
            {
                participant.NominationId = request.TargetNominationId;
                await _unitOfWork.ParticipantRepository.UpdateAsync(participant);
                await _unitOfWork.SaveAllAsync();
            }
            return Unit.Value;
        }
    }
}
