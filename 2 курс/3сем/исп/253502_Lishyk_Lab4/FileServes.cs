using _253502_Lishyk_Lab4;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Collections.Generic;
using System.IO;

namespace _253502_Lishyk_Lab4
{
    public class FileService<T> : IFileService<T> where T : Mammal //наследование от интерфейса где уже задан тип
    {
        public IEnumerable<T> ReadFile(string fileName)
        {
            using (BinaryReader reader = new BinaryReader(File.Open(fileName, FileMode.Open)))
            {
                while (reader.BaseStream.Position < reader.BaseStream.Length)
                {
                    string name = reader.ReadString();
                    int age = reader.ReadInt32();
                    bool hasTail = reader.ReadBoolean();

                    Mammal mammal = new Mammal { Name = name, Age = age, HasTail = hasTail };
                    yield return (T)(object)mammal;
                }
            }
        }

        public void SaveData(string fileName, IEnumerable<T> data)
        {
            using (BinaryWriter writer = new BinaryWriter(File.Open(fileName, FileMode.Create)))
            {
                foreach (var item in data)
                {
                    writer.Write(item.Name);
                    writer.Write(item.Age);
                    writer.Write(item.HasTail);
                }
            }
        }
    }
}