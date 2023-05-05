/**
* Program that defines the UI configuration and methods of the TitleScreen class.
* \file   titlescreen.cpp
* \author Abdul-Wahab et Hiba
* \date   4 mai 2023
* Créé le 9 avril 2023
*/

#include "titlescreen.hpp"
#include "layouts.hpp"

namespace view{

TitleScreen::TitleScreen(QWidget* parent)
    : QWidget(parent),
    titleScreenLayout_(new QVBoxLayout),
    title_(new QLabel),
    buttonLayout_(new QGridLayout)
{
    // Title screen buttons
    newGameButton_  = new QPushButton("Start",   this);
    creditsButton_  = new QPushButton("Credits", this);
    exitGameButton_ = new QPushButton("Exit",    this);
    endGameButton_  = new QPushButton("Practice end games", this);
    
    newGameButton_ -> setStyleSheet (layouts::menuButtonFont);
    creditsButton_ -> setStyleSheet (layouts::menuButtonFont);
    exitGameButton_-> setStyleSheet (layouts::menuButtonFont);
    endGameButton_ -> setStyleSheet (layouts::menuButtonFont);

    newGameButton_ -> setFixedWidth(200);
    endGameButton_ -> setFixedWidth(200);
    creditsButton_ -> setFixedWidth(200);
    exitGameButton_-> setFixedWidth(200);

    // Connect the exit button to the exit function. It closes the app
    connect(exitGameButton_, &QPushButton::clicked, this, &TitleScreen::exit);

    // Alignment of our buttons.
    buttonLayout_->   addWidget(newGameButton_, 0, 0);
    buttonLayout_->   addWidget(endGameButton_, 0, 1);
    buttonLayout_->addWidget(creditsButton_, 1, 0);
    buttonLayout_->addWidget(exitGameButton_, 1, 1);

    title_->setText(titleText_);
    title_->setFont(layouts::pieceFont);

    titleScreenLayout_->addWidget(title_);
    titleScreenLayout_->addLayout(buttonLayout_);

    setLayout(titleScreenLayout_);

};

// Closes application
void TitleScreen::exit()
{
    qApp->exit();
}

}
