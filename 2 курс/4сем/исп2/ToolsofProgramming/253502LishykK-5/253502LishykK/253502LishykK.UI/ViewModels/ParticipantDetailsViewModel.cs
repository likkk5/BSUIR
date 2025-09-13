using System;
using System.Threading.Tasks;
using _253502LishykK.Domain.Entities;
using _253502LishykK.Persistence.Repository;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;

namespace _253502LishykK.UI.ViewModels
{
    [QueryProperty(nameof(Participant), "Participant")]
    public class ParticipantDetailsViewModel : ObservableObject
    {
        private Participant _participant;
        public string Name { get; set; }
        public Participant Participant
        {
            get => _participant;
            set
            {
                SetProperty(ref _participant, value);
                if (File.Exists($"C:/Images/{_participant.Id}.png"))
                    SelectedImageBytes = _participant.Id;
            }
        }

        private string _participantId;

        public string ParticipantId
        {
            set
            {
                if (value != null)
                {
                    _participantId = value;
                    LoadParticipantByIdAsync(_participantId);
                }
            }
        }

        public async Task LoadParticipantByIdAsync(string participantId)
        {
            try
            {
                // Создаем экземпляр репозитория участников
                var participantRepository = new FakeParticipantRepository(); // 

                // Загружаем информацию об участнике по его ID
                Participant = await participantRepository.GetByIdAsync(int.Parse(participantId));
            }
            catch (Exception ex)
            {
                // Обработка ошибок загрузки данных
                Console.WriteLine($"Error loading participant details: {ex.Message}");
            }
        }

        private object _selectedImageBytes;
        public object SelectedImageBytes
        {
            get => _selectedImageBytes;
            set => SetProperty(ref _selectedImageBytes, value);
        }

        private IRelayCommand _selectImageCommand;
        public IRelayCommand SelectImageCommand => _selectImageCommand ??= new RelayCommand(async () => await SelectImage());

        private async Task SelectImage()
        {
            var mediaResult = await MediaPicker.PickPhotoAsync();
            if (mediaResult != null)
            {
                using var stream = await mediaResult.OpenReadAsync();
                using var memoryStream = new MemoryStream();
                await stream.CopyToAsync(memoryStream);
                File.WriteAllBytes($"C:/Images/{Participant.Id}.png", memoryStream.ToArray());
                SelectedImageBytes = Participant.Id;
            }
        }
    }
}
