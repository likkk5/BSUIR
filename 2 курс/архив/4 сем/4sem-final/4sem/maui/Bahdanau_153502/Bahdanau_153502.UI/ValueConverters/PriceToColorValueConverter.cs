using System.Globalization;

namespace Bahdanau_153502.UI.ValueConverters
{
    internal class TickerPriceToColorValueConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            const decimal TICKET_MAX_PRICE = 150;

            if ((decimal)value < TICKET_MAX_PRICE)
            {
                return Colors.LightPink;
            }

            return Colors.WhiteSmoke;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
