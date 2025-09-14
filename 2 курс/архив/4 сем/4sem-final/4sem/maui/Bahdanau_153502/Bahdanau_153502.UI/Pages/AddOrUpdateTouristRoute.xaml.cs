using Bahdanau_153502.UI.ViewModels;

namespace Bahdanau_153502.UI.Pages;

public partial class AddOrUpdateTouristRoute : ContentPage
{
    public AddOrUpdateTouristRoute(AddOrUpdateTouristRouteViewModel viewModel)
    {
        InitializeComponent();

        BindingContext = viewModel;
    }
}