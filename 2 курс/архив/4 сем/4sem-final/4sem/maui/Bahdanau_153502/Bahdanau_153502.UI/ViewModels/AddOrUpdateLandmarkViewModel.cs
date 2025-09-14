using Bahdanau_153502.Domain.Entities;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using Microsoft.Maui.Storage;

namespace Bahdanau_153502.UI.ViewModels
{
    [QueryProperty("AddOrUpdate", "Action")]
    [QueryProperty("LandmarkToUpsert", nameof(Landmark))]
    [QueryProperty("Route", nameof(TouristRoute))]
    public partial class AddOrUpdateLandmarkViewModel : ObservableObject
    {
        [ObservableProperty]
        Landmark landmarkToUpsert = new();

        [ObservableProperty]
        TouristRoute route = new();

        [ObservableProperty]
        FileResult image;

        [RelayCommand]
        public async void PickImage()
        {
            var customFileType = new FilePickerFileType(
                new Dictionary<DevicePlatform, IEnumerable<string>>
                {
                    { DevicePlatform.Android, new[] { ".png" } }, 
                    { DevicePlatform.WinUI, new[] { ".png" } }, 
                });

            PickOptions options = new()
            {
                PickerTitle = "Please select a png image",
                FileTypes = customFileType,
            };

            try
            {
                var result = await FilePicker.Default.PickAsync(options);
                if (result != null)
                {
                    if (result.FileName.EndsWith("png", StringComparison.OrdinalIgnoreCase))
                    {
                        Image = result;
                    }
                }
            }
            catch (Exception ex)
            {
                return;
            }

            return;
        }

        public Func<Landmark, Task<Landmark>> AddOrUpdate { get; set; }

        [RelayCommand]
        async void AddOrUpdateLandmark()
        {
            if (
                LandmarkToUpsert.City is null ||
                LandmarkToUpsert.City == string.Empty ||
                LandmarkToUpsert.Description is null ||
                LandmarkToUpsert.Description == string.Empty
                )
            {
                return;
            }

            LandmarkToUpsert.TouristRoute = LandmarkToUpsert.TouristRoute ?? Route;

            await AddOrUpdate(LandmarkToUpsert);

            if (Image != null)
            {
                using var stream = await Image.OpenReadAsync();
                var image = ImageSource.FromStream(() => stream);

                string filename = Path.Combine(Preferences.Default.Get<string>("LocalData", null), $"{LandmarkToUpsert.Id}.png");

                using var fileStream = File.Create(filename);
                stream.Seek(0, SeekOrigin.Begin);
                stream.CopyTo(fileStream);
                stream.Seek(0, SeekOrigin.Begin);
            }
            

            await Shell.Current.GoToAsync("..");
        }
    }
}
