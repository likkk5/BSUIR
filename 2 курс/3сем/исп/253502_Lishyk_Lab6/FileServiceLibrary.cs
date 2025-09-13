using System;
using System.Collections.Generic;
using System.IO;
using System.Text.Json;

namespace _253502_Lishyk_Lab6
{
    public class FileService<T> : IFileService<T> where T : class
    {
        public IEnumerable<T> ReadFile(string fileName)
        {
            if (File.Exists(fileName))
            {
                string json = File.ReadAllText(fileName);
                return JsonSerializer.Deserialize<IEnumerable<T>>(json);
            }
            return null;
        }

        public void SaveData(IEnumerable<T> data, string fileName)
        {
            string json = JsonSerializer.Serialize(data);
            File.WriteAllText(fileName, json);
        }
    }
}
