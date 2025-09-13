using _253502_Lishyk_Lab7;

class Program
{
    static void Main()
    {
        IntegralCalculation calc = new IntegralCalculation();
        calc.Step = 0.00000001;


        void PrintProgress(double percent)
        {
            int id = Thread.CurrentThread.ManagedThreadId;
            int progUpperLimitarCells = (int)(percent + 0.01) / 5;
            lock (Console.Out)
            {
                Console.SetCursorPosition(0, id);
                Console.Write($"Stream {id}: [{"=".Repeat(progUpperLimitarCells)}{">".Repeat((progUpperLimitarCells < 20) ? 1 : 0)}{" ".Repeat(19 - progUpperLimitarCells)}]{percent:F1}%");
                //метод расширения Repeat из класса StringExtensions
            }
        }

        void PrintResult(double result)
        {
            int id = Thread.CurrentThread.ManagedThreadId;
            lock (Console.Out)
            {
                Console.SetCursorPosition(0, id);
                Console.Write($"Stream {id}: Ended with result: {result}");
            }
        }

        void PrintElapsedTime(long time, ThreadPriority priority)
        {
            int id = Thread.CurrentThread.ManagedThreadId;
            lock (Console.Out)
            {
                Console.SetCursorPosition(60, id);
                Console.Write($"Consumed time: {time}ms");

                if (priority == ThreadPriority.Lowest)
                {
                    Console.Write(" Low priority");
                }
                else if (priority == ThreadPriority.Highest)
                {
                    Console.Write(" High priority");
                }
            }
        }

        calc.CompletionPercentEvent += PrintProgress;
        calc.EndEvent += PrintResult;
        calc.ElapsedTimeEvent += time => PrintElapsedTime(time, Thread.CurrentThread.Priority);

        Thread thread1 = new Thread(calc.Integrate);
        //thread1.ManagedThreadId = 1;
        thread1.Priority = ThreadPriority.Highest;
        thread1.Start();

        Thread thread2 = new Thread(calc.Integrate);
        thread2.Priority = ThreadPriority.Lowest;
        thread2.Start();

        Thread thread3 = new Thread(calc.Integrate);
        thread3.Start();

        Thread thread4 = new Thread(calc.Integrate);
        thread4.Start();

        Thread thread5 = new Thread(calc.Integrate);
        thread5.Start();

        // Waiting for all threads to finish
        thread1.Join();
        thread2.Join();
        thread3.Join();
        thread4.Join();
        thread5.Join();
    }
}