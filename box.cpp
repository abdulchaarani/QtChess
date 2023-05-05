
#include "box.hpp"

using namespace layouts;

namespace view{

QString Box::tempHeldPiece_{};
Color Box::tempHeldColor_{};

Box::Box(int row, int column, QWidget* parent) : parent_{parent}
{
    coordinates_ = {row, column};
    alternator_ ? setColorBlack() : setColorWhite();
    if (column != 7)
        alternator_ = !alternator_;
    setFont(pieceFont);
}

void Box::setColorWhite()
{
    setStyleSheet(whiteBoxFont);
    boxColor_ = Color::white;
}
void Box::setColorBlack()
{
    setStyleSheet(blackBoxFont);
    boxColor_ = Color::black;
}

void Box::setDisplay(const QString& display)
{
    heldPiece_ = display;
    setText(display);
}

void Box::highlightMove()
{
    setStyleSheet(highlightMoveFont);
}

void Box::highlightKill()
{
    setStyleSheet(highlightKillFont);
}

void Box::highlightOff()
{
    if (boxColor_ == Color::white)
        setColorWhite();
    else
        setColorBlack();
}

void Box::purgeBox()
{
    Box::tempHeldPiece_ = heldPiece_;
    Box::tempHeldColor_ = heldColor_;

    heldPiece_ = "";
    setDisplay(heldPiece_);
}

void Box::occupyBox()
{
    setDisplay(Box::tempHeldPiece_);
    heldColor_ = Box::tempHeldColor_;
}

}
