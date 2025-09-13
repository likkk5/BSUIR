//using System.Collections.ObjectModel;
//using _253502LishykK.Application.NominationUseCase.Queries;
//using _253502LishykK.Domain.Abstractions;
//using _253502LishykK.Domain.Entities;
//using _253502LishykK.UI.Pages;
//using CommunityToolkit.Mvvm.ComponentModel;
//using CommunityToolkit.Mvvm.Input;

//namespace _253502LishykK.UI.ViewModels
//{
//    public partial class ParticipantAddEditPageViewModel : ObservableObject
//    {
//        private readonly IMediator _mediator;
//        private readonly IUnitOfWork _unitOfWork;

//        public ParticipantAddEditPageViewModel(IMediator mediator, IUnitOfWork unitOfWork)
//        {
//            _mediator = mediator;
//            _unitOfWork = unitOfWork;
//        }

//        public string Name { get; set; }
//        public int MandatoryProperty { get; set; } // Количество баллов по итогам голосования
//        public string AdditionalProperty1 { get; set; }
//        public string AdditionalProperty2 { get; set; }
//        public ObservableCollection<Nomination> Nominations { get; set; } = new();
//        public ObservableCollection<Participant> Participants { get; set; } = new();

//        private Participant _selectedParticipant;
//        public Participant SelectedParticipant
//        {
//            get => _selectedParticipant;
//            set => SetProperty(ref _selectedParticipant, value);
//        }
//        private Nomination _selectedNomination;
//        public Nomination SelectedNomination
//        {
//            get => _selectedNomination;
//            set => SetProperty(ref _selectedNomination, value);
//        }
//        [RelayCommand]
//        async Task UpdateGroupList() => await LoadData();
//        public IAsyncRelayCommand LoadDataCommand => new AsyncRelayCommand(LoadData);

//        public async Task LoadData()
//        {
//            await LoadNominations();
//            await LoadParticipants();
//        }

//        public async Task LoadNominations()
//        {
//            try
//            {
//                var nominations = await _mediator.Send(new GetNominationsRequest());
//                Nominations.Clear();
//                foreach (var nomination in nominations)
//                    Nominations.Add(nomination);
//            }
//            catch (Exception ex)
//            {
//                return;
//            }
//        }

//        private IAsyncRelayCommand _saveCommand;
//        public IAsyncRelayCommand SaveCommand => _saveCommand ??= new AsyncRelayCommand(SaveParticipant);

//        [RelayCommand]
//        public async Task SaveParticipant()
//        {
//            if (SelectedParticipant == null)
//            {
//                var list = await _unitOfWork.ParticipantRepository.ListAllAsync(new CancellationToken());
//                var maxId = list.Max(c => c.Id);
//                var newParticipant = new Participant(Name, MandatoryProperty, AdditionalProperty1, AdditionalProperty2, SelectedNomination.Id, maxId + 1);
//                newParticipant.Nomination = SelectedNomination;
//                await _unitOfWork.ParticipantRepository.AddAsync(newParticipant);
//                await _unitOfWork.SaveAllAsync();
//                await LoadParticipants();
//                SelectedParticipant = Participants.FirstOrDefault(c => c.Id == newParticipant.Id);
//            }
//            else
//            {
//                SelectedParticipant.Name = Name;
//                SelectedParticipant.MandatoryProperty = MandatoryProperty;
//                SelectedParticipant.AdditionalProperty1 = AdditionalProperty1;
//                SelectedParticipant.AdditionalProperty2 = AdditionalProperty2;

//                await _unitOfWork.ParticipantRepository.UpdateAsync(SelectedParticipant);
//                await _unitOfWork.SaveAllAsync();

//                var selectedId = SelectedParticipant.Id;
//                await LoadParticipants();

//                SelectedParticipant = Participants.FirstOrDefault(c => c.Id == selectedId);
//            }
//            SelectedParticipant = null;
//        }
//        private IAsyncRelayCommand _loadParticipantsCommand;
//        public IAsyncRelayCommand LoadParticipantsCommand => _loadParticipantsCommand ??= new AsyncRelayCommand(LoadParticipants);

//        public async Task LoadParticipants()
//        {
//            if (SelectedNomination != null)
//            {
//                var participants = await _mediator.Send(new GetParticipantsByNominationQuery(SelectedNomination.Id.ToString()));
//                Participants.Clear();
//                foreach (var participant in participants)
//                    Participants.Add(participant);
//            }
//        }
//        private IRelayCommand<Participant> _selectParticipantCommand;
//        public IRelayCommand<Participant> SelectParticipantCommand => _selectParticipantCommand ??= new RelayCommand<Participant>(SelectParticipant);

//        public void SelectParticipant(Participant participant)
//        {
//            SelectedParticipant = participant;
//        }

//        private IRelayCommand _moveToGroupCommand;
//        public IRelayCommand MoveToGroupCommand => _moveToGroupCommand ??= new RelayCommand(async () => await MoveToGroup());

//        // Добавляем новое свойство для выбора целевой группы
//        private Nomination _selectedTargetNomination;
//        public Nomination SelectedTargetNomination
//        {
//            get => _selectedTargetNomination;
//            set => SetProperty(ref _selectedTargetNomination, value);
//        }

//        public async Task MoveToGroup()
//        {

