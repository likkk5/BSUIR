using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _253502LishykK.UI.ValueConverter
{
    // ValueConverter для преобразования массива байт в изображение
    public class ByteArrayToImageSourceConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value == null || !(value is byte[] imageBytes))
            {
                return "C:/Images/placeholder.png"; // Изображение-заместитель
            }

            // Создание временного файла для сохранения изображения
            var tempFilePath = Path.Combine(Path.GetTempPath(), $"{Guid.NewGuid()}.png");
            File.WriteAllBytes(tempFilePath, imageBytes);

            // Возвращение пути к временному файлу
            return tempFilePath;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }

}
