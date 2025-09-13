using _253502LishykK.UI.ViewModels;

namespace _253502LishykK.UI.Pages;

public partial class NominationPage : ContentPage
{
	public NominationPage(IMediator mediator)
	{
		InitializeComponent();
        BindingContext = new NominationPageViewModel(mediator);
    }
}