﻿using Android.App;
using Android.Content.PM;
using Android.OS;

namespace chessviableutooth
{
    [Activity(Theme = "@style/Maui.SplashTheme", MainLauncher = true, ConfigurationChanges = ConfigChanges.ScreenSize | ConfigChanges.Orientation | ConfigChanges.UiMode | ConfigChanges.ScreenLayout | ConfigChanges.SmallestScreenSize | ConfigChanges.Density)]
    public class MainActivity : MauiAppCompatActivity
    {
        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            if (Android.OS.Build.VERSION.SdkInt >= Android.OS.BuildVersionCodes.S)
            {
                RequestPermissions(new string[]
                {
            Android.Manifest.Permission.BluetoothScan,
            Android.Manifest.Permission.BluetoothConnect
                }, 0);
            }
        }

    }
}
