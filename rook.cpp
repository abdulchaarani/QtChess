
#include "rook.hpp"
#include "chessboard.hpp"

Rook::Rook(Color color, int row,  int column, ChessBoard* board, QWidget* parent)
    : Piece(color, row, column, board, parent)
{
    // WARNING: TWO DIFFERENT COLORS OF PIECE
    color_ == Color::white ? setText("♖") : setText("♜");
    changePosition(row, column);
}

Rook::Rook(Piece* queen) : queen_{queen}
{
    isQueen_ = true;
}

void Rook::fillMovements()
{
    // these variables help with queen inheritance/composition
    // to avoid duplication of mouvement filling sequence

    std::list<Point>* movesPtr = &movements;
    std::array<std::array<Piece*, 8>, 8>* boardPtr = &chessboard_->board_;
    Point* coordinatesPtr = &coordinates_;
    Color color = color_;

    if (isQueen_){
        movesPtr = &queen_->movements;
        boardPtr = &queen_->chessboard_->board_;
        coordinatesPtr = &queen_->coordinates_;
        color = queen_->color_;
    }
    else{
        movements.clear();
    }

    int row{coordinatesPtr->getRow()};
    int column{coordinatesPtr->getColumn()};

    // check to the right
    for (int nextColumn{column + 1}; nextColumn < 8; ++nextColumn){

        if ((*boardPtr)[row][nextColumn] == nullptr) // if no one, add
            movesPtr->push_back(Point(row, nextColumn));

        else // if somone
            if ((*boardPtr)[row][nextColumn]->color_ != color){ // enemy in sight?
                movesPtr->push_back(Point(row, nextColumn)); // add enemy to list
                break; // stop adding (u aint a ghost)
            }
            else if ((*boardPtr)[row][nextColumn]->color_ == color) // if friendly
                break; // dont add em, no friendly fire plz, stop adding (u aint a ghost)
    }
    // check to the left
    for (int nextColumn{column - 1}; nextColumn >= 0; --nextColumn){

        if ((*boardPtr)[row][nextColumn] == nullptr) // if no one, add
            movesPtr->push_back(Point(row, nextColumn));

        else // if somone
            if ((*boardPtr)[row][nextColumn]->color_ != color){ // enemy in sight?
                movesPtr->push_back(Point(row, nextColumn)); // add enemy to list
                break; // stop adding (u aint a ghost)
            }
            else if ((*boardPtr)[row][nextColumn]->color_ == color) // if friendly
                break; // dont add em, no friendly fire plz, stop adding (u aint a ghost)
    }

    // check below
    for (int nextRow{row + 1}; nextRow < 8; ++nextRow){

        if ((*boardPtr)[nextRow][column] == nullptr) // if no one, add
            movesPtr->push_back(Point(nextRow, column));

        else // if someone there
            if ((*boardPtr)[nextRow][column]->color_ != color){ // if enemy in sight
                movesPtr->push_back(Point(nextRow, column)); // add enemy to list
                break; // stop adding (u aint a ghost)
            }
            else if ((*boardPtr)[nextRow][column]->color_ == color) // if friendly
                break; // dont add em, no friendly fire plz, stop adding (u aint a ghost)
    }
    // check above
    for (int nextRow{row - 1}; nextRow >= 0; --nextRow){

        if ((*boardPtr)[nextRow][column] == nullptr) // if no one, add
            movesPtr->push_back(Point(nextRow, column));

        else // if somone
            if ((*boardPtr)[nextRow][column]->color_ != color){ // enemy in sight?
                movesPtr->push_back(Point(nextRow, column)); // add enemy to list
                break; // stop adding (u aint a ghost)
            }
            else if ((*boardPtr)[nextRow][column]->color_ == color) // if friendly
                break; // dont add em, no friendly fire plz, stop adding (u aint a ghost)
    }

}
