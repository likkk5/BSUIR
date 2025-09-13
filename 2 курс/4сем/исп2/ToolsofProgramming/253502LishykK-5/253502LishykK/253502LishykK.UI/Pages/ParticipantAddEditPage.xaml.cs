using _253502LishykK.UI.ViewModels;

namespace _253502LishykK.UI.Pages;

public partial class ParticipantAddEditPage : ContentPage
{
	public ParticipantAddEditPage(ParticipantAddEditPageViewModel viewModel)
	{
		InitializeComponent();
        BindingContext = viewModel;
    }
}