#include <QDebug>
#include "piece.hpp"
#include "box.hpp"
#include "chessboard.hpp"
//Styling constants

//SHOULD BE PUT IN A NAMESPACE!! :D

const int OFFSET{148};
const int MARGIN{34};
const int PIECE_SIZE{100};

QFont PIECE_FONT("Freeserif", PIECE_SIZE);

QString PIECE_STYLE = "QPushButton{"
                          "  color: black;"
                          "  background-color: none;"
                          "  opacity: 1;"
                          "  border-style: inset;"
                          "  }"
                          "QPushButton:pressed {"
                          "   border-style: inset;"
                          "}";

QString CHECKED = "QPushButton{"
                      "  color: #F4CB16;"
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
    setFont(PIECE_FONT);
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
    if (box->getParent()->getLastPiecePressed() == this && chessboard_->board_[newRow][newColumn] == nullptr){
        changePosition(newRow, newColumn); // copie Point instead of individual coordinate?
        emit playedFirstMove();
    }

    revertCheck();
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
    revertCheck();
}

void Piece::check(){
    isChecked = true;
    setStyleSheet(CHECKED);
}

void Piece::revertCheck(){
    if (isChecked){
        isChecked = false;
        setStyleSheet(PIECE_STYLE);
    }
}
