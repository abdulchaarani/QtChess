
#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP


#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <list>
#include <array>

#include <QDebug>

#include "box.hpp"

class ChessBoard : public QWidget
{
    Q_OBJECT

public:
    ChessBoard(QWidget* parent = nullptr);
    QGridLayout* grid_;

    std::array<std::array<Piece*, 8>, 8> board_{}; // TODO overload[]

    template <typename T>
    void addPiece(int row, int column){
        T* piece = new T(row, column, this, parent_);
        piece->fillMovements();

        // connect king to every box to detect valid positions
        for (int i{0}; i < grid_->rowCount(); ++i) {
            for (int j{0}; j <  grid_->columnCount(); ++j) {
                QWidget* widget =  grid_->itemAtPosition(i, j)->widget();
                if (i == row && j == column)
                    piece->possessBox(qobject_cast<Box*>(widget));
                connect(piece, SIGNAL(released()), widget, SLOT(highlightColor()));
                connect(widget, SIGNAL(goTo()), piece, SLOT(updatePosition()));
            }
        }
    }

    Box* getBoxPressed() { return boxPressed_; }
    Piece* getPiecePressed() { return piecePressed_; }
    void setPiecePressed(Piece* piece) { piecePressed_ = piece; }

    enum Player{
        WHITE,
        BLACK,
    };

    Player currentPlayer;

    void startGame();
private:
    Box* boxPressed_;
    Piece* piecePressed_;

    std::list<Box*> occupiedWhiteBoxes;

    QWidget* parent_;

    void changePlayer();


signals:
    void buttonTriggered();
    void updateMovements();

private slots:
    void onButtonTrigger()
    {
        QObject* senderObject = QObject::sender();
        if (senderObject == nullptr)
            return;
        boxPressed_ = qobject_cast<Box*>(senderObject);
        emit buttonTriggered();
    }

    void validateMovements(){
        changePlayer();
        emit updateMovements();
    }
};



#endif
