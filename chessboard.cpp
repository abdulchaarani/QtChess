
#include "chessboard.hpp"
#include <QDebug>
#include <QPropertyAnimation>
#include <QVBoxLayout>
#include "bishop.hpp"
#include "king.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "piece.hpp"
#include "queen.hpp"
#include "rook.hpp"

ChessBoard* ChessBoard::instance = nullptr;
QWidget* ChessBoard::parentWindow_ = nullptr;


ChessBoard::ChessBoard(QWidget* parent) : QWidget(parent), parent_(parent)
{

    // creates a 8x8 grid of boxes and connects correct signals
    //test_ = new QVBoxLayout(parent);
    grid_ = new QGridLayout(parent);

    //test_->addLayout(grid_);

    for (int row = 0; row < 8; ++row) {
        for (int column = 0; column < 8; ++column) {
            Box* box = new Box(row, column, this); // !!
            grid_->addWidget(box, row, column);
            connect(box, SIGNAL(released()), this, SLOT(onButtonTrigger()));
            connect(this, SIGNAL(buttonTriggered()), box, SLOT(handleClick()));
        }
    }

    testGame();
}

 // to alternate playes every move
void ChessBoard::changePlayer(){
    if (currentPlayer == Color::WHITE) {
        currentPlayer = Color::BLACK;
        if (isGameStarted)
            qDebug() << "BLACK";
    } else {
        currentPlayer = Color::WHITE;
        if (isGameStarted)
            qDebug() << "WHITE";
    }
}

void ChessBoard::startGame(){

    qDebug() << "no.";

    emit gameStarted();

    // TODO : make pieces appear fr fr

    addPiece<King>(Color::WHITE,0,3);
    addPiece<King>(Color::BLACK,7,5);

    addPiece<Knight>(Color::WHITE, 5, 3);
    addPiece<Knight>(Color::BLACK, 3, 5);

    addPiece<Pawn>(Color::WHITE, 6,2);
    addPiece<Pawn>(Color::BLACK, 1,1);

    addPiece<Rook>(Color::BLACK, 6,7);
    addPiece<Rook>(Color::WHITE, 0,0);

    addPiece<Bishop>(Color::BLACK, 3,4);
    addPiece<Bishop>(Color::WHITE, 2,5);

    addPiece<Queen>(Color::WHITE, 2,2);
    addPiece<Queen>(Color::BLACK, 1,6);

    isGameStarted = true;
    currentPlayer = Color::WHITE;

}

bool ChessBoard::isCheck(Color color){
    Piece* king;

    color == Color::WHITE ? king = whiteKing : king = blackKing;

    for (int i{0}; i < 8; ++i)
        for (int j{0}; j < 8; ++j)
            if (board_[i][j] != nullptr)
                if (board_[i][j]->color_ != color)
                    for (auto&& move : board_[i][j]->movements)
                        if (move == king->getCoordinates()){
                            qDebug() << "YOU CANT PUT YOURSELF INTO CHECK ";
                            king->blinkTimer_.start(150);
                            return true;
                        }

    return false;
}

void ChessBoard::verifyCheck(){
    // which piece got clicked
    QObject* senderObject = QObject::sender();
    if (senderObject == nullptr)
        return;

    auto piece = qobject_cast<Piece*>(senderObject);

    Piece* king;

    piece->color_ == Color::WHITE ? king = blackKing : king = whiteKing;
    if (isGameStarted)
        for (auto&& move : piece->movements){
            if (move == king->getCoordinates()){
                king->check();
                king->blinkTimer_.start(500);
                qDebug() << "CHECK";
            }
        }
}

std::list<Piece*> ChessBoard::getAttackingPieces(Color color, Point position){

    std::list<Piece*> attackingPieces;

    for (int i{0}; i < 8; ++i)
        for (int j{0}; j < 8; ++j)
            if (board_[i][j] != nullptr)
                if (board_[i][j]->color_ != color)
                    for (auto&& move : board_[i][j]->movements)
                        if (move == position)
                            attackingPieces.push_back(board_[i][j]);

    return attackingPieces;

}


bool ChessBoard::isValidMove(Point position){

    Point oldPosition = piecePressed_->getCoordinates();

    board_[oldPosition.getRow()][oldPosition.getColumn()] = nullptr;

    piecePressed_->getCoordinates().setRow(position.getRow());
    piecePressed_->getCoordinates().setColumn(position.getColumn());
    board_[position.getRow()][position.getColumn()] = piecePressed_;

    emit updateMovements();

    bool isValid = !isCheck(piecePressed_->color_);

    piecePressed_->getCoordinates().setRow(oldPosition.getRow());
    piecePressed_->getCoordinates().setColumn(oldPosition.getColumn());

    board_[oldPosition.getRow()][oldPosition.getColumn()] = piecePressed_;
    board_[position.getRow()][position.getColumn()] = nullptr;

    emit updateMovements();

    return isValid;
}

void ChessBoard::testGame(){
    qDebug() << "WOWO;";
    addPiece<King>(Color::WHITE, 0, 3);
    addPiece<King>(Color::BLACK, 7, 5);

    addPiece<Knight>(Color::WHITE, 5, 3);
    addPiece<Knight>(Color::BLACK, 3, 5);

    addPiece<Pawn>(Color::WHITE, 6, 2);
    addPiece<Pawn>(Color::BLACK, 1, 1);

    addPiece<Rook>(Color::BLACK, 6, 7);
    addPiece<Rook>(Color::WHITE, 0, 0);

    addPiece<Bishop>(Color::BLACK, 3, 4);
    addPiece<Bishop>(Color::WHITE, 2, 5);

    addPiece<Queen>(Color::WHITE, 2, 2);
    addPiece<Queen>(Color::BLACK, 1, 6);
    //parent_->show();
    startGame();
}
