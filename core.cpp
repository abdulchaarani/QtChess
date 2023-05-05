
#include "core.hpp"
#include <QDebug>

ChessCore::ChessCore()
         : mainGame_{new model::ChessGame}
         , chessboard_{new view::Chessboard}
         , mainMenuLayout_{new QStackedLayout}
         , titleScreen_{new view::TitleScreen(this)}
         , creditsScreen_{new view::CreditsScreen(this)}
         , endGamesScreen_{new view::EndGamesScreen(this)}

{

    mainMenuLayout_->addWidget(titleScreen_);
    mainMenuLayout_->addWidget(chessboard_);
    mainMenuLayout_->addWidget(creditsScreen_);
    mainMenuLayout_->addWidget(endGamesScreen_);
    mainMenuLayout_->setCurrentWidget(titleScreen_);

    QWidget* centralWidget = new QWidget();
    centralWidget->setLayout(mainMenuLayout_);
    setCentralWidget(centralWidget);

    connectSignals();

    setFixedSize(layouts::screenWidth, layouts::screenHeight);
}

// Slot that switches the current screen to the titlescreen
void ChessCore::onBackPress()
{
    mainMenuLayout_->setCurrentWidget(titleScreen_);
}

// Slot that switches the current screen to credits screen
void ChessCore::onCreditsPress()
{
    mainMenuLayout_->setCurrentWidget(creditsScreen_);
}

void ChessCore::onEndGamesPress()
{
    mainMenuLayout_->setCurrentWidget(endGamesScreen_);
}

// Slot that switches to chessBoard screen.Sensitive to the gameStarted() signal defined in chessBoard
void ChessCore::onGameStarted()
{
    mainMenuLayout_->setCurrentWidget(chessboard_);
}

void ChessCore::connectSignals()
{
    // connect view to model
    connect(chessboard_, SIGNAL(sendClick(Coordinates)), mainGame_, SLOT(validateClick(Coordinates)));
    connect(mainGame_, SIGNAL(initialiseColor(Coordinates,Color)),     chessboard_, SLOT(setPieceColor(Coordinates,Color)));
    connect(mainGame_, SIGNAL(initialiseDisplay(Coordinates,QString)), chessboard_, SLOT(setBoxText(Coordinates,QString)));
    connect(mainGame_, SIGNAL(highlight(Coordinates,Highlight)),           chessboard_, SLOT(processHighlight(Coordinates,Highlight)));
    connect(mainGame_, SIGNAL(updateCoordinates(Coordinates,Coordinates)), chessboard_, SLOT(moveViewPiece(Coordinates,Coordinates)));
    connect(mainGame_, SIGNAL(turnChanged(Color)),                chessboard_, SLOT(toggleTurnLabel(Color)));
    connect(mainGame_, SIGNAL(blinkCheckedKing(Coordinates,int)), chessboard_, SLOT(startTimer(Coordinates,int)));
    connect(mainGame_, SIGNAL(killKing(Coordinates)), chessboard_, SLOT(rotateKing(Coordinates)));
    connect(mainGame_, SIGNAL(crownWinner(Color)),    chessboard_, SLOT(displayWinner(Color)));

    // connect main menu buttons to their proper functions
    connect(titleScreen_->newGameButton_, SIGNAL(clicked()), mainGame_, SLOT(startNewGame()));
    connect(titleScreen_->creditsButton_, SIGNAL(clicked()), this, SLOT(onCreditsPress()));
    connect(titleScreen_->endGameButton_, SIGNAL(clicked()), this, SLOT(onEndGamesPress()));
    connect(creditsScreen_->backButton_,  SIGNAL(clicked()), this, SLOT(onBackPress()));
    connect(mainGame_, SIGNAL(gameStarted()), this, SLOT(onGameStarted()));

    //connect end games buttons
    connect(endGamesScreen_->queenRookButton_, SIGNAL(clicked()), mainGame_, SLOT(startQueenVRook()));
    connect(endGamesScreen_->philidorButton_,  SIGNAL(clicked()), mainGame_, SLOT(startPhilidor()));
    connect(endGamesScreen_->gelfandButton_,   SIGNAL(clicked()), mainGame_, SLOT(startGelfandVSvidler()));
    connect(endGamesScreen_->ponzianiButton_,  SIGNAL(clicked()), mainGame_, SLOT(startPonziani()));
    connect(endGamesScreen_->endGameButton5_,  SIGNAL(clicked()), mainGame_, SLOT(startTestGame()));
}

