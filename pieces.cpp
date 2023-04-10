
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

QString CHECKED = "QPushButton{"
                      "  color: yellow;"
                      "  background-color: none;"
                      "  border-style: inset;"
                      "  }"
                      "QPushButton:pressed {"
                      "   border-style: inset;"
                      "}";

Piece::Piece(Color color, int row, int column, ChessBoard* board, QWidget* parent)
            : QPushButton(parent), color_(color), coordinates_(row, column), chessboard_(board)
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

    // if I am a king and I moved, do something before moving
//    if (dynamic_cast<King*>(this))
//        if (chessboard_->getPiecePressed() == this)
//            isChecked();

    // if there are no friendlies on this position, go to box
    if (box->getParent()->getLastPiecePressed() == this && chessboard_->board_[newRow][newColumn] == nullptr){
        changePosition(newRow, newColumn); // copie Point instead of individual coordinate?
    }
}

// recieve the signal that a piece has moved
void Piece::fillAllMovements(){
    // calls correct overloaded function
    fillMovements();
}

void Piece::killPiece(Piece* victim){
    int row{victim->getCoordinates().getRow()};
    int column{victim->getCoordinates().getColumn()};
    changePosition(row, column);
    delete victim;
}

King::King(Color color, int row,  int column, ChessBoard* board, QWidget* parent)
          : Piece(color, row, column, board, parent)
{
    // WARNING: TWO DIFFERENT COLORS OF PIECE
    color_ == Color::WHITE ? setText("♔") : setText("♚");
    setFont(PIECE_FONT);
    changePosition(row, column);
}


// Error bound checking
void King::fillMovements(){ // to beautify :(
    movements.clear();

    int row{coordinates_.getRow()};
    int column{coordinates_.getColumn()};

    if ((row + 1) < 8)
        if(chessboard_->board_[row + 1][column] == nullptr || chessboard_->board_[row + 1][column]->color_ != color_) // or enemy
            movements.push_back(Point(row + 1, column));
    if ((row - 1) >= 0)
        if(chessboard_->board_[row - 1][column] == nullptr || chessboard_->board_[row - 1][column]->color_ != color_)
            movements.push_back(Point(row - 1, column));
    if ((column + 1) < 8)
        if(chessboard_->board_[row][column + 1] == nullptr || chessboard_->board_[row][column + 1]->color_ != color_)
            movements.push_back(Point(row, column + 1));
    if ((column - 1 ) >= 0)
        if(chessboard_->board_[row][column - 1] == nullptr || chessboard_->board_[row][column - 1]->color_ != color_)
            movements.push_back(Point(row, column - 1));
}

Knight::Knight(Color color, int row,  int column, ChessBoard* board, QWidget* parent)
              : Piece(color, row, column, board, parent)
{
    // WARNING: TWO DIFFERENT COLORS OF PIECE
    color_ == Color::WHITE ? setText("♘") : setText("♞");
    setFont(PIECE_FONT);
    changePosition(row, column);
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

Pawn::Pawn(Color color, int row,  int column, ChessBoard* board, QWidget* parent)
            : Piece(color, row, column, board, parent)
{
    // WARNING: TWO DIFFERENT COLORS OF PIECE
    color_ == Color::WHITE ? setText("♙") : setText("♟︎");
    setFont(PIECE_FONT);
    changePosition(row, column);
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
