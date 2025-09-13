using System.Windows.Input;
using _253502LishykK.UI.Pages;

namespace _253502LishykK.UI
{
    public partial class AppShell : Shell
    {
        public AppShell()
        {
            InitializeComponent();
            BindingContext = this;
            Routing.RegisterRoute(nameof(ParticipantDetailsPage), typeof(ParticipantDetailsPage)); //регистрации маршрута для навигации по стеку
        }
        //public ICommand TapCommand => new Command<string>((url) => DisplayAlert("Уведомление", "Наименование категории успешно изменено!", "ОK"));

        private void OnAddButtonClicked(object sender, EventArgs e)
        {
            GoToAsync("//nominationadd");
        }
        private void OnEditButtonClicked(object sender, EventArgs e)
        {
            GoToAsync("//participantnadd");

        }
        
        protected override void OnNavigated(ShellNavigatedEventArgs args)
        {
            base.OnNavigated(args);
            mylabel.Text = Shell.Current?.CurrentItem?.Title;
        }
    }
}
