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
    if (currentPlayer == Color::white) {
        currentPlayer = Color::black;
        if (isGameStarted){
            label_->setStyleSheet(blackTurnFont);
            label_->setText("Black's Turn");
        }
    } else {
        currentPlayer = Color::white;
            if (isGameStarted){
            label_->setStyleSheet(whiteTurnFont);
            label_->setText("White's Turn");
        }
    }
}

bool ChessBoard::isCheck(Color color)
{
    Piece* king;

    color == Color::white ? king = whiteKing : king = blackKing;

    for (int i{0}; i < 8; ++i)
        for (int j{0}; j < 8; ++j)
            if (board_[i][j] != nullptr)
                if (board_[i][j]->color_ != color)
                    for (Point& move : board_[i][j]->movements)
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

    piece->color_ == Color::white ? king = blackKing : king = whiteKing;
    if (isGameStarted)
        for (Point& move : piece->movements){
            if (move == king->getCoordinates()){
                king->check();
                king->blinkTimer_.start(500);
                qDebug() << "CHECK";
                return;
            }
        }
}

void ChessBoard::verifyCheckmate(Color color){

    for (int i{0}; i < 8; ++i)
        for (int j{0}; j < 8; ++j)
            if (board_[i][j] != nullptr)
                if (board_[i][j]->color_ == color){
                    std::list<Point> pieceMovements{board_[i][j]->movements};
                    for (Point& move : pieceMovements){
                        piecePressed_ = board_[i][j];
                        if (isValidMove(move))
                            return;
                    }
                }
    qDebug() << "CHECKMATE";
    gameOver();
    return;
}

void ChessBoard::gameOver(){
    isGameStarted = false;
    for (int i{0}; i < 8; ++i)
        for (int j{0}; j < 8; ++j)
            if (board_[i][j] != nullptr)
                board_[i][j]->movements.clear();
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

bool ChessBoard::isValidPosition(Point position, Piece* piece)
{

    Point oldPosition = piece->getCoordinates();
    Piece* potentialVictim{nullptr};

    int newRow = position.getRow();
    int newColumn = position.getColumn();


    // validate if enemy's death would cause a self-check
    if (board_[newRow][newColumn] != nullptr){
        potentialVictim = board_[newRow][newColumn];
    }

    // move clicked piece into future position to validate if king is checked
    board_[oldPosition.getRow()][oldPosition.getColumn()] = nullptr;
    piece->getCoordinates().setRow(newRow);
    piece->getCoordinates().setColumn(newColumn);
    board_[newRow][newColumn] = piece;

    emit updateMovements();

    if (potentialVictim != nullptr)
        potentialVictim->movements.clear();

    bool isValid = !isCheck(piece->color_);

    // replace all the moved pieces back to original positions
    piece->getCoordinates().setRow(oldPosition.getRow());
    piece->getCoordinates().setColumn(oldPosition.getColumn());
    board_[oldPosition.getRow()][oldPosition.getColumn()] = piece;

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
    if (whiteKing->isChecked)
        verifyCheckmate(Color::white);
    changePlayer();

}
// position = row and column respectively

void ChessBoard::startGame()
{
    addPiece<King>(Color::white, 7, 4);
    addPiece<King>(Color::black, 0, 4);

    addPiece<Knight>(Color::white, 7, 1);
    addPiece<Knight>(Color::white, 7, 6);
    addPiece<Knight>(Color::black, 0, 1);
    addPiece<Knight>(Color::black, 0, 6);

    addPiece<Rook>(Color::white, 7, 0);
    addPiece<Rook>(Color::white, 7, 7);
    addPiece<Rook>(Color::black, 0, 0);
    addPiece<Rook>(Color::black, 0, 7);

    addPiece<Bishop>(Color::white, 7, 2);
    addPiece<Bishop>(Color::white, 7, 5);
    addPiece<Bishop>(Color::black, 0, 2);
    addPiece<Bishop>(Color::black, 0, 5);

    addPiece<Queen>(Color::white, 7, 3);
    addPiece<Queen>(Color::black, 0, 3);

    for (int i{0}; i < 8; ++i){
        addPiece<Pawn>(Color::white, 6, i);
        addPiece<Pawn>(Color::black, 1, i);
    }

    isGameStarted = true;
    currentPlayer = Color::white;

    emit gameStarted();
}

void ChessBoard::startQueenVRook()
{
    addPiece<King>(Color::white,3,3);
    addPiece<Queen>(Color::white, 1,5);

    addPiece<King>(Color::black,0,3);
    addPiece<Rook>(Color::black, 2,1);

    isGameStarted = true;
    currentPlayer = Color::white;

    emit gameStarted();
}


void ChessBoard::startPhilidor()
{
    addPiece<King>(Color::white, 2, 2);
    addPiece<Queen>(Color::white, 3, 0);

    addPiece<King>(Color::black, 0, 1);
    addPiece<Rook>(Color::black, 1, 1);
    isGameStarted = true;
    currentPlayer = Color::white;

    emit gameStarted();
}


void ChessBoard::startGelfandVSvidler()
{
    addPiece<King>(Color::white, 1 ,6);
    addPiece<Rook>(Color::white, 1, 7);

    addPiece<King>(Color::black, 3, 6);
    addPiece<Queen>(Color::black, 0, 4);

    isGameStarted = true;
    currentPlayer = Color::white;

    emit gameStarted();
}

void ChessBoard::startPonziani()
{
    addPiece<King>(Color::white, 7 ,0);
    addPiece<Queen>(Color::white, 1, 5);

    addPiece<King>(Color::black, 4, 1);
    addPiece<Bishop>(Color::black, 5, 0);
    addPiece<Knight>(Color::black, 5, 2);

    isGameStarted = true;
    currentPlayer = Color::white;

    emit gameStarted();
}

