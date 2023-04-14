
#include "queen.hpp"
#include "chessboard.hpp"

Queen::Queen(Color color, int row,  int column, ChessBoard* board, QWidget* parent)
     : Piece(color, column, row, board, parent)

{
    // WARNING: TWO DIFFERENT COLORS OF PIECE
    color_ == Color::WHITE ? setText("♕") : setText("♛");
    changePosition(row, column);
}

void Queen::fillMovements(){
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


    // check to the right
    for (int nextColumn{column + 1}; nextColumn < 8; ++nextColumn){

        if (chessboard_->board_[row][nextColumn] == nullptr) // if no one, add
            movements.push_back(Point(row, nextColumn));

        else // if somone
            if (chessboard_->board_[row][nextColumn]->color_ != color_){ // enemy in sight?
                movements.push_back(Point(row, nextColumn)); // add enemy to list
                break; // stop adding (u aint a ghost)
            }
            else if (chessboard_->board_[row][nextColumn]->color_ == color_) // if friendly
                break; // dont add em, no friendly fire plz, stop adding (u aint a ghost)
    }
    // check to the left
    for (int nextColumn{column - 1}; nextColumn >= 0; --nextColumn){

        if (chessboard_->board_[row][nextColumn] == nullptr) // if no one, add
            movements.push_back(Point(row, nextColumn));

        else // if somone
            if (chessboard_->board_[row][nextColumn]->color_ != color_){ // enemy in sight?
                movements.push_back(Point(row, nextColumn)); // add enemy to list
                break; // stop adding (u aint a ghost)
            }
            else if (chessboard_->board_[row][nextColumn]->color_ == color_) // if friendly
                break; // dont add em, no friendly fire plz, stop adding (u aint a ghost)
    }

    // check below
    for (int nextRow{row + 1}; nextRow < 8; ++nextRow){

        if (chessboard_->board_[nextRow][column] == nullptr) // if no one, add
            movements.push_back(Point(nextRow, column));

        else // if someone there
            if (chessboard_->board_[nextRow][column]->color_ != color_){ // if enemy in sight
                movements.push_back(Point(nextRow, column)); // add enemy to list
                break; // stop adding (u aint a ghost)
            }
            else if (chessboard_->board_[nextRow][column]->color_ == color_) // if friendly
                break; // dont add em, no friendly fire plz, stop adding (u aint a ghost)
    }
    // check above
    for (int nextRow{row - 1}; nextRow >= 0; --nextRow){

        if (chessboard_->board_[nextRow][column] == nullptr) // if no one, add
            movements.push_back(Point(nextRow, column));

        else // if somone
            if (chessboard_->board_[nextRow][column]->color_ != color_){ // enemy in sight?
                movements.push_back(Point(nextRow, column)); // add enemy to list
                break; // stop adding (u aint a ghost)
            }
            else if (chessboard_->board_[nextRow][column]->color_ == color_) // if friendly
                break; // dont add em, no friendly fire plz, stop adding (u aint a ghost)
    }


}
