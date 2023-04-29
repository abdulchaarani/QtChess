
#include "box.hpp"
#include "chessboard.hpp"

// Stylesheets for the box colors

// NAMESPACE :D :D

const QString WHITE_BOX = "QPushButton{"
                     "  background-color: rgb(238, 238, 212);"
                     "  border-style: inset;"
                     "  }"
                     "QPushButton:pressed {"
                     "   border-style: inset;"
                     "}";

const QString BLACK_BOX = "QPushButton{"
                     "  background-color: rgb(126, 148, 90);"
                     "  border-style: inset;"
                     "  }"
                     "QPushButton:pressed {"
                     "   border-style: inset;"
                     "}";

const QString HIGHLIGHT_KILL = "QPushButton{"
                     "  background-color: #F90F33;"
                     "  border-style: solid;"
                     "  border-width: 2px;"
                     "  border-color: white;"
                     "  }"
                     "QPushButton:pressed {"
                     "   border-style: inset;"
                     "}";

const QString HIGHLIGHT_MOVE = "QPushButton{"
                              "  background-color: #0B76D4;"
                              "  border-style: solid;"
                              "  border-width: 2px;"
                              "  border-color: white;"
                              "  }"
                              "QPushButton:pressed {"
                              "   border-style: inset;"
                              "}";

Box::Box(int row, int column, ChessBoard *parent) : QPushButton(parent), coordinates_(row, column)
{
    // to alternate black and white colors on the chessboard
    counter_ ? setColorBlack() : setColorWhite();
    if (coordinates_.getColumn() != 7)
        counter_ = !counter_;

    // save chessboard as an attribute
    chessboard_ = parent;
}

void Box::setColorWhite(){

    this->setStyleSheet(WHITE_BOX);
    color_ = true;
}
void Box::setColorBlack(){


    this->setStyleSheet(BLACK_BOX);
    color_ = false;
}

void Box::onPieceClick(){ // refactor maybe?

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
        if (movableBox_ == true && chessboard_->isValidMove(piece->getCoordinates()))
            for(auto&& movement : killer->movements)
                if (movement == piece->getCoordinates()){
                    killer->killPiece(piece);
                    movableBox_ = false;
                    chessboard_->finishingBlow();
                    return;
                }
        return;
    }

    // colors the boxes in the appropriate colors;
    handleClick();
    chessboard_->setPiecePressed(piece);
    highlightColor();

}

// If box is in the possible moveset of the clicked piece, highlight
void Box::highlightColor(){

    Piece* piece = chessboard_->getLastPiecePressed();
    for(auto&& movement : piece->movements)
        if (movement == this->coordinates_){
            movableBox_ = true;
            if (chessboard_->board_[coordinates_.getRow()][coordinates_.getColumn()] != nullptr)
                setStyleSheet(HIGHLIGHT_KILL);
            else
                setStyleSheet(HIGHLIGHT_MOVE);
        }
}

void Box::revertColor(){
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
                else{
                    emit goTo();
                }

    revertColor();
    movableBox_ = false;
    currentBox = nullptr;
}
