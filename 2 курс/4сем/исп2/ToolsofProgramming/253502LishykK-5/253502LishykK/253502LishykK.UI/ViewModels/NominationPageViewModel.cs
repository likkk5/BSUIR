using System.Collections.ObjectModel;
using _253502LishykK.Application.NominationUseCase.Queries;
using _253502LishykK.UI.Pages;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
//баллы участников добавить.

namespace _253502LishykK.UI.ViewModels
{
    public partial class NominationPageViewModel : ObservableObject
    {
        private readonly IMediator _mediator;
        public NominationPageViewModel(IMediator mediator)
        {
            _mediator = mediator;
        }
        public string Name { get; set; }
        public int Id { get; set; }
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
            await LoadParticipants();
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
        private IAsyncRelayCommand _loadParticipantsCommand;
        public IAsyncRelayCommand LoadParticipantsCommand => _loadParticipantsCommand ??= new AsyncRelayCommand(LoadParticipants);

        public async Task LoadParticipants()
        {
            if (SelectedNomination != null)
            {
                var participants = await _mediator.Send(new GetParticipantsByNominationQuery(SelectedNomination.Id.ToString()));
                Participants.Clear();
                foreach (var participant in participants)
                    Participants.Add(participant);
            }
        }

        [RelayCommand]
        async Task ShowParticipantDetails(Participant participant)
        {
            //ChangeFrameBackgroundColor(); // Изменяем цвет фона при нажатии
            await GotoParticipantDetailsPage(participant); // Переходим на страницу с подробностями об участнике
        }

        // Метод для выполнения перехода на страницу ParticipantDetailsPage
        private async Task GotoParticipantDetailsPage(Participant participant)
        {
            IDictionary<string, object> parameters = new Dictionary<string, object>
            {
                { "Participant", participant }
            };
            await Shell.Current.GoToAsync($"{nameof(ParticipantDetailsPage)}", parameters);
        }

        //private Color _frameBackgroundColor;
        //public Color FrameBackgroundColor
        //{
        //    get => _frameBackgroundColor;
        //    set => SetProperty(ref _frameBackgroundColor, value);
        //}

        //private void ChangeFrameBackgroundColor()
        //{
        //    // Измените цвет фона при нажатии на элемент
        //    FrameBackgroundColor = Colors.LightGray;
        //}
    }
}
