using _253502LishykK.UI.ViewModels;

namespace _253502LishykK.UI.Pages;


public partial class ParticipantDetailsPage : ContentPage
{
    public ParticipantDetailsPage(ParticipantDetailsViewModel viewModel)
    {
        InitializeComponent();
        BindingContext = viewModel;
    }
}