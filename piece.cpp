#include "piece.hpp"

#include <QDebug>

#include "box.hpp"
#include "chessboard.hpp"
// Styling constants

// SHOULD BE PUT IN A NAMESPACE!! :D

const double OFFSET{100.5};
const int MARGIN_X{10};
const int MARGIN_Y{30};
const int PIECE_SIZE{60};
const int BUTTON_SIZE{100};

QFont PIECE_FONT("Segoe UI Symbol", PIECE_SIZE);

QString PIECE_STYLE =
    "QPushButton{"
    "  color: black;"
    "  background-color: none;"
    "  border-style: inset;"
    "  }"
    "QPushButton:pressed {"
    "   border-style: inset;"
    "}";

QString CHECKED =
    "QPushButton{"
    "  color: #F4CB16;"
    "  background-color: none;"
    "  border-style: inset;"
    "  }"
    "QPushButton:pressed {"
    "   border-style: inset;"
    "}";

Piece::Piece(Color color, int row, int column, ChessBoard* board, QWidget* parent)
    : QPushButton(parent), color_(color), coordinates_(row, column), chessboard_(board) {
    connect(this, SIGNAL(movedPiece()), chessboard_, SLOT(validateMovements()));
    connect(chessboard_, SIGNAL(updateMovements()), this, SLOT(fillAllMovements()));
    connect(&blinkTimer_, &QTimer::timeout, this, &Piece::toggleBlink);
    setStyleSheet(PIECE_STYLE);
    setFixedSize(BUTTON_SIZE, BUTTON_SIZE);
    setFont(PIECE_FONT);
}

void Piece::changePosition(int row, int column) {
    // remove previous location on board
    chessboard_->board_[coordinates_.getRow()][coordinates_.getColumn()] = nullptr;
    // change location
    coordinates_.setRow(row);
    coordinates_.setColumn(column);
    // add new location to board
    chessboard_->board_[row][column] = this;
    setGeometry(column * OFFSET + MARGIN_X, row * OFFSET + MARGIN_Y, BUTTON_SIZE, BUTTON_SIZE);
    emit movedPiece();
}

Point& Piece::getCoordinates() { return coordinates_; }

void Piece::updatePosition() {
    // get which box just got clicked
    QObject* senderObject = QObject::sender();
    if (senderObject == nullptr)
        return;

    auto box = qobject_cast<Box*>(senderObject);

    // get the boxes' coordinates
    int newRow{box->getCoordinates().getRow()};
    int newColumn{box->getCoordinates().getColumn()};

    // if there are no friendlies on this position, go to box
    if (box->getParent()->getLastPiecePressed() == this && chessboard_->board_[newRow][newColumn] == nullptr) {
        changePosition(newRow, newColumn);  // copie Point instead of individual coordinate?
        emit playedFirstMove();
    }

    revertCheck();
}

// recieve the signal that a piece has moved
void Piece::fillAllMovements() {
    // calls correct overloaded function
    fillMovements();
}

void Piece::killPiece(Piece* victim) {
    int row{victim->getCoordinates().getRow()};
    int column{victim->getCoordinates().getColumn()};
    changePosition(row, column);
    delete victim;
    revertCheck();
}

void Piece::check() {
    isChecked = true;
    setStyleSheet(CHECKED);
}

void Piece::revertCheck() {
    if (isChecked) {
        isChecked = false;
        setStyleSheet(PIECE_STYLE);
    }
}

void Piece::toggleBlink() {
    static int counter{0};
    if (palette().color(QPalette::ButtonText) == Qt::black) {
        setStyleSheet(CHECKED);
        ++counter;
    } else {
        setStyleSheet(PIECE_STYLE);
    }
    if (counter == 4) {
        counter = 0;
        blinkTimer_.stop();
        setStyleSheet(PIECE_STYLE);
    }
}
