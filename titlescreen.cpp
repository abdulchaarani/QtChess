
#include "titlescreen.h"

TitleScreen::TitleScreen(QWidget* parent)
    : QWidget(parent),
    topButtonLayout(new QHBoxLayout),
    bottomButtonLayout(new QHBoxLayout),
    titleScreenLayout(new QGridLayout)
{
    setWindowTitle(tr("Hibooboo & Abdoodoo's SPECTACULAR CHESS-INATOR"));

    // Using Pixmap so i can put custom image
    QPixmap pixmap("add image link here");
    m_titleImage = new QLabel(this);
    m_titleImage->setPixmap(pixmap);
    m_titleImage->setAlignment(Qt::AlignCenter);

    // Title screen will have these four buttons
    m_newGameButton  = new QPushButton("Start",   this);
    m_creditsButton  = new QPushButton("Credits", this);
    m_exitGameButton = new QPushButton("Exit",    this);
    m_endGameButton  = new QPushButton("Practice end games", this);

    // Connect the exit button to the exit function. It closes the app
    connect(m_exitGameButton, &QPushButton::clicked, this, &TitleScreen::exit);

    // Alignment of our buttons. Will be beautified later
    topButtonLayout->addWidget   (m_newGameButton,  0, Qt::AlignLeft);
    topButtonLayout->addWidget   (m_exitGameButton, 0, Qt::AlignRight);
    bottomButtonLayout->addWidget(m_creditsButton,  1, Qt::AlignLeft);
    bottomButtonLayout->addWidget(m_endGameButton,  1, Qt::AlignRight);

    // Needed two layouts to have a nice 2x2 grid without the hassle
    titleScreenLayout->addLayout(topButtonLayout,    0, 0);
    titleScreenLayout->addLayout(bottomButtonLayout, 1, 0);

    setLayout(titleScreenLayout);

};

// Closes application
void TitleScreen::exit()
{
    qApp->exit();
}
