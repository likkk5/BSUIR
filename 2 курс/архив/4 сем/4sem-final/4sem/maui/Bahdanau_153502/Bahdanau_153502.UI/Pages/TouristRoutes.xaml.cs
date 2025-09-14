using Bahdanau_153502.UI.ViewModels;

namespace Bahdanau_153502.UI.Pages;

public partial class TouristRoutes : ContentPage
{
    public TouristRoutes(TouristRoutesViewModel viewModel)
    {
        InitializeComponent();

        BindingContext = viewModel;
    }
}