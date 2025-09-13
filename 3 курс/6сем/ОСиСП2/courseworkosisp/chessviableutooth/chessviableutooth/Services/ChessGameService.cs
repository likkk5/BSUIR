using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using chessviableutooth.Components.Pages;
using System;
using ChessDotNet;
namespace chessviableutooth.Services
{

    public class ChessGameService
    {

        private ChessGame game = new();

        public string GetFen() => game.GetFen(); // Получаем текущее состояние доски в FEN-формате

        public bool MakeMove(string move)
        {
            Move chessMove = new Move(move.Substring(0, 2), move.Substring(2, 2), game.WhoseTurn);

            // Проверяем, валиден ли ход
            if (game.IsValidMove(chessMove))
            {
                game.MakeMove(chessMove, true); // Если ход допустим, то выполняем его
                return true; // Успех, ход был принят
            }

            // Если ход недопустим, возвращаем false
            return false;
        }


        public void ResetGame()
        {
            game = new ChessGame(); // Начинаем новую игру
        }
    }

}
