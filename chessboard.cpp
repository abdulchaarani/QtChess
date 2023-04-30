#include "chessboard.hpp"
#include <QDebug>
#include <QPropertyAnimation>
#include <QMessageBox>
#include "king.hpp"
#include "knight.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include "pawn.hpp"

#include "layouts.hpp"

using namespace layouts;

ChessBoard::ChessBoard(QWidget* parent) : QWidget(parent), parent_(parent)
{

    // creates a 8x8 grid of boxes and connects correct signals
    lay_ = new QVBoxLayout(this);
    grid_ = new QGridLayout();

    label_ = new QLabel("White's turn");
    label_->setFixedHeight(labelSize);
    label_->setStyleSheet(whiteTurnFont);
    label_->setAlignment(Qt::AlignCenter);

    lay_->addWidget(label_);
    lay_->addLayout(grid_);

    //lay_ = new QVBoxLayout(this);
    for (int row = 0; row < 8; ++row) {
        for (int column = 0; column < 8; ++column) {
            Box* box = new Box(row, column, this); // !!
            box->setFixedSize(boxSize, boxSize);
            grid_->addWidget(box, row, column);
            connect(box, SIGNAL(released()), this, SLOT(onButtonTrigger()));
            connect(this, SIGNAL(buttonTriggered()), box, SLOT(handleClick()));
        }
    }    
}

template <typename T>
void ChessBoard::addPiece(Color color, int row, int column)
{
    T* piece = new T(color, row, column, this, parent_);
    piece->fillMovements();
    piece->show();
    // connect king to every box to detect valid positions
    for (int i{0}; i < grid_->rowCount(); ++i) {
        for (int j{0}; j < grid_->columnCount(); ++j) {
            QWidget* widget =  grid_->itemAtPosition(i, j)->widget();
            connect(piece, SIGNAL(released()), widget, SLOT(onPieceClick()));
            connect(widget, SIGNAL(goTo()), piece, SLOT(updatePosition()));
        }
    }
}



 // to alternate playes every move
void ChessBoard::changePlayer()
{
    if (currentPlayer == Color::WHITE) {
        currentPlayer = Color::BLACK;
        if (isGameStarted){
            label_->setStyleSheet(blackTurnFont);
            label_->setText("Black's Turn");
        }
    } else {
        currentPlayer = Color::WHITE;
            if (isGameStarted){
            label_->setStyleSheet(whiteTurnFont);
            label_->setText("White's Turn");
        }
    }
}

