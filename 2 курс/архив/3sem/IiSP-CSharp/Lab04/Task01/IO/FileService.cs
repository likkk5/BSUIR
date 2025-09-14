using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Task01.Interfaces;
using Task01.Entities;

namespace Task01.IO
{
    public class FileService : IFileService<Car>
    {
        public IEnumerable<Car> ReadFile(string fileName)
        {
            if (!File.Exists(fileName))
            {
                throw new FileNotFoundException("File does not exists");
            }
            using (var stream = File.OpenRead(fileName))
            {
                using (BinaryReader reader = new BinaryReader(stream))
                {
                    while (stream.Position < stream.Length)
                    {
                        int price;
                        bool sold;
                        string name;
                        try
                        {
                            price = reader.ReadInt32();
                            sold = reader.ReadBoolean();
                            name = reader.ReadString();
                        }
                        catch (Exception ex)
                        {
                            Console.WriteLine(ex.Message);
                            yield break;
                        }
                        yield return new Car(price, sold, name);
                    }
                }
            }
        }

        public void SaveData(IEnumerable<Car> data, string fileName)
        {
            using (var stream = File.Open(fileName, FileMode.OpenOrCreate))
            {
                using (BinaryWriter writer = new BinaryWriter(stream))
                {
                    foreach (Car car in data)
                    {
                        (int price, bool sold, string name) = car;
                        try
                        {
                            writer.Write(price);
                            writer.Write(sold);
                            writer.Write(name);
                        }
                        catch (Exception ex)
                        {
                            Console.WriteLine(ex.Message);
                            break;
                        }
                    }
                }
            }
        }
    }
}
