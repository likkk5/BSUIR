using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml.Navigation;

// The User Control item template is documented at https://go.microsoft.com/fwlink/?LinkId=234236

namespace SDKTemplate
{
    public sealed partial class ChessBoard : UserControl
    {
        public EventHandler SendEvent;
        private string[] _pos = new string[] { "A", "B", "C", "D", "E", "F", "G", "H" };
        public ChessBoard()
        {
            this.InitializeComponent();
        }

        private string prefix = "W";
        private bool isYourStep = true;

        public void InitBoard(bool isWhite = true)
        {
            isYourStep = isWhite;
            prefix = isWhite ? "W" : "B";

            foreach (Button btn in gBoard.Children.OfType<Button>())
            {
                int row = Grid.GetRow(btn);
                int column = Grid.GetColumn(btn);
                btn.Tag = isWhite
                    ? $"{_pos[column]}{8 - row}"
                    : $"{_pos[7 - column]}{row + 1}";
            }

            if (!isWhite)
            {
                SwapContentForRows(0, 7);
                SwapContentForRows(1, 6);

                var whiteQueen = gBoard.Children.OfType<Button>().First(b => Grid.GetRow(b) == 0 && Grid.GetColumn(b) == 3);
                var whiteKing = gBoard.Children.OfType<Button>().First(b => Grid.GetRow(b) == 0 && Grid.GetColumn(b) == 4);

                SwapButtonContent(whiteQueen, whiteKing);

                var blackQueen = gBoard.Children.OfType<Button>().First(b => Grid.GetRow(b) == 7 && Grid.GetColumn(b) == 3);
                var blackKing = gBoard.Children.OfType<Button>().First(b => Grid.GetRow(b) == 7 && Grid.GetColumn(b) == 4);

                SwapButtonContent(blackQueen, blackKing);
            }
        }
        
        private void SwapContentForRows(int sourceRow, int targetRow)
        {
            foreach (Button btnFrom in gBoard.Children.OfType<Button>().Where(b => Grid.GetRow(b) == sourceRow))
            {
                int column = Grid.GetColumn(btnFrom);
                Button btnTo = gBoard.Children
                    .OfType<Button>()
                    .FirstOrDefault(b => Grid.GetRow(b) == targetRow && Grid.GetColumn(b) == column);

                if (btnTo != null)
                {
                    SwapButtonContent(btnFrom, btnTo);
                }
            }
        }

        private void SwapButtonContent(Button btnFrom, Button btnTo)
        {
            if (btnFrom.Content is Image fromImage && btnTo.Content is Image toImage)
            {
                var tempSource = toImage.Source;
                var tempTag = toImage.Tag;

                toImage.Source = fromImage.Source;
                toImage.Tag = fromImage.Tag;

                fromImage.Source = tempSource;
                fromImage.Tag = tempTag;
            }
        }

        public void UpdateBoard(string board)
        {
            //Exemple: W:Pawn:H2:H4
            var split = board.Split(':');
            isYourStep = split[0] != prefix;

            var btnFrom = gBoard.Children.OfType<Button>().FirstOrDefault(b => (string)b.Tag == split[2]);
            var btnTo = gBoard.Children.OfType<Button>().FirstOrDefault(b => (string)b.Tag == split[3]);

            ((Image)btnTo.Content).Source = ((Image)btnFrom.Content).Source;
            ((Image)btnTo.Content).Tag = ((Image)btnFrom.Content).Tag;
            ((Image)btnFrom.Content).Source = null;
        }


        private Button SelectedButton;
        //private void Button_Click(object sender, RoutedEventArgs e)
        //{
        //    var btn = sender as Button;
        //    if (SelectedButton != null)
        //    {
        //        if (SelectedButton == btn)
        //        {
        //            SelectedButton.BorderBrush = SelectedButton.Background;
        //            SelectedButton = null;
        //        }
        //        else
        //        {
        //            var msg = $"{prefix}:{((Image)SelectedButton.Content).Tag}:{SelectedButton.Tag}:{btn.Tag}";

        //            SelectedButton.BorderBrush = SelectedButton.Background;
        //            ((Image)btn.Content).Source = ((Image)SelectedButton.Content).Source;
        //            ((Image)btn.Content).Tag = ((Image)SelectedButton.Content).Tag;
        //            ((Image)SelectedButton.Content).Source = null;
        //            SelectedButton = null;