bool ChessBoard::isCheck(Color color)
{
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

void ChessBoard::verifyCheck()
{
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

std::list<Piece*> ChessBoard::getAttackingPieces(Color color, Point position)
{
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


bool ChessBoard::isValidMove(Point position)
{

    Point oldPosition = piecePressed_->getCoordinates();
    Piece* potentialVictim{nullptr};

    int newRow = position.getRow();
    int newColumn = position.getColumn();


    // validate if enemy's death would cause a self-check
    if (board_[newRow][newColumn] != nullptr){
        potentialVictim = board_[newRow][newColumn];
    }

    // move clicked piece into future position to validate if king is checked
    board_[oldPosition.getRow()][oldPosition.getColumn()] = nullptr;
    piecePressed_->getCoordinates().setRow(newRow);
    piecePressed_->getCoordinates().setColumn(newColumn);
    board_[newRow][newColumn] = piecePressed_;

    emit updateMovements();

    if (potentialVictim != nullptr)
        potentialVictim->movements.clear();

    bool isValid = !isCheck(piecePressed_->color_);

    // replace all the moved pieces back to original positions
    piecePressed_->getCoordinates().setRow(oldPosition.getRow());
    piecePressed_->getCoordinates().setColumn(oldPosition.getColumn());
    board_[oldPosition.getRow()][oldPosition.getColumn()] = piecePressed_;

    if (potentialVictim != nullptr){
        board_[newRow][newColumn] = potentialVictim;
        potentialVictim->getCoordinates().setRow(newRow);
        potentialVictim->getCoordinates().setColumn(newColumn);
    }
    else{
        board_[newRow][newColumn] = nullptr;
    }

    emit updateMovements();

    return isValid;
}

void ChessBoard::finishingBlow()
{
    emit buttonTriggered();
}

void ChessBoard::onButtonTrigger()
{
    QObject* senderObject = QObject::sender();
    if (senderObject == nullptr)
        return;
    boxPressed_ = qobject_cast<Box*>(senderObject);
    emit buttonTriggered();
}

void ChessBoard::validateMovements()
{
    emit updateMovements();
    verifyCheck();
    changePlayer();
}
// the "magic" numbers below represent the position will occupy the piece
// (row and column respectively)

void ChessBoard::startGame()
{
    addPiece<King>(Color::WHITE, 7, 4);
    addPiece<King>(Color::BLACK, 0, 4);

    addPiece<Knight>(Color::WHITE, 7, 1);
    addPiece<Knight>(Color::WHITE, 7, 6);
    addPiece<Knight>(Color::BLACK, 0, 1);
    addPiece<Knight>(Color::BLACK, 0, 6);

    addPiece<Rook>(Color::WHITE, 7, 0);
    addPiece<Rook>(Color::WHITE, 7, 7);
    addPiece<Rook>(Color::BLACK, 0, 0);
    addPiece<Rook>(Color::BLACK, 0, 7);

    addPiece<Bishop>(Color::WHITE, 7, 2);
    addPiece<Bishop>(Color::WHITE, 7, 5);
    addPiece<Bishop>(Color::BLACK, 0, 2);
    addPiece<Bishop>(Color::BLACK, 0, 5);

    addPiece<Queen>(Color::WHITE, 7, 3);
    addPiece<Queen>(Color::BLACK, 0, 3);

    for (int i{0}; i < 8; ++i){
        addPiece<Pawn>(Color::WHITE, 6, i);
        addPiece<Pawn>(Color::BLACK, 1, i);
    }

    isGameStarted = true;
    currentPlayer = Color::WHITE;

    emit gameStarted();
}


void ChessBoard::startEndGame1()
{
    addPiece<King>(Color::WHITE,3,3);
    addPiece<Queen>(Color::WHITE, 1,5);

    addPiece<King>(Color::BLACK,0,3);
    addPiece<Rook>(Color::BLACK, 2,1);

    isGameStarted = true;
    currentPlayer = Color::WHITE;

    emit gameStarted();
}


void ChessBoard::startEndGame2()
{
    addPiece<King>(Color::WHITE, 2, 2);
    addPiece<Queen>(Color::WHITE, 3, 0);

    addPiece<King>(Color::BLACK, 0, 1);
    addPiece<Rook>(Color::BLACK, 1, 1);
    isGameStarted = true;
    currentPlayer = Color::WHITE;

    emit gameStarted();
}


void ChessBoard::startEndGame3()
{
    addPiece<King>(Color::WHITE, 1 ,6);
    addPiece<Rook>(Color::WHITE, 1, 7);

    addPiece<King>(Color::BLACK, 3, 6);
    addPiece<Queen>(Color::BLACK, 0, 4);

    isGameStarted = true;
    currentPlayer = Color::WHITE;

    emit gameStarted();
}

void ChessBoard::startEndGame4()
{
    addPiece<King>(Color::WHITE, 7 ,0);
    addPiece<Queen>(Color::WHITE, 1, 5);

    addPiece<King>(Color::BLACK, 4, 1);
    addPiece<Bishop>(Color::BLACK, 5, 0);
    addPiece<Knight>(Color::BLACK, 5, 2);

    isGameStarted = true;
    currentPlayer = Color::WHITE;

    emit gameStarted();
}

void ChessBoard::startTestGame()
{
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

    isGameStarted = true;
    currentPlayer = Color::WHITE;

    emit gameStarted();
}
