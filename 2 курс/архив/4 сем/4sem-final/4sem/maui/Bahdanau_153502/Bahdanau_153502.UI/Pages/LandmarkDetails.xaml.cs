using Bahdanau_153502.UI.ViewModels;

namespace Bahdanau_153502.UI.Pages;

public partial class LandmarkDetails : ContentPage
{
    public LandmarkDetails(LandmarkDetailsViewModel viewModel)
    {
        InitializeComponent();

        BindingContext = viewModel;
    }
}