using Bahdanau_153502.UI.ViewModels;

namespace Bahdanau_153502.UI.Pages;

public partial class AddOrUpdateLandmark : ContentPage
{
    public AddOrUpdateLandmark(AddOrUpdateLandmarkViewModel viewModel)
    {
        InitializeComponent();

        BindingContext = viewModel;
    }
}