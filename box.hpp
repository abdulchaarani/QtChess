
#ifndef BOX_HPP
#define BOX_HPP

// The chessboard is made of an 8x8 grid of boxes (this class)
// the boxes are pushbuttons (which makes it easier to track when they are clicked
// they have individual coordinates
// Every box is interconnected, when one box is clicked, all of them react
// They boxes themselves decide if they are to be highlighted or not
// When a highlighted box is clicked, the piece copies the clicked boxes' coordinates

#include <QApplication>
#include <QPushButton>
#include "point.hpp"
#include "piece.hpp"

class ChessBoard;

class Box : public QPushButton

{
    Q_OBJECT

public:
    Box(int row, int column, ChessBoard* parent = nullptr);
    ~Box() = default;

     // when a piece is clicked, the correct highlighted boxes are "movable"
    bool movableBox_{false};

    // Old getters, might not be useful later
    Point& getCoordinates() { return coordinates_; }
    ChessBoard* getParent() { return chessboard_; }

private:
    Point coordinates_;

    int BOX_SIZE{150};

    // to help alternate colors when generating chessboard
    inline static bool counter_{false};

    // true for white, false for black
    bool color_; //TODO !!! might change since enum color exists

    void setColorWhite();
    void setColorBlack();

    ChessBoard* chessboard_;

    void highlightColor();
    // when you click outside of the highlighted are
    void revertColor();

signals:
    // piece goes to clicked box (if move is valid)
    void goTo();

public slots:
    // when any piece is clicked
    void onPieceClick();

    // when one box is clicked, all boxes recieve this signal and react accordingly
    void handleClick();

};


#endif // BOX_HPP
