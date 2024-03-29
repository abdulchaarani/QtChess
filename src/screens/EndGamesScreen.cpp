/**
* Program that defines the EndGamesScreen class (UI configurations).
* Part of the View
* \file   EndGamesScreen.cpp
* \author Abdul-Wahab Chaarani 1793305 and Hiba Chaarani 2205674
* \date   5/05/2023
* Created on 9/04/2023
*/

#include "EndGamesScreen.hpp"
#include "layouts.hpp"

namespace view{

EndGamesScreen::EndGamesScreen(QWidget* parent) : QWidget(parent),
    verticalButtonLayout_{new QVBoxLayout(this)}

{
    queenRookButton_ = new QPushButton("Queen Versus Rook", this);
    philidorButton_  = new QPushButton("Philidor Position", this);
    gelfandButton_   = new QPushButton("Gelfand vs. Svidler, 2001", this);
    ponzianiButton_  = new QPushButton("Ponziani 1782", this);
    endGameButton5_  = new QPushButton("Test Game", this);

    queenRookButton_->setStyleSheet(layouts::menuButtonFont);
    philidorButton_ ->setStyleSheet(layouts::menuButtonFont);
    gelfandButton_  ->setStyleSheet(layouts::menuButtonFont);
    ponzianiButton_ ->setStyleSheet(layouts::menuButtonFont);
    endGameButton5_ ->setStyleSheet(layouts::menuButtonFont);

    verticalButtonLayout_->addWidget(queenRookButton_);
    verticalButtonLayout_->addWidget(philidorButton_);
    verticalButtonLayout_->addWidget(gelfandButton_);
    verticalButtonLayout_->addWidget(ponzianiButton_);
    verticalButtonLayout_->addWidget(endGameButton5_);
}

}