        //            SendEvent?.Invoke(msg, EventArgs.Empty);
        //        }
        //    }
        //    else
        //    {
        //        SelectedButton = sender as Button;
        //        SelectedButton.BorderBrush = new SolidColorBrush(Windows.UI.Colors.Black);
        //    }
        //}

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var btn = sender as Button;
            if (!isYourStep)
            {
                ContentDialog dlg = new ContentDialog
                {
                    Title = "Не ваш ход",
                    Content = "Сейчас ход противника.",
                    CloseButtonText = "OK"
                };
                _ = dlg.ShowAsync();
                return;
            }
            if (SelectedButton != null)
            {
                if (SelectedButton == btn)
                {
                    SelectedButton.BorderBrush = SelectedButton.Background;
                    SelectedButton = null;
                }
                else
                {
                    var fromRow = Grid.GetRow(SelectedButton);
                    var fromCol = Grid.GetColumn(SelectedButton);
                    var toRow = Grid.GetRow(btn);
                    var toCol = Grid.GetColumn(btn);

                    var pieceImage = SelectedButton.Content as Image;
                    if (pieceImage == null)
                        return;

                    string pieceType = pieceImage.Tag?.ToString();
                    if (IsValidMove(pieceType, fromRow, fromCol, toRow, toCol))
                    {
                        var msg = $"{prefix}:{pieceType}:{SelectedButton.Tag}:{btn.Tag}";

                        ((Image)btn.Content).Source = ((Image)SelectedButton.Content).Source;
                        ((Image)btn.Content).Tag = ((Image)SelectedButton.Content).Tag;
                        ((Image)SelectedButton.Content).Source = null;
                        SelectedButton.BorderBrush = SelectedButton.Background;
                        SelectedButton = null;

                        SendEvent?.Invoke(msg, EventArgs.Empty);
                        isYourStep = false;

                        CheckForCheck();

                        CheckForCheckmate();
                    }
                    else
                    {
                        // недопустимый ход
                        SelectedButton.BorderBrush = SelectedButton.Background;
                        SelectedButton = null;
                        ContentDialog dlg = new ContentDialog
                        {
                            Title = "Неверный ход",
                            Content = "Эта фигура не может сделать такой ход.",
                            CloseButtonText = "OK"
                        };
                        _ = dlg.ShowAsync();
                    }
                }
            }
            else
            {
                var pieceImage = btn.Content as Image;
                if (pieceImage?.Source is BitmapImage bitmapImage)
                {
                    var uri = bitmapImage.UriSource.ToString();
                    bool isWhite = uri.Contains("w.png");

                    if ((isWhite && prefix == "W") || (!isWhite && prefix == "B"))
                    {
                        SelectedButton = btn;
                        SelectedButton.BorderBrush = new SolidColorBrush(Windows.UI.Colors.Black);
                    }
                    else
                    {
                        ContentDialog dlg = new ContentDialog
                        {
                            Title = "Не ваша фигура",
                            Content = "Вы не можете ходить фигурой противника.",
                            CloseButtonText = "OK"
                        };
                        _ = dlg.ShowAsync();
                    }
                }
            }

        }


        private void Button_PointerExited(object sender, PointerRoutedEventArgs e)
        {
            var btn = sender as Button;
            if (btn != SelectedButton)
                btn.BorderBrush = btn.Background;
        }

        private void Button_PointerEntered(object sender, PointerRoutedEventArgs e)
        {
            ((Button)sender).BorderBrush = new SolidColorBrush(Windows.UI.Colors.Black);
        }
        private bool IsValidMove(string pieceType, int fromRow, int fromCol, int toRow, int toCol)
        {
            int rowDiff = toRow - fromRow;
            int colDiff = toCol - fromCol;

            var toButton = GetButtonAt(toRow, toCol);
            var toImage = toButton.Content as Image;

            // Нельзя бить свою фигуру
            if (toImage != null && toImage.Tag != null && IsSameColor(prefix, toImage.Tag.ToString()))
                return false;

            switch (pieceType)
            {
                case "Pawn":
                    // Прямой ход вперёд
                    if (colDiff == 0)
                    {
                        if (rowDiff == -1 && IsEmpty(toRow, toCol))
                            return true;
                        if (rowDiff == -2 && fromRow == 6 && IsEmpty(toRow, toCol) && IsEmpty(fromRow - 1, fromCol))
                            return true;
                    }
                    // Атака по диагонали
                    else if (Math.Abs(colDiff) == 1 && rowDiff == -1)
                    {
                        return toImage != null && toImage.Tag != null && !IsSameColor(prefix, toImage.Tag.ToString());
                    }
                    return false;

                case "Rook":
                    return (fromRow == toRow || fromCol == toCol) && IsPathClear(fromRow, fromCol, toRow, toCol);

                case "Knight":
                    return (Math.Abs(rowDiff) == 2 && Math.Abs(colDiff) == 1) ||
                           (Math.Abs(rowDiff) == 1 && Math.Abs(colDiff) == 2);

                case "Bishop":
                    return Math.Abs(rowDiff) == Math.Abs(colDiff) && IsPathClear(fromRow, fromCol, toRow, toCol);

                case "Queen":
                    return ((fromRow == toRow || fromCol == toCol) ||
                            (Math.Abs(rowDiff) == Math.Abs(colDiff))) &&
                           IsPathClear(fromRow, fromCol, toRow, toCol);

                case "King":
                    return Math.Abs(rowDiff) <= 1 && Math.Abs(colDiff) <= 1;

                default:
                    return false;
            }
        }
        private bool IsSameColor(string currentPrefix, string tag)
        {
            return tag.StartsWith(currentPrefix);
        }

