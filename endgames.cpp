
#include "endgames.hpp"
#include "layouts.hpp"

EndGamesScreen::EndGamesScreen(QWidget* parent) : QWidget(parent),
    verticalButtonLayout_{new QVBoxLayout(this)}

{
    endGameButton1_ = new QPushButton("Queen Versus Rook", this);
    endGameButton2_ = new QPushButton("Philidor Position", this);
    endGameButton3_ = new QPushButton("Gelfand vs. Svidler, 2001", this);
    endGameButton4_ = new QPushButton("Ponziani 1782", this);
    endGameButton5_ = new QPushButton("Test Game", this);

    endGameButton1_->setStyleSheet(layouts::menuButtonFont);
    endGameButton2_->setStyleSheet(layouts::menuButtonFont);
    endGameButton3_->setStyleSheet(layouts::menuButtonFont);
    endGameButton4_->setStyleSheet(layouts::menuButtonFont);
    endGameButton5_->setStyleSheet(layouts::menuButtonFont);

    verticalButtonLayout_->addWidget(endGameButton1_);
    verticalButtonLayout_->addWidget(endGameButton2_);
    verticalButtonLayout_->addWidget(endGameButton3_);
    verticalButtonLayout_->addWidget(endGameButton4_);
    verticalButtonLayout_->addWidget(endGameButton5_);
}

