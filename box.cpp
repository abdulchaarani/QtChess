
#include "box.hpp"
#include "chessboard.hpp"
#include "layouts.hpp"

using namespace layouts;

Box::Box(int row, int column, ChessBoard *parent) : QPushButton(parent), coordinates_(row, column)
{
    // to alternate black and white colors on the chessboard
    counter_ ? setColorBlack() : setColorWhite();
    if (coordinates_.getColumn() != 7)
        counter_ = !counter_;

    // save chessboard as an attribute
    chessboard_ = parent;
}

void Box::setColorWhite()
{
    this->setStyleSheet(whiteBoxFont);
    color_ = true;
}
void Box::setColorBlack()
{
    this->setStyleSheet(blackBoxFont);
    color_ = false;
}

void Box::onPieceClick()
{
    // reset clicked box
    chessboard_->setBoxPressed(nullptr);


    // which piece got clicked
    QObject* senderObject = QObject::sender();
    if (senderObject == nullptr)
        return;

    auto piece = qobject_cast<Piece*>(senderObject);

    // if not your turn no touchy! Also Check for kill
    if (piece->color_ != chessboard_->currentPlayer){
        Piece* killer{chessboard_->getLastPiecePressed()};
        // check if in killing position

        Point pieceCoordinates = piece->coordinates_;

        if (coordinates_ == pieceCoordinates)
            if (movableBox_ == true && chessboard_->isValidMove(piece->getCoordinates())){
                for(auto&& movement : killer->movements)
                    if (movement == piece->getCoordinates()){
                        killer->killPiece(piece);
                        movableBox_ = false;
                        chessboard_->finishingBlow();
                        return;
                    }
            }
        return;
    }

    // colors the boxes in the appropriate colors;
    handleClick();
    chessboard_->setPiecePressed(piece);
    highlightColor();

}

// If box is in the possible moveset of the clicked piece, highlight
void Box::highlightColor()
{
    Piece* piece = chessboard_->getLastPiecePressed();
    for(auto&& movement : piece->movements)
        if (movement == this->coordinates_){
            movableBox_ = true;
            if (chessboard_->board_[coordinates_.getRow()][coordinates_.getColumn()] != nullptr)
                setStyleSheet(highlightKillFont);
            else
                setStyleSheet(highlightMoveFont);
        }
}

void Box::revertColor()
{
    color_ ? setColorWhite() : setColorBlack();
}


void Box::handleClick()
{
    // if the next clicked box is not a highlighted one, cancel movement
    // else make the piece goto said box
    Piece* potentialVictim{chessboard_->board_[coordinates_.getRow()][coordinates_.getColumn()]};

    auto currentBox = chessboard_->getBoxPressed();
    if (currentBox == this)
        if (currentBox->movableBox_)
            if (chessboard_->isValidMove(coordinates_))
                if (potentialVictim != nullptr)
                    chessboard_->getLastPiecePressed()->killPiece(potentialVictim);
                else
                    emit goTo();

    revertColor();
    movableBox_ = false;
    currentBox = nullptr;
}
