
#include "queen.hpp"
namespace model{
Queen::Queen(Color color, int row, int column)
    :Piece(color, row, column)

{
    color_ == Color::white ? display_ = "♕" : display_ = "♛";
}

void Queen::fillMovements(BoardView board){
    movements.clear();
    Bishop::fillMovements(board);
    Rook::fillMovements(board);
}
}
