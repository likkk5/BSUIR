using System.Globalization;

namespace _253502LishykK.UI.ValueConverter
{
    // ValueConverter для преобразования массива байт в изображение
    public class IdToImageSourceConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value == null || !(value is int id))
            {
                return "C:/Images/placeholder.png"; // Изображение-заместитель
            }

            if (File.Exists($"C:/Images/{value}.png"))
            {
                return $"C:/Images/{value}.png";
            }
            else
                return "C:/Images/placeholder.png";
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }

}
