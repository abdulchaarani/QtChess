
#include "box.hpp"
#include "chessboard.hpp"

const QString WHITE = "QPushButton{"
                     "  background-color: rgb(238, 238, 212);"
                     "  border-style: inset;"
                     "  }"
                     "QPushButton:pressed {"
                     "   border-style: inset;"
                     "}";

const QString BLACK = "QPushButton{"
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

    parent_ = parent;
    //parent_ = dynamic_cast<ChessBoard*>(parent);
}


void Box::setColorWhite(){

    this->setStyleSheet(WHITE);
    color_ = true;
}
void Box::setColorBlack(){


    this->setStyleSheet(BLACK);
    color_ = false;
}

void Box::highlightColor(){
    handleClick();

    QObject* senderObject = QObject::sender();
    if (senderObject == nullptr)
        return;

    auto piece = qobject_cast<Piece*>(senderObject);

    parent_->setPiecePressed(piece);

    for(auto && movement : piece->movements)
        if (movement == this->coordinates_){
            nextPos_ = true;
            if (!occupied_)
                this->setStyleSheet(HIGHLIGHT);
        }
}

void Box::revertColor(){
    color_ ? setColorWhite() : setColorBlack();
}

void Box::handleClick()
{
    auto mf = parent_->getBoxPressed();
    if (mf == nullptr)
        return;
    else if (mf == this)
        if (mf->nextPos_)
            emit goTo();

    revertColor();
    nextPos_ = false;
}
