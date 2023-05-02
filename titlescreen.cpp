
#include "titlescreen.hpp"

TitleScreen::TitleScreen(QWidget* parent)
    : QWidget(parent),
    topButtonLayout(new QHBoxLayout),
    bottomButtonLayout(new QHBoxLayout),
    titleScreenLayout(new QGridLayout)
{
    // Title screen buttons
    m_newGameButton  = new QPushButton("Start",   this);
    m_creditsButton  = new QPushButton("Credits", this);
    m_exitGameButton = new QPushButton("Exit",    this);
    m_endGameButton  = new QPushButton("Practice end games", this);

    m_newGameButton-> setFixedWidth(200);
    m_endGameButton-> setFixedWidth(200);
    m_creditsButton-> setFixedWidth(200);
    m_exitGameButton->setFixedWidth(200);

    // Connect the exit button to the exit function. It closes the app
    connect(m_exitGameButton, &QPushButton::clicked, this, &TitleScreen::exit);

    // Alignment of our buttons.
    topButtonLayout->   addWidget(m_newGameButton,  0, Qt::AlignHCenter);
    topButtonLayout->   addWidget(m_endGameButton,  0, Qt::AlignHCenter);
    bottomButtonLayout->addWidget(m_creditsButton,  1, Qt::AlignHCenter);
    bottomButtonLayout->addWidget(m_exitGameButton, 1, Qt::AlignHCenter);

    titleScreenLayout->addLayout(topButtonLayout,    0, 0);
    titleScreenLayout->addLayout(bottomButtonLayout, 1, 0);

    setLayout(titleScreenLayout);

};

// Closes application
void TitleScreen::exit()
{
    qApp->exit();
}
