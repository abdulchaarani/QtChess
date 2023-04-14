
#include "bishop.hpp"
#include "chessboard.hpp"

Bishop::Bishop(Color color, int row,  int column, ChessBoard* board, QWidget* parent)
    : Piece(color, row, column, board, parent)
{
    // WARNING: TWO DIFFERENT COLORS OF PIECE
    color_ == Color::WHITE ? setText("♗") : setText("♝");
    changePosition(row, column);
}

void Bishop::fillMovements(){ // to beautify :(
    // if not a queen, dont delete movements (helps with multiple inheritance :p)
    if (text() != "♕" && text() != "♛")
        movements.clear();

    int row{coordinates_.getRow()};
    int column{coordinates_.getColumn()};

    // check south-east
    for (int nextRow{row + 1}, nextColumn{column + 1}; nextRow < 8 && nextColumn < 8; ++nextRow, ++nextColumn){

        if (chessboard_->board_[nextRow][nextColumn] == nullptr) // if no one, add
            movements.push_back(Point(nextRow, nextColumn));

        else // if somone
            if (chessboard_->board_[nextRow][nextColumn]->color_ != color_){ // enemy in sight?
                movements.push_back(Point(nextRow, nextColumn)); // add enemy to list
                break; // stop adding (u aint a ghost)
            }
            else if (chessboard_->board_[nextRow][nextColumn]->color_ == color_) // if friendly
                break; // dont add em, no friendly fire plz, stop adding (u aint a ghost)
    }

    // check south-west
    for (int nextRow{row + 1}, nextColumn{column - 1}; nextRow < 8 && nextColumn >= 0; ++nextRow, --nextColumn){

        if (chessboard_->board_[nextRow][nextColumn] == nullptr) // if no one, add
            movements.push_back(Point(nextRow, nextColumn));

        else // if somone
            if (chessboard_->board_[nextRow][nextColumn]->color_ != color_){ // enemy in sight?
                movements.push_back(Point(nextRow, nextColumn)); // add enemy to list
                break; // stop adding (u aint a ghost)
            }
            else if (chessboard_->board_[nextRow][nextColumn]->color_ == color_) // if friendly
                break; // dont add em, no friendly fire plz, stop adding (u aint a ghost)
    }

    // check north-west
    for (int nextRow{row - 1}, nextColumn{column - 1}; nextRow >= 0 && nextColumn >= 0; --nextRow, --nextColumn){

        if (chessboard_->board_[nextRow][nextColumn] == nullptr) // if no one, add
            movements.push_back(Point(nextRow, nextColumn));

        else // if somone
            if (chessboard_->board_[nextRow][nextColumn]->color_ != color_){ // enemy in sight?
                movements.push_back(Point(nextRow, nextColumn)); // add enemy to list
                break; // stop adding (u aint a ghost)
            }
            else if (chessboard_->board_[nextRow][nextColumn]->color_ == color_) // if friendly
                break; // dont add em, no friendly fire plz, stop adding (u aint a ghost)
    }

    // check north-east
    for (int nextRow{row - 1}, nextColumn{column + 1}; nextRow >= 0 && nextColumn < 8; --nextRow, ++nextColumn){

        if (chessboard_->board_[nextRow][nextColumn] == nullptr) // if no one, add
            movements.push_back(Point(nextRow, nextColumn));

        else // if somone
            if (chessboard_->board_[nextRow][nextColumn]->color_ != color_){ // enemy in sight?
                movements.push_back(Point(nextRow, nextColumn)); // add enemy to list
                break; // stop adding (u aint a ghost)
            }
            else if (chessboard_->board_[nextRow][nextColumn]->color_ == color_) // if friendly
                break; // dont add em, no friendly fire plz, stop adding (u aint a ghost)
    }

}
