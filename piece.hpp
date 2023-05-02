
#ifndef PIECE_H
#define PIECE_H


#include <QObject>
#include <QPushButton>
#include <QTimer>

#include <list>
#include <map>

#include "point.hpp"

class Box;
class ChessBoard;
enum class Color;

class Piece : public QPushButton
{
    Q_OBJECT

public:
    Piece(Color color, int column, int row, ChessBoard* board, QWidget *parent = nullptr);
    Piece() = default;
    virtual ~Piece() = default;

    void changePosition(int column, int row);

    // List of valid moves
    std::list<Point> movements;

    Point& getCoordinates();

    // function that fills list of valid moves
    virtual void fillMovements() = 0;

    Color color_;

    void killPiece(Piece* victim);

    void check();

    bool isChecked{false};

     QTimer blinkTimer_;

//protected:
    Point coordinates_;
    ChessBoard* chessboard_;

private:
    void revertCheck();


signals:
    // fires everytime a piece is moved
    void movedPiece();

    void playedFirstMove();

private slots:
    void updatePosition();

    // to call correct overloaded function (#operator<<)
    void fillAllMovements();

public slots:
    void toggleBlink();

};
#endif // PIECE_H
