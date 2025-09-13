using Newtonsoft.Json;

namespace _253502_Lishyk_Lab8
{
    public class StreamService<T>
    {
        public event EventHandler<ProgressEventArgs> ProgressEvent;
        public async Task WriteToStreamAsync(Stream stream, IEnumerable<T> data, IProgress<string> progress)
        {
            OnProgressEvent(Thread.CurrentThread.ManagedThreadId, "Writing to stream started");
            foreach (var item in data)
            {
                // Simulate slow writing
                await Task.Delay(1000);
                var serializedItem = $"{item.ToString()}\n";
                await stream.WriteAsync(System.Text.Encoding.UTF8.GetBytes(serializedItem), 0, serializedItem.Length);
            }
            OnProgressEvent(Thread.CurrentThread.ManagedThreadId, "Writing to stream completed");
            //    progress.Report("Writing to stream completed");
        }


        public async Task CopyFromStreamAsync(Stream stream, string filename, IProgress<string> progress)
        {
            OnProgressEvent(Thread.CurrentThread.ManagedThreadId, "Copying from stream started");
            using (var fileStream = File.Create(filename))
            {
                await stream.CopyToAsync(fileStream);
            }
            OnProgressEvent(Thread.CurrentThread.ManagedThreadId, "Copying from stream completed");
            progress.Report("Copying from stream completed");
        }

        public async Task<int> GetStatisticsAsync(string fileName, Func<T, bool> filter)
        {
            OnProgressEvent(Thread.CurrentThread.ManagedThreadId, "Getting statistics started");
            int count = 0;
            using (var reader = new StreamReader(fileName))
            {
                while (!reader.EndOfStream)
                {
                    var line = await reader.ReadLineAsync();
                    var item = DeserializeItem(line);
                    if (filter(item))
                    {
                        count++;
                    }
                }
            }
            OnProgressEvent(Thread.CurrentThread.ManagedThreadId, "Getting statistics completed");
            return count;
        }

        //private T DeserializeItem(string line)
        //{
        //    // For simplicity, assuming the serialized item is a string representation of the object
        //    return (T)Convert.ChangeType(line, typeof(T));
        //}
        private T DeserializeItem(string line)
        {
            try
            {
                return JsonConvert.DeserializeObject<T>(line);
            }
            catch (System.Text.Json.JsonException ex)
            {
                // Обработка ошибки десериализации
                Console.WriteLine($"Error deserializing: {ex.Message}");
                return default(T);
            }
        }

        private void OnProgressEvent(int threadId, string message)
        {
            ProgressEvent?.Invoke(this, new ProgressEventArgs { ThreadId = threadId, Message = message });
        }
    }

    public class ProgressEventArgs : EventArgs
    {
        public int ThreadId { get; set; }
        public string Message { get; set; }
    }

}
