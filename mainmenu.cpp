
#include "mainmenu.hpp"
#include <QDebug>

MainMenu::MainMenu(QMainWindow* parent)
    :
    mainMenuLayout{new QStackedLayout()},
    chessBoard{new ChessBoard(this)},
    titleScreen{new TitleScreen(this)},
    creditsScreen{new CreditsScreen(tr("Abdoodoo and Hibooboo"), this)},
    endGamesScreen{new EndGamesScreen(this)},
    parent_{parent}

{
    // Defining a custom layout for MainMenu. This is the reason for the message in output
    mainMenuLayout->addWidget(titleScreen);
    mainMenuLayout->addWidget(chessBoard);
    mainMenuLayout->addWidget(creditsScreen);
    mainMenuLayout->addWidget(endGamesScreen);
    mainMenuLayout->setCurrentWidget(titleScreen);


    // The central widget is the widget u see when u run. I use it to switch screens
    QWidget* centralWidget = new QWidget();
    centralWidget->setLayout(mainMenuLayout);
    setCentralWidget(centralWidget);

    // connect main menu buttons to their proper functions
    connect(titleScreen->m_newGameButton, SIGNAL(clicked()), chessBoard, SLOT(startGame()));
    connect(titleScreen->m_creditsButton, SIGNAL(clicked()), this, SLOT(onCreditsPress()));
    connect(titleScreen->m_endGameButton, SIGNAL(clicked()), this, SLOT(onEndGamesPress()));
    connect(creditsScreen->m_backButton, SIGNAL(clicked()), this, SLOT(onBackPress()));
    connect(chessBoard, SIGNAL(gameStarted()), this, SLOT(onGameStarted()));

    //connect end games buttons
    connect(endGamesScreen->endGameButton1_, SIGNAL(clicked()), chessBoard, SLOT(startEndGame1()));
    connect(endGamesScreen->endGameButton2_, SIGNAL(clicked()), chessBoard, SLOT(startEndGame2()));
    connect(endGamesScreen->endGameButton3_, SIGNAL(clicked()), chessBoard, SLOT(startEndGame3()));
    connect(endGamesScreen->endGameButton4_, SIGNAL(clicked()), chessBoard, SLOT(startEndGame4()));
    connect(endGamesScreen->endGameButton5_, SIGNAL(clicked()), chessBoard, SLOT(startTestGame()));
}

// Slot that switches the current screen to the titlescreen
void MainMenu::onBackPress()
{
    mainMenuLayout->setCurrentWidget(titleScreen);
}

// Slot that switches the current screen to credits screen
void MainMenu::onCreditsPress()
{
    mainMenuLayout->setCurrentWidget(creditsScreen);
}

void MainMenu::onEndGamesPress()
{
    mainMenuLayout->setCurrentWidget(endGamesScreen);
}

// Slot that switches to chessBoard screen.Sensitive to the gameStarted() signal defined in chessBoard
void MainMenu::onGameStarted()
{
    mainMenuLayout->setCurrentWidget(chessBoard);
}


