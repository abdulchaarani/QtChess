
#include "titlescreen.hpp"

TitleScreen::TitleScreen(QWidget* parent) : QMainWindow(parent)
{
    // Using Pixmap so i can put custom image
    QPixmap pixmap("add image link here");
    m_titleImage = new QLabel(this);
    m_titleImage->setPixmap(pixmap);
    m_titleImage->setAlignment(Qt::AlignCenter);

    // Title screen will have these four buttons
    m_newGameButton  = new QPushButton("Start", this);
    connect(m_newGameButton, &QPushButton::clicked, this, &TitleScreen::startNewGame);

    m_creditsButton = new QPushButton("Credits", this);
    connect(m_creditsButton, &QPushButton::clicked, this, &TitleScreen::credits);

    m_endGameButton = new QPushButton("Exit", this);
    connect(m_exitGameButton, &QPushButton::clicked, this, &TitleScreen::exit);

    m_endGameButton  = new QPushButton("Practice end games", this);
    connect(m_endGameButton, &QPushButton::clicked, this, &TitleScreen::endGame);

    // Using QVBoxLayout to make it easier to adjust window size after resizing.
    QVBoxLayout* screenLayout = new QVBoxLayout;
    screenLayout->addWidget(m_titleImage);
    screenLayout->addWidget(m_newGameButton);
    screenLayout->addWidget(m_endGameButton);

    // Tells QT to manage size and position of widgets in the mainWindow. Less of a hassle
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(screenLayout);
    setCentralWidget(centralWidget);

};

void TitleScreen::startNewGame()
{
    // Start new game
}

void TitleScreen::endGame()
{
    // Start end game
}

void TitleScreen::credits()
{
    // Pop-up
}

void TitleScreen::exit()
{
    qApp->exit();
}
