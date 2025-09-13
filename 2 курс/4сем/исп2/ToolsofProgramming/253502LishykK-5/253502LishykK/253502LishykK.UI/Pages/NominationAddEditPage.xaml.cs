using _253502LishykK.UI.ViewModels;

namespace _253502LishykK.UI.Pages;

public partial class NominationAddEditPage : ContentPage
{
    public NominationAddEditPage(NominationAddEditPageViewModel viewModel)
    {
        InitializeComponent();
        BindingContext = viewModel;
    }
}