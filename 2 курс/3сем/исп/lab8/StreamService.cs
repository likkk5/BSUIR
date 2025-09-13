using System.IO;
using System.Text.Json;
using System.Threading.Tasks; //масштабируемый параллельный код без необходимости работать непосредственно с потоками или пулом потоков


namespace _253502_Lishyk_Lab8
{
    public class StreamService<T> where T : class
    {
        public readonly Semaphore semaphore = new Semaphore(1, 1);
        public async Task WriteToStreamAsync(Stream stream, IEnumerable<T> data, IProgress<string> progress)
        //записывает коллекцию data в поток stream
        {
            Console.WriteLine($"Starting write to stream {Thread.CurrentThread.ManagedThreadId}");
            await Task.Delay(3000); //приводит к блокированию до тех пор, пока она не будет завершена, и эквивалентен вызову метода Join(группирует без явного преобразования) на объекте потока
            semaphore.WaitOne(); 
            await JsonSerializer.SerializeAsync(stream, data);

            Console.WriteLine($"Ending write to stream {Thread.CurrentThread.ManagedThreadId}");
            progress.Report("Write to stream completed");
            semaphore.Release();
        }

        public async Task CopyFromStreamAsync(Stream stream, string fileName, IProgress<string> progress)
        {
            Console.WriteLine($"Starting copy from stream to file {Thread.CurrentThread.ManagedThreadId}");
            await Task.Delay(3000);

            semaphore.WaitOne();

            try
            {
                using (var file = File.Open(fileName, FileMode.Create, FileAccess.ReadWrite))
                {
                    stream.Seek(0, SeekOrigin.Begin);
                    await stream.CopyToAsync(file);
                }

                Console.WriteLine($"Ending copy from stream to file {Thread.CurrentThread.ManagedThreadId}");
                progress.Report("Copy from stream to file completed");
            }
            finally
            {
                semaphore.Release();
            }
        }

        public async Task<int> GetStatisticsAsync(string fileName, Func<T, bool> filter)
        //считывает объекты типа Т из файла с именем filename и возвращает количество объектов, удовлетворяющих условию filter
        {
            List<T> list;
            using (var fileStream = File.OpenRead(fileName))
            {
                list = await JsonSerializer.DeserializeAsync<List<T>>(fileStream);
            }

            return list.Count(filter);
        }
    }
}