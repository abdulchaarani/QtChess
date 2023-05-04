
#include "titlescreen.hpp"
#include "layouts.hpp"

TitleScreen::TitleScreen(QWidget* parent)
    : QWidget(parent),
    topButtonLayout(new QHBoxLayout),
    bottomButtonLayout(new QHBoxLayout),
    titleScreenLayout(new QGridLayout)
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
    topButtonLayout->   addWidget(newGameButton_,  0, Qt::AlignHCenter);
    topButtonLayout->   addWidget(endGameButton_,  0, Qt::AlignHCenter);
    bottomButtonLayout->addWidget(creditsButton_,  1, Qt::AlignHCenter);
    bottomButtonLayout->addWidget(exitGameButton_, 1, Qt::AlignHCenter);

    titleScreenLayout->addLayout(topButtonLayout,    0, 0);
    titleScreenLayout->addLayout(bottomButtonLayout, 1, 0);

    setLayout(titleScreenLayout);

};

// Closes application
void TitleScreen::exit()
{
    qApp->exit();
}
