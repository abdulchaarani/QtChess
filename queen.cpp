
#include "queen.hpp"
#include "chessboard.hpp"

// Qt doesnt seem to support multiple heritage very well,
// Will try in the future to derive Queen from Rook and Bishop correctly
// In the meantime, Queen will have a member bishop and rook

Queen::Queen(Color color, int row,  int column, ChessBoard* board, QWidget* parent)
     : Piece(color, column, row, board, parent)
     , bishop_{new Bishop(this)}
     , rook_{new Rook(this)}
{
    // WARNING: TWO DIFFERENT COLORS OF PIECE
    color_ == Color::white ? setText("♕") : setText("♛");
    changePosition(row, column);
}

void Queen::fillMovements()
{
    movements.clear();
    bishop_->fillMovements();
    rook_->fillMovements();
}
