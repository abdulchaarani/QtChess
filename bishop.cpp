
#include "bishop.hpp"
#include "chessboard.hpp"

Bishop::Bishop(Color color, int row,  int column, ChessBoard* board, QWidget* parent)
    : Piece(color, row, column, board, parent)
{
    // WARNING: TWO DIFFERENT COLORS OF PIECE
    color_ == Color::white ? setText("♗") : setText("♝");
    changePosition(row, column);
}

Bishop::Bishop(Piece* queen) : queen_{queen}
{
    isQueen_ = true;
}

void Bishop::fillMovements()
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

    // check south-east
    for (int nextRow{row + 1}, nextColumn{column + 1}; nextRow < 8 && nextColumn < 8; ++nextRow, ++nextColumn){

        if ((*boardPtr)[nextRow][nextColumn] == nullptr) // if no one, add
            movesPtr->push_back(Point(nextRow, nextColumn));

        else // if somone
            if ((*boardPtr)[nextRow][nextColumn]->color_ != color){ // enemy in sight?
                movesPtr->push_back(Point(nextRow, nextColumn)); // add enemy to list
                break; // stop adding
            }
            else if ((*boardPtr)[nextRow][nextColumn]->color_ == color) // if friendly
                break; // stop adding
    }

    // check south-west
    for (int nextRow{row + 1}, nextColumn{column - 1}; nextRow < 8 && nextColumn >= 0; ++nextRow, --nextColumn){

        if ((*boardPtr)[nextRow][nextColumn] == nullptr) // if no one, add
            movesPtr->push_back(Point(nextRow, nextColumn));

        else // if somone
            if ((*boardPtr)[nextRow][nextColumn]->color_ != color){ // enemy in sight?
                movesPtr->push_back(Point(nextRow, nextColumn)); // add enemy to list
                break; // stop adding
            }
            else if ((*boardPtr)[nextRow][nextColumn]->color_ == color) // if friendly
                break; // stop adding
    }

    // check north-west
    for (int nextRow{row - 1}, nextColumn{column - 1}; nextRow >= 0 && nextColumn >= 0; --nextRow, --nextColumn){

        if ((*boardPtr)[nextRow][nextColumn] == nullptr) // if no one, add
            movesPtr->push_back(Point(nextRow, nextColumn));

        else // if somone
            if ((*boardPtr)[nextRow][nextColumn]->color_ != color){ // enemy in sight?
                movesPtr->push_back(Point(nextRow, nextColumn)); // add enemy to list
                break; // stop adding
            }
            else if ((*boardPtr)[nextRow][nextColumn]->color_ == color) // if friendly
                break; // stop adding
    }

    // check north-east
    for (int nextRow{row - 1}, nextColumn{column + 1}; nextRow >= 0 && nextColumn < 8; --nextRow, ++nextColumn){

        if ((*boardPtr)[nextRow][nextColumn] == nullptr) // if no one, add
            movesPtr->push_back(Point(nextRow, nextColumn));

        else // if somone
            if ((*boardPtr)[nextRow][nextColumn]->color_ != color){ // enemy in sight?
                movesPtr->push_back(Point(nextRow, nextColumn)); // add enemy to list
                break; // stop adding
            }
            else if ((*boardPtr)[nextRow][nextColumn]->color_ == color) // if friendly
                break; // stop adding
    }

}
