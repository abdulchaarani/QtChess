
#include "mainmenu.h"
#include <QDebug>

MainMenu::MainMenu(QMainWindow *parent)
    : QMainWindow(parent),
    mainMenuLayout(new QStackedLayout(this)),
    chessBoard(new ChessBoard(this)),
    titleScreen(new TitleScreen(this)),
    creditsScreen(new CreditsScreen(tr("Abdoodoo and Hibooboo"), this))

{
    // Defining a custom layout for MainMenu. This is the reason for the message in output
    mainMenuLayout->addWidget(titleScreen);
    mainMenuLayout->addWidget(chessBoard);
    mainMenuLayout->addWidget(creditsScreen);
    mainMenuLayout->setCurrentWidget(titleScreen);

    // The central widget is the widget u see when u run. I use it to switch screens
    QWidget* centralWidget = new QWidget();
    centralWidget->setLayout(mainMenuLayout);
    setCentralWidget(centralWidget);

    // Connect the startGame button to the startGame function in chessboard
    connect(titleScreen->m_newGameButton, &QPushButton::clicked, chessBoard, &ChessBoard::startGame);

    // Connect the gameStarted signal emitted in startGame() to the onGameStarted slot in MainMenu
    connect(chessBoard, &ChessBoard::gameStarted, this, &MainMenu::onGameStarted);

    // Connect the credits button to the onCreditsPress slot. Switches current screen to credits screen
    connect(titleScreen->m_creditsButton, &QPushButton::clicked, this, &MainMenu::onCreditsPress);

    // Connect the backButton to the onBackPress slot. Returns to title screen from credits screen
    connect(creditsScreen->m_backButton, &QPushButton::clicked, this, &MainMenu::onBackPress);

}

// Slot that switches the current screen to the titlescreen
void MainMenu::onBackPress()
{
    mainMenuLayout->setCurrentWidget(titleScreen);
    setLayout(mainMenuLayout);
}

// Slot that switches the current screen to credits screen
void MainMenu::onCreditsPress()
{
    mainMenuLayout->setCurrentWidget(creditsScreen);
    setLayout(mainMenuLayout);
}

// Slot that switches to chessBoard screen.Sensitive to the gameStarted() signal defined in chessBoard
void MainMenu::onGameStarted()
{
    chessBoard->setFixedSize(800,800);
    mainMenuLayout->setCurrentWidget(chessBoard);
    setLayout(mainMenuLayout);
}
