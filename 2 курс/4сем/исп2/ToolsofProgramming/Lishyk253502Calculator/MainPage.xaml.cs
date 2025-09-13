namespace Lishyk253502Calculator
{
    public partial class MainPage : ContentPage
    {
        public MainPage()
        {
            InitializeComponent();
        }
        private void OnGoToSQLiteDemoPageClicked(object sender, EventArgs e)
        {
            Shell.Current.GoToAsync("//sqlitedemo");
        }

    }

}
