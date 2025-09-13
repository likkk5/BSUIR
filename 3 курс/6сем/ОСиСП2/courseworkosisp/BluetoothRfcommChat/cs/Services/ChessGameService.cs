using ChessDotNet;
using SDKTemplate;
using Windows.UI.Xaml.Controls;

namespace RfcommChat.Services
{
    public class ChessGameService
    {
        private ChessGame game = new ChessGame();

        public WebView WebViewReference { get; set; } // подключаем WebView

        public string GetFen() => game.GetFen();

        public bool MakeMove(string move)
        {
            var chessMove = new Move(move.Substring(0, 2), move.Substring(2, 2), game.WhoseTurn);
            if (game.IsValidMove(chessMove))
            {
                game.MakeMove(chessMove, true);
                return true;
            }
            return false;
        }

        public void ReceiveMoveFromBluetooth(string move)
        {
            var chessMove = new Move(move.Substring(0, 2), move.Substring(2, 2), game.WhoseTurn);
            if (game.IsValidMove(chessMove))
            {
                game.MakeMove(chessMove, true);

                // Обновляем доску через JS
                WebViewReference?.InvokeScriptAsync("receiveMove", new[] { move });
            }
        }

        public void ResetGame()
        {
            game = new ChessGame();
        }
    }
}
