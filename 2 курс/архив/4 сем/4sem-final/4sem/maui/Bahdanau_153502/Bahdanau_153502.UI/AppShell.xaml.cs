using Bahdanau_153502.UI.Pages;

namespace Bahdanau_153502.UI;

public partial class AppShell : Shell
{
    public AppShell()
    {
        InitializeComponent();

        Routing.RegisterRoute(nameof(LandmarkDetails), typeof(LandmarkDetails));
        Routing.RegisterRoute(nameof(AddOrUpdateTouristRoute), typeof(AddOrUpdateTouristRoute));
        Routing.RegisterRoute(nameof(AddOrUpdateLandmark), typeof(AddOrUpdateLandmark));
    }
}