        private bool IsEmpty(int row, int col)
        {
            var btn = GetButtonAt(row, col);
            var image = btn.Content as Image;
            return image?.Source == null;
        }

        private Button GetButtonAt(int row, int col)
        {
            return gBoard.Children
                .OfType<Button>()
                .FirstOrDefault(b => Grid.GetRow(b) == row && Grid.GetColumn(b) == col);
        }

        private bool IsPathClear(int fromRow, int fromCol, int toRow, int toCol)
        {
            int rowStep = Math.Sign(toRow - fromRow);
            int colStep = Math.Sign(toCol - fromCol);

            int currentRow = fromRow + rowStep;
            int currentCol = fromCol + colStep;

            while (currentRow != toRow || currentCol != toCol)
            {
                if (!IsEmpty(currentRow, currentCol))
                    return false;

                currentRow += rowStep;
                currentCol += colStep;
            }
            return true;
        }
        private Button FindKing(string color)
        {
            string kingTag = color + ":King";

            return gBoard.Children
                .OfType<Button>()
                .FirstOrDefault(b =>
                {
                    var img = b.Content as Image;
                    return img?.Tag != null && img.Tag.ToString() == kingTag;
                });
        }

        private bool IsKingInCheck(string color)
        {
            // Найдем позицию короля
            var kingPosition = FindKing(color);
            if (kingPosition == null) return false;

            int kingRow = Grid.GetRow(kingPosition);
            int kingCol = Grid.GetColumn(kingPosition);

            // Проверяем все фигуры противника
            foreach (var btn in gBoard.Children.OfType<Button>())
            {
                var pieceImage = btn.Content as Image;
                if (pieceImage == null || !IsSameColor(color == "W" ? "B" : "W", pieceImage.Tag?.ToString()))
                    continue;

                int pieceRow = Grid.GetRow(btn);
                int pieceCol = Grid.GetColumn(btn);
                string pieceType = pieceImage.Tag?.ToString().Split(':')[1];

                // Если фигура противника может атаковать короля
                if (IsValidMove(pieceType, pieceRow, pieceCol, kingRow, kingCol))
                {
                    return true;
                }
            }

            return false;
        }
        private void CheckForCheck()
        {
            if (IsKingInCheck(prefix))
            {
                ContentDialog dlg = new ContentDialog
                {
                    Title = "Шах!",
                    Content = $"{(prefix == "W" ? "Белые" : "Чёрные")} находятся в шахе!",
                    CloseButtonText = "OK"
                };
                _ = dlg.ShowAsync();
            }
        }
        private bool IsKingInCheckAfterMove(int fromRow, int fromCol, int toRow, int toCol, string color)
        {
            var kingButton = FindKing(color);
            if (kingButton == null) return false;

            int kingRow = Grid.GetRow(kingButton);
            int kingCol = Grid.GetColumn(kingButton);

            // Временно перемещаем короля
            var kingImage = (Image)kingButton.Content;
            string kingTag = kingImage.Tag.ToString();
            kingButton.Content = null;
            Button targetButton = GetButtonAt(toRow, toCol);
            targetButton.Content = kingImage;

            // Проверяем, находится ли король в шахе после перемещения
            bool isInCheck = IsKingInCheck(color);

            // Возвращаем короля на место
            targetButton.Content = null;
            kingButton.Content = kingImage;

            return isInCheck;
        }

        private bool IsCheckmate(string color)
        {
            // Найдем позицию короля
            var kingPosition = FindKing(color);
            if (kingPosition == null) return false;

            int kingRow = Grid.GetRow(kingPosition);
            int kingCol = Grid.GetColumn(kingPosition);

            // Проверяем, может ли король сделать безопасный ход
            for (int row = kingRow - 1; row <= kingRow + 1; row++)
            {
                for (int col = kingCol - 1; col <= kingCol + 1; col++)
                {
                    if (row < 0 || row > 7 || col < 0 || col > 7) continue;

                    // Проверим, может ли король переместиться на эту клетку
                    if (IsEmpty(row, col) || !IsSameColor(color, ((Image)GetButtonAt(row, col).Content)?.Tag.ToString()))
                    {
                        if (!IsKingInCheckAfterMove(kingRow, kingCol, row, col, color))
                        {
                            return false;
                        }
                    }
                }
            }

            // Если король не может сделать ни одного безопасного хода, это мат
            return true;
        }
        private void CheckForCheckmate()
        {
            if (IsCheckmate(prefix))
            {
                ContentDialog dlg = new ContentDialog
                {
                    Title = "Мат!",
                    Content = $"{(prefix == "W" ? "Белые" : "Чёрные")} выиграли.",
                    CloseButtonText = "OK"
                };
                _ = dlg.ShowAsync();
            }
        }

    }
}
