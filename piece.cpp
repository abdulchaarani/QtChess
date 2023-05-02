#include <QDebug>
#include "piece.hpp"
#include "box.hpp"
#include "chessboard.hpp"
#include "layouts.hpp"
//Styling constants

using namespace layouts;

Piece::Piece(Color color, int row, int column, ChessBoard* board, QWidget* parent)
            : QPushButton(parent), color_(color), coordinates_(row, column), chessboard_(board)
{
    connect(this, SIGNAL(movedPiece()), chessboard_, SLOT(validateMovements()));
    connect(chessboard_, SIGNAL(updateMovements()), this, SLOT(fillAllMovements()));
    connect(&blinkTimer_, &QTimer::timeout, this, &Piece::toggleBlink);
    setStyleSheet (pieceStyle);
    setFixedWidth (buttonSize);
    setFixedHeight(buttonSize);
    setFont       (pieceFont);

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
    setGeometry(column * offset + marginX, row * offset + marginY, buttonSize, buttonSize);
    emit movedPiece();
}


Point& Piece::getCoordinates()
{
    return coordinates_;
}

void Piece::updatePosition()
{
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
        changePosition(newRow, newColumn);
        emit playedFirstMove();
    }

    revertCheck();
}

// recieve the signal that a piece has moved
void Piece::fillAllMovements()
{
    // calls correct overloaded function
    fillMovements();
}

void Piece::killPiece(Piece* victim)
{
    int row{victim->getCoordinates().getRow()};
    int column{victim->getCoordinates().getColumn()};
    changePosition(row, column);
    delete victim;
    revertCheck();
}

void Piece::check()
{
    isChecked = true;
    setStyleSheet(checkedFont);
}

void Piece::revertCheck()
{
    if (isChecked){
        isChecked = false;
        setStyleSheet(pieceStyle);
    }
}

void Piece::toggleBlink()
{
    static int counter{0};
    if (palette().color(QPalette::ButtonText) == Qt::black) {
        setStyleSheet(checkedFont);
        ++counter;
    } else {
        setStyleSheet(pieceStyle);
    }
    if (counter == 4){
        counter = 0;
        blinkTimer_.stop();
        setStyleSheet(pieceStyle);
    }
}
