
#ifndef BOX_HPP
#define BOX_HPP

#include <QPushButton>
#include "layouts.hpp"

namespace view{

class Box : public QPushButton
{
    using Coordinates = std::pair<int, int>;
    Q_OBJECT

public:
    Box(int row, int column,QWidget* parent);
    Coordinates coordinates_;
    Color boxColor_;
    QString heldPiece_;
    Color heldColor_;

    void setDisplay(const QString& display);

    void highlightMove();
    void highlightKill();
    void highlightOff();

    void purgeBox();
    void occupyBox();

private:
    QWidget* parent_;

    inline static bool alternator_{false};

    void setColorWhite();
    void setColorBlack();

    static Color tempHeldColor_;
    static QString tempHeldPiece_;


};
}
#endif // BOX_HPP
