#include "chessboard.hpp"

using namespace layouts;

Chessboard::Chessboard(QWidget* parent) : QWidget(parent), parent_(parent)
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
            Box* box = new Box(row, column, this);
            boardBoxes_[row][column] = box;
            box->setFixedSize(boxSize, boxSize);
            grid_->addWidget(box, row, column);

            connect(box, SIGNAL(clicked()), this, SLOT(onBoxClicked()));
        }
    }
    connect(&blinkTimer_, &QTimer::timeout, this, &Chessboard::toggleBlink);

}

void Chessboard::onBoxClicked()
{
    QObject* senderObject = QObject::sender();
    if (senderObject == nullptr)
        return;

    auto box = qobject_cast<Box*>(senderObject);

    emit sendClick(box->coordinates_);
}

void Chessboard::setPieceColor(Coordinates coordinates, Color color)
{
    auto [row, column] = coordinates;
    boardBoxes_[row][column]->heldColor_ = color;
}
void Chessboard::setBoxText(Coordinates coordinates, QString text)
{
    auto [row, column] = coordinates;
    boardBoxes_[row][column]->setDisplay(text);
}

void Chessboard::processHighlight(Coordinates coordinates, Highlight highlight)
{
    auto [row, column] = coordinates;
    Box* box = boardBoxes_[row][column];
    switch (highlight){
    case Highlight::move :
        box->highlightMove();
        break;
    case Highlight::kill :
        box->highlightKill();
        break;
    case Highlight::revert :
        box->highlightOff();
        break;
    }
}

void Chessboard::moveViewPiece(Coordinates oldCoordinates, Coordinates newCoordinates)
{
    auto [oldRow, oldColumn] = oldCoordinates;
    auto [newRow, newColumn] = newCoordinates;

    boardBoxes_[oldRow][oldColumn]->purgeBox();
    boardBoxes_[newRow][newColumn]->occupyBox();
}

void Chessboard::toggleTurnLabel(Color nextTurn)
{
    if (nextTurn == Color::white) {
        label_->setStyleSheet(whiteTurnFont);
        label_->setText("White's Turn");

    } else {
        label_->setStyleSheet(blackTurnFont);
        label_->setText("Black's Turn");
    }
}

void Chessboard::startTimer(Coordinates coordinates, int time)
{
    blinkingPiece = boardBoxes_[coordinates.first][coordinates.second];
    if (blinkingPiece->boxColor_ == Color::white){
        originalFont = &whiteBoxFont;
        checkedFont = &whiteCheckedFont;
    }
    else{
        originalFont = &blackBoxFont;
        checkedFont = &blackCheckedFont;
    }
    blinkTimer_.start(time);
}
void Chessboard::toggleBlink()
{

    static int counter{0};

    if (counter % 2 == 0) {
        blinkingPiece->setStyleSheet(*checkedFont);
    } else {
        blinkingPiece->setStyleSheet(*originalFont);
    }
    if (counter == 5){
        counter = 0;
        blinkTimer_.stop();
        blinkingPiece->setStyleSheet(*originalFont);
    }
    ++counter;
}

void Chessboard::rotateKing(Coordinates kingPosition)
{

    blinkTimer_.stop();
    auto [row, column] = kingPosition;

    auto deadKing = boardBoxes_[row][column];

    if(deadKing->boxColor_ == Color::white)
        deadKing->setStyleSheet(whiteLostFont);
    else
        deadKing->setStyleSheet(blackLostFont);
}

void Chessboard::displayWinner(Color winner)
{
    if (winner == Color::white) {
        label_->setStyleSheet(whiteTurnFont);
        label_->setText("White wins!");

    } else {
        label_->setStyleSheet(blackTurnFont);
        label_->setText("Black wins!");
    }
}
