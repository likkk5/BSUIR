using System.Diagnostics;


namespace _253502_Lishyk_Lab7
{
    public class IntegralCalculation
    {
        private readonly Semaphore semaphore = new Semaphore(2, 2); //огранич доступа к участку кода, чтобы не более двух потоков могли выполнять интегрирование(нач и макс знач)
        private Function function;

        public delegate double Function(double x);
        public event Action<double>? CompletionPercentEvent;
        public event Action<double>? EndEvent;
        public event Action<long>? ElapsedTimeEvent;

        public double LowerLimit { get; set; }
        public double UpperLimit { get; set; }
        public double Step { get; set; }

        public IntegralCalculation()
        {
            function = Math.Sin;
            LowerLimit = 0;
            UpperLimit = 1;
            Step = 0.00000001;
        }

        public void SetFunction(Function newFunction)
        {
            function = newFunction;
        }

        public void Integrate()
        {
            semaphore.WaitOne();//вызов блокирует поток, если счетчик равен нулю, и уменьшает счетчик на единицу
            double result = 0;
            var stopwatch = Stopwatch.StartNew(); //использ для измерения времени выполнения метода
            double completionPercent = 0;

            for (double i = LowerLimit; i <= UpperLimit; i += Step)
            {
                //На каждом шаге интеграл вычисляется и добавляется к общему результату.
                result += function(i) * Step;

                double newCompletionPercent = (i - LowerLimit) / (UpperLimit - LowerLimit) * 100;
                if (newCompletionPercent > completionPercent + 0.1)
                {
                    completionPercent = newCompletionPercent;
                    CompletionPercentEvent?.Invoke(completionPercent);
                }
            }

            stopwatch.Stop();
            ElapsedTimeEvent?.Invoke(stopwatch.ElapsedMilliseconds);
            EndEvent?.Invoke(result);
            semaphore.Release();//увеличение счетчика Semaphore, разблокировка ожидающего потока.
        }
    }
}

public static class StringExtensions
{
    //Метод расширения для строки, который повторяет строку указанное количество раз.
    //Возвращает новую строку, состоящую из повторений исходной строки.
    public static string Repeat(this string value, int count)
    {
        count = Math.Max(0, count);
        return new string(value[0], count);
    }
}

