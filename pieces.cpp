
#include <QDebug>
#include "pieces.hpp"
#include "box.hpp"
#include "chessboard.hpp"

//Styling constants

const int OFFSET{148};
const int MARGIN{34};
const int PIECE_SIZE{100};

QFont PIECE_FONT("Freeserif", 100);

QString PIECE_STYLE = "QPushButton{"
                          "  background-color: none;"
                          "  border-style: inset;"
                          "  }"
                          "QPushButton:pressed {"
                          "   border-style: inset;"
                          "}";

Piece::Piece(int row, int column, ChessBoard* board, QWidget* parent) : QPushButton(parent), coordinates_(row, column), chessboard_(board)
{
    connect(this, SIGNAL(movedPiece()), chessboard_, SLOT(validateMovements()));
    connect(chessboard_, SIGNAL(updateMovements()), this, SLOT(fillAllMovements()));
    setStyleSheet(PIECE_STYLE);

    // UNUSED
    id_ = ++idCount;

}

void Piece::changePosition(int row, int column)
{
    // remove previous location on board
    chessboard_->board_[coordinates_.getRow()][coordinates_.getColumn()] = nullptr;
    // change location
    coordinates_.setRow(row);
    coordinates_.setColumn(column);
    // add new location to board
    chessboard_->board_[row][column] = this;
    setGeometry(column * OFFSET + MARGIN +column/2, row * OFFSET + MARGIN  + row/2, PIECE_SIZE, PIECE_SIZE);
    emit movedPiece();
}


Point& Piece::getCoordinates() { return coordinates_; }

void Piece::updatePosition(){
    // get which box just got clicked
    QObject* senderObject = QObject::sender();
    if (senderObject == nullptr)
        return;

    auto box = qobject_cast<Box*>(senderObject);

    // get the boxes' coordinates
    int newRow{box->getCoordinates().getRow()};
    int newColumn {box->getCoordinates().getColumn()};

    // if there are no friendlies on this position, go to box
    if (box->getParent()->getPiecePressed() == this && chessboard_->board_[newRow][newColumn] == nullptr){
        changePosition(newRow, newColumn); // copie Point instead of individual coordinate?

    }
}

// recieve the signal that a piece has moved
void Piece::fillAllMovements(){
    // calls correct overloaded function
    fillMovements();
}

King::King(int row,  int column, ChessBoard* board, QWidget* parent, Colour colour) : Piece(row, column, board, parent)
{
    if(colour == BLACK) {
        setText("♚");
        setFont(PIECE_FONT);
        changePosition(row, column);
    }
    else if(colour == WHITE) {
        setText("♔");
        setFont(PIECE_FONT);
        changePosition(row, column);
    }

}


// Error bound checking
void King::fillMovements(){ // to beautify :(
    movements.clear();

    int row{coordinates_.getRow()};
    int column{coordinates_.getColumn()};

    if ((row + 1) < 8)
        if(chessboard_->board_[row + 1][column] == nullptr) // or enemy
            movements.push_back(Point(row + 1, column));
    if ((row - 1) >= 0)
        if(chessboard_->board_[row - 1][column] == nullptr)
            movements.push_back(Point(row - 1, column));
    if ((column + 1) < 8)
        if(chessboard_->board_[row][column + 1] == nullptr)
            movements.push_back(Point(row, column + 1));
    if ((column - 1 ) >= 0)
        if(chessboard_->board_[row][column - 1] == nullptr)
            movements.push_back(Point(row, column - 1));
}
// Checking for checks
void King::check()
{
    if(this->colour_ == WHITE) // not sure if best way to write it yet..
    {
        for(auto& piece : blackPieces)
    }
}

Knight::Knight(int row,  int column, ChessBoard* board, QWidget* parent, Colour colour) : Piece(row, column, board, parent)
{
    if(colour == BLACK) {
        setText("♞");
        setFont(PIECE_FONT);
        changePosition(row, column);
    }
    else if(colour == WHITE) {
        setText("♘");
        setFont(PIECE_FONT);
        changePosition(row, column);
    }
}

// Error bound checking
void Knight::fillMovements(){// to beautify :(
    movements.clear();

    int row{coordinates_.getRow()};
    int column{coordinates_.getColumn()};

    if (((row + 1) < 8) && ((column + 2) < 8))
        if(chessboard_->board_[row + 1][column + 2] == nullptr)
            movements.push_back(Point(row + 1, column + 2));
    if (((row + 1) < 8) && ((column - 2) >= 0))
        if(chessboard_->board_[row + 1][column - 2] == nullptr)
            movements.push_back(Point(row + 1, column - 2));
    if (((row - 1) >= 0) && ((column + 2) < 8))
        if(chessboard_->board_[row - 1][column + 2] == nullptr)
            movements.push_back(Point(row - 1, column + 2));
    if (((row - 1) >= 0) && ((column - 2) >= 0))
        if(chessboard_->board_[row - 1][column - 2] == nullptr)
            movements.push_back(Point(row - 1, column - 2));
    if (((row + 2) < 8) && ((column + 1) < 8))
        if(chessboard_->board_[row + 2][column + 1] == nullptr)
            movements.push_back(Point(row + 2, column + 1));
    if (((row + 2) < 8) && ((column - 1) >= 0))
        if(chessboard_->board_[row + 2][column - 1] == nullptr)
            movements.push_back(Point(row + 2, column - 1));
    if (((row - 2) >= 0) && ((column + 1) < 8))
        if(chessboard_->board_[row - 2][column + 1] == nullptr)
            movements.push_back(Point(row - 2, column + 1));
    if (((row - 2) >= 0) && ((column - 1) >= 0))
        if(chessboard_->board_[row - 2][column - 1] == nullptr)
            movements.push_back(Point(row - 2, column - 1));
}

Pawn::Pawn(int row,  int column, ChessBoard* board, QWidget* parent, Colour colour) : Piece(row, column, board, parent)
{

    if(colour == BLACK) {
        setText("♟︎");
        setFont(PIECE_FONT);
        changePosition(row, column);
    }
    else if(colour == WHITE) {
        setText("♙");
        setFont(PIECE_FONT);
        changePosition(row, column);
    }
}

// Error bound checking
void Pawn::fillMovements(){ // to beautify :(
    movements.clear();

    int row{coordinates_.getRow()};
    int column{coordinates_.getColumn()};

    if ((row + 1) < 8)
        if(chessboard_->board_[row + 1][column] == nullptr) // or enemy
            movements.push_back(Point(row + 1, column));
    if ((row - 1) >= 0)
        if(chessboard_->board_[row - 1][column] == nullptr)
            movements.push_back(Point(row - 1, column));
    if (firstMove_)
        if ((row + 2) < 8)
            if(chessboard_->board_[row + 2][column] == nullptr) // or enemy
                movements.push_back(Point(row + 2, column));
}