//                if (SelectedParticipant != null && SelectedTargetNomination != null)
//                {
//                    SelectedParticipant.NominationId = SelectedTargetNomination.Id;
//                    await _unitOfWork.ParticipantRepository.UpdateAsync(SelectedParticipant);
//                    await _unitOfWork.SaveAllAsync();
//                    await LoadParticipants();
//                }
//                else
//                {
//                    // Обработка случая, когда не выбран участник или целевая группа
//                }
//        }
//    }
//}

using System.Threading.Tasks;
using _253502LishykK.Application.ParticipantUseCase.Commands;
using _253502LishykK.Domain.Abstractions;
using _253502LishykK.Domain.Entities;
using MediatR;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using _253502LishykK.Application.NominationUseCase.Queries;
using System.Collections.ObjectModel;
using System.Collections.Generic;
using _253502LishykK.Persistence.Repository;

namespace _253502LishykK.UI.ViewModels
{
    public partial class ParticipantAddEditPageViewModel : ObservableObject
    {
        private readonly IMediator _mediator;
        private readonly IUnitOfWork _unitOfWork;

        public ParticipantAddEditPageViewModel(IMediator mediator, IUnitOfWork unitOfWork)
        {
            _mediator = mediator;
            _unitOfWork = unitOfWork;
        }

        public string Name { get; set; }
        public int MandatoryProperty { get; set; }
        public string AdditionalProperty1 { get; set; }
        public string AdditionalProperty2 { get; set; }
        public ObservableCollection<Nomination> Nominations { get; set; } = new();
        public ObservableCollection<Participant> Participants { get; set; } = new();

        private Participant _selectedParticipant;
        public Participant SelectedParticipant
        {
            get => _selectedParticipant;
            set => SetProperty(ref _selectedParticipant, value);
        }

        private Nomination _selectedNomination;
        public Nomination SelectedNomination
        {
            get => _selectedNomination;
            set => SetProperty(ref _selectedNomination, value);
        }
        [RelayCommand]
        async Task UpdateGroupList() => await LoadData();
        public IAsyncRelayCommand LoadDataCommand => new AsyncRelayCommand(LoadData);

        private async Task LoadData()
        {
            await LoadNominations();
            await LoadParticipants();
        }

        private async Task LoadNominations()
        {
            var nominations = await _mediator.Send(new GetNominationsRequest());
            Nominations.Clear();
            foreach (var nomination in nominations)
                Nominations.Add(nomination);
        }
        private IAsyncRelayCommand _loadParticipantsCommand;
        public IAsyncRelayCommand LoadParticipantsCommand => _loadParticipantsCommand ??= new AsyncRelayCommand(LoadParticipants);


        private async Task LoadParticipants()
        {
            if (SelectedNomination != null)
            {
                var participants = await _mediator.Send(new GetParticipantsByNominationQuery(SelectedNomination.Id.ToString()));
                Participants.Clear();
                foreach (var participant in participants)
                    Participants.Add(participant);
            }
        }

        private IAsyncRelayCommand _saveCommand;
        public IAsyncRelayCommand SaveCommand => _saveCommand ??= new AsyncRelayCommand(SaveParticipant);

        public async Task SaveParticipant()
        {
            if (SelectedParticipant == null)
            {

                //                var list = await _unitOfWork.ParticipantRepository.ListAllAsync(new CancellationToken());
                //                var maxId = list.Max(c => c.Id);
                //                var newParticipant = new Participant(Name, MandatoryProperty, AdditionalProperty1, AdditionalProperty2, SelectedNomination.Id, maxId + 1);
                var list = await _unitOfWork.ParticipantRepository.ListAllAsync(new CancellationToken());
                var maxId = list.Max(c => c.Id);
                var command = new CreateParticipantCommand(Name, MandatoryProperty, AdditionalProperty1, AdditionalProperty2, SelectedNomination.Id, maxId + 1);
                await _mediator.Send(command);
            }
            else
            {
                var command = new UpdateParticipantCommand(SelectedParticipant.Id, Name, MandatoryProperty, AdditionalProperty1, AdditionalProperty2, SelectedNomination.Id);
                await _mediator.Send(command);
            }
            await LoadParticipants();
            SelectedParticipant = null; // Очищаем выбранного участника после сохранения
        }
        private IRelayCommand<Participant> _selectParticipantCommand;
        public IRelayCommand<Participant> SelectParticipantCommand => _selectParticipantCommand ??= new RelayCommand<Participant>(SelectParticipant);

        public void SelectParticipant(Participant participant)
        {
            SelectedParticipant = participant;
        }

        private IRelayCommand _moveToGroupCommand;
        public IRelayCommand MoveToGroupCommand => _moveToGroupCommand ??= new RelayCommand(async () => await MoveParticipant());


        // Добавляем новое свойство для выбора целевой группы
        private Nomination _selectedTargetNomination;
        public Nomination SelectedTargetNomination
        {
            get => _selectedTargetNomination;
            set => SetProperty(ref _selectedTargetNomination, value);
        }
        public async Task MoveParticipant()
        {
            if (SelectedParticipant != null && SelectedTargetNomination != null)
            {
                var command = new MoveParticipantCommand(SelectedParticipant.Id, SelectedTargetNomination.Id);
                await _mediator.Send(command);
                await LoadParticipants();
            }
            else
            {
                // Обработка случая, когда не выбран участник или целевая группа
            }
        }
    }
}

