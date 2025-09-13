using Microsoft.Maui.Controls;
using System;
using System.Collections.ObjectModel;
using Lishyk253502Calculator.Entities;
using Lishyk253502Calculator.Services;
namespace Lishyk253502Calculator.View;

public partial class SQLiteDemoPage : ContentPage
{
    private readonly IDbService _dbService;
    private ObservableCollection<string> _sushiSets;

    public SQLiteDemoPage(IDbService dbService)
    {
        _dbService = dbService;
        InitializeComponent();
    }

    protected override void OnAppearing()
    {
        base.OnAppearing();

        if (_sushiSets == null)
        {
            LoadSushiSets();
        }
        //LoadSushiSets();
    }

    private void LoadSushiSets()
    {
        var sushiSets = _dbService.GetAllSushiSets();

        // Преобразовать список объектов в список имен
        var sushiSetNames = sushiSets.Select(sushiSet => sushiSet.Name).ToList();

        if (_sushiSets == null)
        {
            _sushiSets = new ObservableCollection<string>(sushiSetNames);
            SushiSetPicker.ItemsSource = _sushiSets;
        }
        else
        {
            // Очистите коллекцию и добавьте новые данные
            _sushiSets.Clear();
            foreach (var name in sushiSetNames)
            {
                _sushiSets.Add(name);
            }
        }
    }

    private void OnSushiSetSelectedIndexChanged(object sender, EventArgs e)
    {
        if (_sushiSets != null && SushiSetPicker.SelectedItem is string selectedSushiSetName)
        {
            // Получите объект SushiSetEntity по имени из базы данных
            var selectedSushiSet = _dbService.GetAllSushiSets().FirstOrDefault(sushiSet => sushiSet.Name == selectedSushiSetName);

            if (selectedSushiSet != null)
            {
                var sushisInSet = _dbService.GetSushisInSet(selectedSushiSet.Id);
                SushisCollectionView.ItemsSource = sushisInSet;
            }
        }
    }

    //Вызовите этот метод при необходимости очистки базы данных
    //private void OnClearDatabaseButtonClicked(object sender, EventArgs e)
    //{
    //    _dbService.ClearDatabase();
    //    LoadSushiSets();
    //}

}