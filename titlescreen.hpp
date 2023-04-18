
#ifndef TITLESCREEN_H
#define TITLESCREEN_H


#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication> //to allow the use of qApp

class TitleScreen : public QMainWindow
{
    Q_OBJECT
public:
    TitleScreen();
    // Chat GPT told me to do this. I might change later
    explicit TitleScreen(QWidget* parent = nullptr);


private:
    // Im gonna draw an image when i have time
    QLabel*      m_titleImage;
    QPushButton* m_newGameButton;
    QPushButton* m_endGameButton;
    QPushButton* m_creditsButton;
    QPushButton* m_exitGameButton;

private slots:
    void startNewGame(); // standard chess game
    void endGame();      // endgame plays (think queens gambit)
    void credits();      // pop-up with credits
    void exit();         // exits game completely
};


#endif // TITLESCREEN_H
