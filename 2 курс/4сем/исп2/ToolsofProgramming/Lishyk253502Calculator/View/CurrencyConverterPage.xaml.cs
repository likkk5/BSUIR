using Lishyk253502Calculator.Services;
using Lishyk253502Calculator.Entities;
using Microsoft.Maui.Controls;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace Lishyk253502Calculator.View
{
    public partial class CurrencyConverterPage : ContentPage
    {
        private readonly IRateService _rateService;

        public CurrencyConverterPage(IRateService rateService)
        {
            _rateService = rateService;
            InitializeComponent();
            InitializeCurrencyPicker();
        }

        protected override void OnAppearing()
        {
            base.OnAppearing();
            CheckInternetAndLoadData(); // Проверяем подключение к интернету и загружаем данные
        }

        private async void CheckInternetAndLoadData()
        {
            if (Connectivity.NetworkAccess != NetworkAccess.Internet)
            {
                await DisplayAlert("No Internet", "Please check your internet connection", "OK");
            }
            else
            {
                await UpdateCurrencyPickerAsync(); // Асинхронно обновляем список валют
            }
        }

        private async void OnDateSelected(object sender, DateChangedEventArgs e)
        {
            await UpdateCurrencyPickerAsync(); // Асинхронно обновляем список валют
        }

        private async void OnCurrencySelectedIndexChanged(object sender, EventArgs e)
        {
            await ConvertCurrencyAsync(); // Асинхронно конвертируем валюту
        }

        private async void OnAmountEntryCompleted(object sender, EventArgs e)
        {
            await ConvertCurrencyAsync(); // Асинхронно конвертируем валюту
        }

        private async Task UpdateCurrencyPickerAsync()
        {
            if (Connectivity.NetworkAccess != NetworkAccess.Internet)
            {
                await DisplayAlert("No Internet", "Please check your internet connection", "OK");
                return;
            }

            DateTime selectedDate = DatePicker.Date;
            IEnumerable<Rate> rates = await _rateService.GetRates(selectedDate);

            CurrencyPicker.ItemsSource = rates.ToList();
            CurrencyPicker.SelectedIndex = 0;
        }

        private async Task ConvertCurrencyAsync()
        {
            if (Connectivity.NetworkAccess != NetworkAccess.Internet)
            {
                await DisplayAlert("No Internet", "Please check your internet connection", "OK");
                return;
            }

            if (CurrencyPicker.SelectedItem is Rate selectedRate && double.TryParse(AmountEntry.Text, out double amount))
            {
                double result = isReverseConversion ? amount / selectedRate.Cur_OfficialRate : amount * selectedRate.Cur_OfficialRate;

                ResultLabel.Text = isReverseConversion ?
                    $"{amount} {selectedRate.Cur_Abbreviation} is approximately {result:F2} BYN" :
                    $"{amount} BYN is approximately {result:F2} {selectedRate.Cur_Abbreviation}";
            }
        }

        private bool isReverseConversion = false;

        private void OnReverseSwitchToggled(object sender, ToggledEventArgs e)
        {
            isReverseConversion = e.Value;
            UpdateConversionDirectionLabel();
        }

        private void UpdateConversionDirectionLabel()
        {
            ConversionDirectionLabel.Text = isReverseConversion ?
                "Converting from Foreign Currency to BYN" :
                "Converting from BYN to Foreign Currency";
        }

        private void InitializeCurrencyPicker()
        {
            // Default to today's date
            DatePicker.Date = DateTime.Today;
            CheckInternetAndLoadData(); // Проверяем подключение к интернету и загружаем данные
        }
    }
}
