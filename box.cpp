
#include "box.hpp"
#include "chessboard.hpp"

// Stylesheets for the box colors

const QString WHITE_BOX = "QPushButton{"
                     "  background-color: rgb(238, 238, 212);"
                     "  border-style: inset;"
                     "  }"
                     "QPushButton:pressed {"
                     "   border-style: inset;"
                     "}";

const QString BLACK_BOX = "QPushButton{"
                     "  background-color: rgb(126, 148, 90);"
                     "  border-style: inset;"
                     "  }"
                     "QPushButton:pressed {"
                     "   border-style: inset;"
                     "}";

const QString HIGHLIGHT = "QPushButton{"
                     "  background-color: red;"
                     "  border-style: inset;"
                     "  }"
                     "QPushButton:pressed {"
                     "   border-style: inset;"
                     "}";

Box::Box(int row, int column, ChessBoard *parent) : QPushButton(parent), coordinates_(row, column)
{
    // to alternate black and white colors on the chessboard
    counter_ ? setColorBlack() : setColorWhite();
    if (coordinates_.getColumn() != 7)
        counter_ = !counter_;

    // save chessboard as an attribute
    board_ = parent;
}


void Box::setColorWhite(){

    this->setStyleSheet(WHITE_BOX);
    color_ = true;
}
void Box::setColorBlack(){


    this->setStyleSheet(BLACK_BOX);
    color_ = false;
}

void Box::highlightColor(){
    // which piece got clicked
    QObject* senderObject = QObject::sender();
    if (senderObject == nullptr)
        return;

    auto piece = qobject_cast<Piece*>(senderObject);

    // if not your turn no touchy
    if (piece->color_ != board_->currentPlayer)
        return;

    handleClick();

    board_->setPiecePressed(piece);

    // If box is in the possible moveset of the clicked piece, highlight

    for(auto && movement : piece->movements)
        if (movement == this->coordinates_){
            movableBox_ = true;
            this->setStyleSheet(HIGHLIGHT);
        }
}

void Box::revertColor(){
    color_ ? setColorWhite() : setColorBlack();
}



void Box::handleClick()
{
    // if the next clicked box is not a highlighted one, cancel movement
    // else make the piece goto said box

    auto currentBox = board_->getBoxPressed();
    if (currentBox == nullptr)
        return;
    else if (currentBox == this)
        if (currentBox->movableBox_)
            emit goTo();

    revertColor();
    movableBox_ = false;
}
