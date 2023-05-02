
#include "endgames.hpp"
#include "layouts.hpp"

EndGamesScreen::EndGamesScreen(QWidget* parent) : QWidget(parent),
    verticalButtonLayout_{new QVBoxLayout(this)}

{
    queenRookButton_ = new QPushButton("Queen Versus Rook", this);
    philidorButton_  = new QPushButton("Philidor Position", this);
    gelfandButton_   = new QPushButton("Gelfand vs. Svidler, 2001", this);
    ponzianiButton_  = new QPushButton("Ponziani 1782", this);

    queenRookButton_->setStyleSheet(layouts::menuButtonFont);
    philidorButton_->setStyleSheet(layouts::menuButtonFont);
    gelfandButton_->setStyleSheet(layouts::menuButtonFont);
    ponzianiButton_->setStyleSheet(layouts::menuButtonFont);

    verticalButtonLayout_->addWidget(queenRookButton_);
    verticalButtonLayout_->addWidget(philidorButton_);
    verticalButtonLayout_->addWidget(gelfandButton_);
    verticalButtonLayout_->addWidget(ponzianiButton_);
}

