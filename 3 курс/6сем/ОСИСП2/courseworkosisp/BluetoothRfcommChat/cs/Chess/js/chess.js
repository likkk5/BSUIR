console.log("✅ chess.js загружен!");

let board = null;
let game = new Chess(); // Логика шахмат
let dotNetRef = null;
let whiteSquareGrey = '#a9a9a9';
let blackSquareGrey = '#696969';

function removeGreySquares() {
    document.querySelectorAll('#chessboard .square-55d63').forEach(square => {
        square.style.background = '';
    });
}

function greySquare(square) {
    let squareEl = document.querySelector(`#chessboard .square-${square}`);
    if (!squareEl) return;

    let background = whiteSquareGrey;
    if (squareEl.classList.contains('black-3c85d')) {
        background = blackSquareGrey;
    }

    squareEl.style.background = background;
}

function loadBoard(position = "start", dotNetReference) {
    console.log(`JS: loadBoard вызван с позицией ${position}`);

    dotNetRef = dotNetReference;
    game.load(position);

    board = Chessboard("chessboard", {
        position: position,
        draggable: true,
        pieceTheme: "img/chesspieces/wikipedia/{piece}.png",
        onDragStart: onDragStart,
        onDrop: onDrop,
        onSnapEnd: onSnapEnd,
        onMouseoutSquare: onMouseoutSquare,
        onMouseoverSquare: onMouseoverSquare
    });

    updateStatus();
}

function onDragStart(source, piece) {
    if (game.game_over()) return false;
    if ((game.turn() === "w" && piece.startsWith("b")) ||
        (game.turn() === "b" && piece.startsWith("w"))) return false;
}

async function onDrop(source, target) {
    removeGreySquares();
    let move = { from: source, to: target, promotion: "q" };
    let moveObj = game.move(move);

    if (!moveObj) return "snapback";

    console.log(`♟ Ход принят: ${moveObj.san}`);

    if (dotNetRef) {
        try {
            const moveSuccess = await dotNetRef.invokeMethodAsync("MakeMove", source + target);
            onMoveMade(source + target); 
            if (!moveSuccess) {
                setTimeout(() => game.undo(), 50);
                return "snapback";
            }
            updateBoard(game.fen(), source + target);
            updateStatus();
        } catch (error) {
            console.error("Ошибка при отправке хода:", error);
            setTimeout(() => game.undo(), 50);
            return "snapback";
        }
    }
}

function onMouseoverSquare(square, piece) {
    let moves = game.moves({ square: square, verbose: true });
    if (moves.length === 0) return;
    greySquare(square);
    moves.forEach(m => greySquare(m.to));
}

function onMouseoutSquare(square, piece) {
    removeGreySquares();
}

function onSnapEnd() {
    board.position(game.fen());
}
// Получение хода по Bluetooth
function receiveMove(move) {
    console.log(`🔔 Применение хода от Bluetooth: ${move}`);

    let moveObj = game.move({ from: move.substring(0, 2), to: move.substring(2, 4), promotion: "q" });

    if (!moveObj) {
        console.warn(`❌ Недопустимый ход по Bluetooth: ${move}`);
        return;
    }

    setTimeout(() => {
        updateBoard(game.fen(), move); 
        updateStatus();
    }, 50);
}

function updateBoard(fen, move = null) {
    if (move) {
        // Если ход передан строкой, преобразуем в объект
        if (typeof move === "string") {
            move = { from: move.substring(0, 2), to: move.substring(2, 4) };
        }
        board.move(move.from + "-" + move.to); 
    } else {
        board.position(fen, false); 
    }
    console.log(`♟ Доска обновлена: ${fen}`);
}

function updateStatus() {
    let status = "";
    let moveColor = game.turn() === "w" ? "Белые" : "Чёрные";

    if (game.in_checkmate()) {
        status = `🏁 Игра окончена. ${moveColor} получили мат.`;
    } else if (game.in_draw()) {
        status = "🏁 Игра окончена. Ничья.";
    } else {
        status = `♟ Ходят ${moveColor}`;
        if (game.in_check()) status += `, ${moveColor} под шахом!`;
    }

    console.log(status);
    document.getElementById("status").innerText = status;
    document.getElementById("fen").innerText = game.fen();
    document.getElementById("pgn").innerText = game.pgn();
}

// Дополнительные функции управления доской
function clearBoard() {
    board.clear();
}

function startPosition() {
    board.start();
}

function flipBoard() {
    board.flip();
}

function setWhiteOrientation() {
    board.orientation('white');
}

function setBlackOrientation() {
    board.orientation('black');
}

function showOrientation() {
    console.log("Board orientation is: " + board.orientation());
}
