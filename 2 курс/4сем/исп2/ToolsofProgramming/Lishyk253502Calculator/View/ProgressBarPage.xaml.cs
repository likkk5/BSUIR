using System;
using System.Diagnostics;
using System.Threading;
using static System.Net.Mime.MediaTypeNames;

namespace Lishyk253502Calculator.View;

public partial class ProgressBarPage : ContentPage
{
    double Answer = 0;

    private CancellationTokenSource cancellationTokenSource;

    public ProgressBarPage()
    {
        InitializeComponent();
    }

    private async void OnStart(object sender, EventArgs e) //��������� ����������� �������� ��������������
    {
        label.Text = "�alculation";
        startButton.IsEnabled = false;
        //startButton.BackgroundColor = Color.FromRgba(0, 0, 0, 0);
        startButton.BackgroundColor = Colors.Transparent;
        try
        {
            var progress = new Progress<int>(value =>
            {
                progressBar.Progress = ((double)value / 100);
                label_progress.Text = $"{value}%";
            });
            cancellationTokenSource = new CancellationTokenSource();
            Answer = await Task.Run(() => Calculate(cancellationTokenSource.Token, progress)); //��������� ����������� ������ � ������� ������, ����� ������� ����������
            //��������� ������� ���������� ����������� ������ � ������� await

            label.Text = $"Integrate[Sin(x),{{x,0,1}}] = {Answer:f10}";
            label_progress.Text = $"100%";
            progressBar.Progress = 1;
            startButton.IsEnabled = true;
            startButton.TextColor = Colors.White;
        }
        catch (OperationCanceledException)
        {
            label.Text = "The task has been canceled";
        }
        finally
        {
            // �������������� ������ � ����� ������ (���� ��� ������ ��� ������)
            startButton.IsEnabled = true;
            startButton.TextColor = Colors.White;
        }
    }
    private double Calculate(CancellationToken cancellationToken, IProgress<int> progress)//�����, ����������� ��������� �������������� � ������� ���������
    {
        double Step = 0.000001;
        double result = 0;
        double delay = 2;

        for (double x = 0; x < 1; x += Step)
        {
            cancellationToken.ThrowIfCancellationRequested();

            result += Math.Sin(x) * Step;

            int percentComplete = (int)(x * 100);
            progress.Report(percentComplete);

            int counter = 1000;
            while (counter != 0)
            {
                delay *= counter;
                counter--;
            }
        }

        return result;
    }

    private void OnCancel(object sender, EventArgs e)
    {
        cancellationTokenSource?.Cancel(); //������������ ��� ������������ � �������� ���������� ����������� �������� ��������������
        startButton.IsEnabled = true;
        startButton.TextColor = Colors.White;
    }
    //async await ���������� �� ���������� ������
}