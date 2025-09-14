using Bahdanau_153502.Application.Abstractions;
using Bahdanau_153502.Domain.Entities;
using Bahdanau_153502.UI.Pages;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;

namespace Bahdanau_153502.UI.ViewModels
{
    [QueryProperty("Landmark", "Landmark")]
    public partial class LandmarkDetailsViewModel : ObservableObject
    {
        ILandmarkService _landmarkService;
        public LandmarkDetailsViewModel(ILandmarkService landmarkService)
        {
            _landmarkService = landmarkService;
        }

        [ObservableProperty]
        Landmark landmark;

        [RelayCommand]
        async void UpdateLandmark() => await GotoAddOrUpdatePage<AddOrUpdateLandmark, Landmark>(_landmarkService.UpdateAsync, Landmark);

        private async Task GotoAddOrUpdatePage<Page, Entity>(Func<Entity, Task<Entity>> method, params object[] entities)
            where Entity : class
            where Page : ContentPage
        {
            IDictionary<string, object> parameters = new Dictionary<string, object>()
            {
                { "Action", method }
            };

            foreach (object entity in entities)
            {
                string name = entity.GetType().Name;
                parameters.Add(name, entity);
            }

            await Shell.Current.GoToAsync(typeof(Page).Name, parameters);
        }
    }
}
