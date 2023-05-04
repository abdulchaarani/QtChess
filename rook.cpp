
#include "rook.hpp"

Rook::Rook(Color color, int row, int column) : Piece(color, row, column)
{
    color_ == Color::white ? display_ = "♖" : display_ = "♜";
}

void Rook::fillMovements(BoardView board)
{
    // if not a queen, since queens inherit from rook
    // and shares same instance of movements
    if (display_ != "♕" && display_ != "♛")
        movements.clear();

    auto [row, column] = coordinates_;

    // check to the right
    for (int nextColumn{column + 1}; nextColumn < 8; ++nextColumn){

        if (board[row][nextColumn] == nullptr) // if no one, add
            movements.push_front({row, nextColumn});

        else
            if (board[row][nextColumn]->color_ != color_){ // enemy in sight?
                movements.push_front({row, nextColumn}); // add enemy to list
                break;
            }
            else if (board[row][nextColumn]->color_ == color_) // if friendly
                break;
    }
    // check to the left
    for (int nextColumn{column - 1}; nextColumn >= 0; --nextColumn){

        if (board[row][nextColumn] == nullptr) // if no one, add
            movements.push_front({row, nextColumn});

        else // if somone
            if (board[row][nextColumn]->color_ != color_){ // enemy in sight?
                movements.push_front({row, nextColumn}); // add enemy to list
                break; // stop adding
            }
            else if (board[row][nextColumn]->color_ == color_) // if friendly
                break;
    }

    // check below
    for (int nextRow{row + 1}; nextRow < 8; ++nextRow){

        if (board[nextRow][column] == nullptr) // if no one, add
            movements.push_front({nextRow, column});

        else // if someone there
            if (board[nextRow][column]->color_ != color_){ // if enemy in sight
                movements.push_front({nextRow, column}); // add enemy to list
                break; // stop adding
            }
            else if (board[nextRow][column]->color_ == color_) // if friendly
                break;
    }
    // check above
    for (int nextRow{row - 1}; nextRow >= 0; --nextRow){

        if (board[nextRow][column] == nullptr) // if no one, add
            movements.push_front({nextRow, column});

        else // if somone
            if (board[nextRow][column]->color_ != color_){ // enemy in sight?
                movements.push_front({nextRow, column}); // add enemy to list
                break; // stop adding
            }
            else if (board[nextRow][column]->color_ == color_) // if friendly
                break;
    }

}
