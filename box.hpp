
#ifndef BOX_HPP
#define BOX_HPP

#include <QApplication>
#include <QPushButton>
#include "point.hpp"
#include "pieces.hpp"

class ChessBoard;

class Box : public QPushButton

{
    Q_OBJECT

public:
    Box(int row, int column, ChessBoard* parent = nullptr);
    ~Box() = default;
    bool nextPos_{false};

    Point& getCoordinates() { return coordinates_; }
    ChessBoard* getParent() { return parent_; }

    void occupyBox() { occupied_ = true; }
    void unoccupyBox() { occupied_ = false; }
    bool isOccupied() { return occupied_; }
private:
    Point coordinates_;

    int BOX_SIZE{150};

    inline static bool counter_{false};

    bool color_;

    bool occupied_{false};
    void setColorWhite();
    void setColorBlack();

    ChessBoard* parent_;

    void revertColor();

signals:
    void goTo();

public slots:
    void highlightColor();

    void handleClick();

};


#endif // BOX_HPP
