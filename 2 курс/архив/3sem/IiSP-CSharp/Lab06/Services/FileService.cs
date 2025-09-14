using System.Text.Json;

namespace Services
{
    public class FileService<T> : IFileService<T> where T : class
    {
        public IEnumerable<T> ReadFile(string fileName)
        {
            string jsonString = File.ReadAllText(fileName);
            var list = JsonSerializer.Deserialize<List<T>>(jsonString);
            foreach (var item in list)
            {
                yield return item;
            }
        }

        public void SaveData(IEnumerable<T> data, string fileName)
        {
            string jsonString = JsonSerializer.Serialize(data);
            File.WriteAllText(fileName, jsonString);
        }
    }
}