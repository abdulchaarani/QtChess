
#include "chessboard.hpp"
#include <QDebug>
#include <QPropertyAnimation>

ChessBoard::ChessBoard(QWidget* parent) : QWidget(parent), parent_(parent)
{

    // creates a 8x8 grid of boxes and connects correct signals

    grid_ = new QGridLayout(this);

    for (int row = 0; row < 8; ++row) {
        for (int column = 0; column < 8; ++column) {
            Box* box = new Box(row, column, this); // !!
            box->setFixedSize(150, 150);
            grid_->addWidget(box, row, column);
            connect(box, SIGNAL(released()), this, SLOT(onButtonTrigger()));
            connect(this, SIGNAL(buttonTriggered()), box, SLOT(handleClick()));
        }
    }
}

 // to alternate playes every move
void ChessBoard::changePlayer(){
    if (currentPlayer == Color::WHITE) {
        currentPlayer = Color::BLACK;
        qDebug() << "BLACK";
    } else {
        currentPlayer = Color::WHITE;
        qDebug() << "WHITE";
    }
}

void ChessBoard::startGame(){
    gameStart = true;
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
                            qDebug() << "CHECK";
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
    if (gameStart)
        for (auto&& move : piece->movements){
            if (move == king->getCoordinates()){
                king->check();
                qDebug() << "CHECK KING";
                isInCheckmate(king->color_);
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

bool ChessBoard::isInCheckmate(Color color) {
    // Get the current position of the king of the given color
    Piece* king{};
    color == Color::WHITE ? king = whiteKing : king = blackKing;

    Point kingPos = king->getCoordinates();

    // Get the list of attacking pieces
    std::list<Piece*> attackers = getAttackingPieces(color, kingPos);

    // Check if any attacking piece can be captured or blocked
    for (Piece* attacker : attackers) {
        std::list<Point> attackerMoves = attacker->movements;
        for (Point& move : attackerMoves) {
            // Temporarily move the king to the new position and check if it's still in check
            bool isKingSafe = moveKing(king, move);
            if (isKingSafe) {
                // The king is no longer in checkmate
                //undoLastMove();
                qDebug() << "NO CHECKMATE!";
                return false;
            }
            //undoLastMove();
        }
    }

    // The king is in checkmate
    qDebug() << "CHECKMATE!";
    return true;
}


bool ChessBoard::moveKing(Piece* king, const Point& newPosition) {
    // Remember the original position of the king
    Point oldPosition = king->getCoordinates();

    // Temporarily move the king to the new position
    king->getCoordinates().setRow(newPosition.getRow());
    king->getCoordinates().setColumn(newPosition.getColumn());
    // Check if the king is still in check
    bool inCheck = isCheck(king->color_);

    // Move the king back to the original position
    king->getCoordinates().setRow(oldPosition.getRow());
    king->getCoordinates().setColumn(oldPosition.getColumn());

    return !inCheck;
}


bool ChessBoard::isValidMove(Point position){

    Point oldPosition = piecePressed_->getCoordinates();

    board_[oldPosition.getRow()][oldPosition.getColumn()] = nullptr;

    piecePressed_->getCoordinates().setRow(position.getRow());
    piecePressed_->getCoordinates().setColumn(position.getColumn());
    board_[position.getRow()][position.getColumn()] = piecePressed_;

    emit updateMovements();

    bool result = isCheck(piecePressed_->color_);

    piecePressed_->getCoordinates().setRow(oldPosition.getRow());
    piecePressed_->getCoordinates().setColumn(oldPosition.getColumn());

    board_[oldPosition.getRow()][oldPosition.getColumn()] = piecePressed_;
    board_[position.getRow()][position.getColumn()] = nullptr;

    emit updateMovements();

    return !result;

}


void ChessBoard::blinkKing(Piece* king)
{

}
