
#include <QDebug>
#include "pieces.hpp"
#include "box.hpp"
#include "chessboard.hpp"

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
    id_ = ++idCount;
    setStyleSheet(PIECE_STYLE);

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


Point& Piece::getCoordinates() {return coordinates_;}

void Piece::updatePosition(){
    QObject* senderObject = QObject::sender();
    if (senderObject == nullptr)
        return;

    auto box = qobject_cast<Box*>(senderObject);
    //qDebug() << box->getCoordinates().getRow() << ", " << box->getCoordinates().getColumn();

    if (box->getParent()->getPiecePressed() == this && !box->isOccupied()){
        possessBox(box);
        changePosition(box->getCoordinates().getRow(), box->getCoordinates().getColumn()); // copie?

    }
}

void Piece::possessBox(Box* box){
    if (possessedBox_ != nullptr)
        possessedBox_->unoccupyBox();


    possessedBox_ = box;
    box->occupyBox();
}


void Piece::fillAllMovements(){
    fillMovements();
}

King::King(int row,  int column, ChessBoard* board, QWidget* parent) : Piece(row, column, board, parent)
{
    setText("♔");
    setFont(PIECE_FONT);
    changePosition(row, column);
}

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

Knight::Knight(int row,  int column, ChessBoard* board, QWidget* parent) : Piece(row, column, board, parent)
{
    setText("♘");
    setFont(PIECE_FONT);
    changePosition(row, column);
}

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
