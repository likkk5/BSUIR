using System.Collections.ObjectModel;
using _253502LishykK.Application.NominationUseCase.Queries;
using _253502LishykK.Domain.Abstractions;
using _253502LishykK.UI.Pages;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;

namespace _253502LishykK.UI.ViewModels
{
    public partial class NominationAddEditPageViewModel : ObservableObject
    {
        private readonly IMediator _mediator;
        private readonly IUnitOfWork _unitOfWork;
        public NominationAddEditPageViewModel(IMediator mediator, IUnitOfWork unitOfWork)
        {
            this._mediator = mediator;
            this._unitOfWork = unitOfWork;
        }
        public string Name { get; set; }
        public int MandatoryProperty { get; set; } // Количество баллов по итогам голосования
        public string AdditionalProperty1 { get; set; }
        public string AdditionalProperty2 { get; set; }
        public ObservableCollection<Nomination> Nominations { get; set; } = new();
        public ObservableCollection<Participant> Participants { get; set; } = new();

        private Nomination _selectedNomination;
        public Nomination SelectedNomination
        {
            get => _selectedNomination;
            set => SetProperty(ref _selectedNomination, value);
        }
        [RelayCommand]
        async Task UpdateGroupList() => await LoadData();
        public IAsyncRelayCommand LoadDataCommand => new AsyncRelayCommand(LoadData);

        public async Task LoadData()
        {
            await LoadNominations();
        }

        public async Task LoadNominations()
        {
            try { 
            var nominations = await _mediator.Send(new GetNominationsRequest());
                Nominations.Clear();
                foreach (var nomination in nominations)
                    Nominations.Add(nomination);
            } catch (Exception ex)
            {
                return;
            }
        }
        private IAsyncRelayCommand _saveCommand;
        public IAsyncRelayCommand SaveCommand => _saveCommand ??= new AsyncRelayCommand(SaveNomination);

        public async Task SaveNomination()
        {
            if (SelectedNomination == null)
            {
                var maxId = Nominations.Max(x => x.Id);
                await _unitOfWork.NominationRepository.AddAsync(new Nomination(Name, ++maxId));
                await _unitOfWork.SaveAllAsync();
                await LoadNominations();
                SelectedNomination = Nominations.First(c => c.Id == maxId);
            }
            else
            {
                SelectedNomination.Name = Name;
                
                await _unitOfWork.NominationRepository.UpdateAsync(SelectedNomination);
                await _unitOfWork.SaveAllAsync();

                //сохраняю выбранный id, т.к. после обновления списка он станет NULL
                var selectedId = SelectedNomination.Id;
                await LoadNominations();
                
                SelectedNomination = Nominations.First(c => c.Id == selectedId);
            }
        }
    }
}
