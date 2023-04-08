
#include "box.hpp"

Box::Box(int x, int y, QWidget *parent) : QPushButton(parent), x_{x}, y_{y}
{
    //this->setGeometry(x_ * BOX_SIZE + X_OFFSET, y_ * BOX_SIZE + Y_OFFSET, BOX_SIZE, BOX_SIZE);

    // to alternate black and white colors on the chessboard
    counter_ ? setColorBlack() : setColorWhite();
    if (this->x_ != 7)
        counter_ = !counter_;
}


void Box::setColorWhite(){
    QString styleSheet = "QPushButton{"
                         "  background-color: rgb(238, 238, 212);"
                         "  border-style: inset;"
                         "  }"
                         "QPushButton:pressed {"
                         "   border-style: inset;"
                         "}";
    this->setStyleSheet(styleSheet);
}
void Box::setColorBlack(){
    QString styleSheet = "QPushButton{"
                         "  background-color: rgb(126, 148, 90);"
                         "  border-style: inset;"
                         "  }"
                         "QPushButton:pressed {"
                         "   border-style: inset;"
                         "}";
        this->setStyleSheet(styleSheet);
}
