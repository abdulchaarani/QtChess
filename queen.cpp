
#include "queen.hpp"
#include "chessboard.hpp"

Queen::Queen(Color color, int row,  int column, ChessBoard* board, QWidget* parent)
     : Piece(color, column, row, board, parent)
     , Rook(color, column, row, board, parent)
     , Bishop(color, column, row, board, parent)
{
    // WARNING: TWO DIFFERENT COLORS OF PIECE
    color_ == Color::WHITE ? setText("♕") : setText("♛");
    changePosition(row, column);
}

void Queen::fillMovements(){
    movements.clear();
    Rook::fillMovements();
    Bishop::fillMovements();
}
