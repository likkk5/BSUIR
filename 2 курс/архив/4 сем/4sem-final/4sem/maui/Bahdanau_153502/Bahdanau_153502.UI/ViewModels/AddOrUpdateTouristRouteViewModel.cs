using Bahdanau_153502.Domain.Entities;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;

namespace Bahdanau_153502.UI.ViewModels
{
    [QueryProperty("AddOrUpdate", "Action")]
    [QueryProperty("RouteToCreate", nameof(TouristRoute))]
    public partial class AddOrUpdateTouristRouteViewModel : ObservableObject
    {
        [ObservableProperty]
        TouristRoute routeToUpsert = new();

        public Func<TouristRoute, Task<TouristRoute>> AddOrUpdate { get; set; }

        [RelayCommand]
        async void AddOrUpdateTouristRoute()
        {
            if (RouteToUpsert.Title is null || RouteToUpsert.Title == string.Empty)
            {
                return;
            }

            await AddOrUpdate(RouteToUpsert);

            await Shell.Current.GoToAsync("..");
        }
    }
}
