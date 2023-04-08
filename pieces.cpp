
#include <QDebug>
#include "pieces.hpp"
#include "box.hpp"

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

Piece::Piece(int row, int column, QWidget* parent) : QPushButton(parent), coordinates_(row,column)
{
    changePosition(row, column);
    this->setStyleSheet(PIECE_STYLE);
}

void Piece::changePosition(int row, int column)
{
    this->coordinates_.setRow(row);
    this->coordinates_.setColumn(column);
    this->setGeometry(row * OFFSET + MARGIN +row/2, column * OFFSET + MARGIN  + column/2, PIECE_SIZE, PIECE_SIZE);
}


Point& Piece::getCoordinates() {return coordinates_;}

King::King(int row,  int column,  QWidget* parent) : Piece(column, row, parent)
{
    this->setText("♔");
    this->setFont(PIECE_FONT);
}

void King::fillMovements(){
    movements.clear();
    movements.push_back(Point(coordinates_.getRow() + 1, coordinates_.getColumn()));
    movements.push_back(Point(coordinates_.getRow() - 1, coordinates_.getColumn()));
    movements.push_back(Point(coordinates_.getRow(), coordinates_.getColumn() + 1));
    movements.push_back(Point(coordinates_.getRow(), coordinates_.getColumn() - 1));
}

void Piece::updatePosition(){
    QObject* senderObject = QObject::sender();
    if (senderObject == nullptr)
        return;

    auto box = qobject_cast<Box*>(senderObject);
    qDebug() << box->getCoordinates().getRow() << "," << box->getCoordinates().getColumn();
    this->changePosition(box->getCoordinates().getRow(), box->getCoordinates().getColumn()); // copie?
    this->fillMovements();
}
