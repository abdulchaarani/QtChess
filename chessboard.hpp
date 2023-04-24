
#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

// this class acts as the controller-ish model to keep track of the events
// and positions of stuff on the board

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <list>
#include <array>

#include <QDebug>

#include "box.hpp"
#include "piece.hpp"
#include "king.hpp"
#include "knight.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include "pawn.hpp"

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

    // keeps track of ALL the pieces on the board
    std::array<std::array<Piece*, 8>, 8> board_{}; // TODO overload[]

    friend class MainMenu;

    // to add a piece to the board and to connect the right signals
    template <typename T>
    void addPiece(Color color, int row, int column){
        T* piece = new T(color, row, column, this, parent_);
        piece->fillMovements();

        // connect king to every box to detect valid positions
        for (int i{0}; i < grid_->rowCount(); ++i) {
            for (int j{0}; j <  grid_->columnCount(); ++j) {
                QWidget* widget =  grid_->itemAtPosition(i, j)->widget();
                connect(piece, SIGNAL(released()), widget, SLOT(onPieceClick()));
                connect(widget, SIGNAL(goTo()), piece, SLOT(updatePosition()));
            }
        }
    }

    // TODO CHANGE NAMES
    // Getters : to keep track of current pressed piece and box
    Box* getBoxPressed() { return boxPressed_; }
    void setBoxPressed(Box* box) { boxPressed_ = box; }
    Piece* getLastPiecePressed() { return piecePressed_; }
    void setPiecePressed(Piece* piece) { piecePressed_ = piece; }

    Color currentPlayer;



    void finishingBlow(){
        //getBoxPressed()->movableBox_ = false;
        emit buttonTriggered();
    }

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
    void onButtonTrigger()
    {
        QObject* senderObject = QObject::sender();
        if (senderObject == nullptr)
            return;
        boxPressed_ = qobject_cast<Box*>(senderObject);
        emit buttonTriggered();
    }

    // at everymove, signal the pieces to recalculate their next possible move
    // and change player
    void validateMovements(){
        emit updateMovements();
        verifyCheck();
        changePlayer();
    }

    void startGame();
};



#endif
