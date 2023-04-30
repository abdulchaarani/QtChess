
#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

// this class acts as the controller-ish model to keep track of the events
// and positions of stuff on the board

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <list>
#include <array>

#include <QDebug>

#include "box.hpp"
#include "piece.hpp"

enum class Color{
    WHITE,
    BLACK,
};


class ChessBoard : public QWidget
{
    Q_OBJECT

public:
    ChessBoard(QWidget* parent = nullptr);
    QGridLayout* grid_;
    QVBoxLayout* lay_;
    QLabel* label_;
    // keeps track of ALL the pieces on the board
    std::array<std::array<Piece*, 8>, 8> board_{}; // TODO overload[]

    friend class MainMenu;

    // to add a piece to the board and to connect the right signals
    template <typename T>
    void addPiece(Color color, int row, int column);
    // TODO CHANGE NAMES
    // Getters : to keep track of current pressed piece and box
    Box* getBoxPressed() { return boxPressed_; }
    void setBoxPressed(Box* box) { boxPressed_ = box; }
    Piece* getLastPiecePressed() { return piecePressed_; }
    void setPiecePressed(Piece* piece) { piecePressed_ = piece; }

    Color currentPlayer;

    void finishingBlow();

    void setWhiteKing(Piece* king) {whiteKing = king;}
    void setBlackKing(Piece* king) {blackKing = king;}

    bool isInCheckmate(Color color);

    bool moveKing(Piece* king, const Point& newPosition);

    bool isValidMove(Point position);
private:

    // Getters : to keep track of current pressed piece and box

    Box* boxPressed_;
    Piece* piecePressed_;
    Piece* pieceToDelete_;
    // necessary or program crashes lol
    QWidget* parent_;

    //to alternate playes every move
    void changePlayer();
    void verifyCheck();
    bool isCheck(Color color);

    Piece* whiteKing{};
    Piece* blackKing{};

    std::list<Piece*> getAttackingPieces(Color color, Point position);

    bool isGameStarted{false};

signals:
    void buttonTriggered();
    void updateMovements();
    void gameStarted();

private slots:

    // acts as the controller of who pressed what
    void onButtonTrigger();
    // at everymove, signal the pieces to recalculate their next possible move
    // and change player
    void validateMovements();

    void startGame();
    void startEndGame1();
    void startEndGame2();
    void startEndGame3();
    void startEndGame4();
    void startTestGame();
};



#endif
