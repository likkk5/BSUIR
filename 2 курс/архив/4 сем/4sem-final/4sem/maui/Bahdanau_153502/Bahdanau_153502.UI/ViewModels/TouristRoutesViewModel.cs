using Bahdanau_153502.Application.Abstractions;
using Bahdanau_153502.Domain.Entities;
using Bahdanau_153502.UI.Pages;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using System.Collections.ObjectModel;

namespace Bahdanau_153502.UI.ViewModels
{
    public partial class TouristRoutesViewModel : ObservableObject
    {
        private readonly ILandmarkService _landmarkService;
        private readonly ITouristRouteService _touristRouteService;
        public TouristRoutesViewModel(ILandmarkService landmarkService, ITouristRouteService touristRouteService)
        {
            _landmarkService = landmarkService;
            _touristRouteService = touristRouteService;
        }

        [ObservableProperty]
        private ObservableCollection<Landmark> _landmarks = new();

        [ObservableProperty]
        private ObservableCollection<TouristRoute> _touristRoutes = new();

        [ObservableProperty]
        TouristRoute selectedTouristRoute;


        [RelayCommand]
        async void ShowDetails(Landmark landmark) => await GotoDetailsPage(landmark);

        private async Task GotoDetailsPage(Landmark landmark)
        {
            IDictionary<string, object> parameters = new Dictionary<string, object>()
            {
                { "Landmark", landmark }
            };

            await Shell.Current.GoToAsync(nameof(LandmarkDetails), parameters);
        }

        [RelayCommand]
        async void AddLandmark()
        {
            if (SelectedTouristRoute is not null)
            {
                await GotoAddOrUpdatePage<AddOrUpdateLandmark, Landmark>(_landmarkService.AddAsync, SelectedTouristRoute);
            }
        }

        [RelayCommand]
        async void AddTouristRoute() => await GotoAddOrUpdatePage<AddOrUpdateTouristRoute, TouristRoute>(_touristRouteService.AddAsync);

        [RelayCommand]
        async void UpdateTouristRoute()
        {
            if (SelectedTouristRoute is not null)
            {
                await GotoAddOrUpdatePage<AddOrUpdateTouristRoute, TouristRoute>(_touristRouteService.UpdateAsync, SelectedTouristRoute);
            }
        }

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

        [RelayCommand]
        async void UpdateTouristRoutes() => await GetTouristRoutes();

        [RelayCommand]
        async void UpdateLandmarks() => await GetLandmarks();

        public async Task GetTouristRoutes()
        {
            IEnumerable<TouristRoute> touristRoutes = await _touristRouteService.GetAllAsync();

            await MainThread.InvokeOnMainThreadAsync(() =>
            {
                TouristRoutes.Clear();
                foreach (TouristRoute touristRoute in touristRoutes)
                    TouristRoutes.Add(touristRoute);
            });
        }

        public async Task GetLandmarks()
        {
            if (SelectedTouristRoute is null)
            {
                return;
            }

            IEnumerable<Landmark> landmarks = await _landmarkService.GetLandmarksByTouristRoute(SelectedTouristRoute);

            await MainThread.InvokeOnMainThreadAsync(() =>
            {
                Landmarks = new();
                foreach (Landmark landmark in landmarks)
                    Landmarks.Add(landmark);
            }); 
        }
    }
}
