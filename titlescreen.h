
#ifndef TITLESCREEN_H
#define TITLESCREEN_H


#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QApplication>

/* The titleScreen class was originally supposed to be the MainMenu class but it became so big i seperated them
 * in two. You might see some unsed things here because of this. This class is the screen u see when u open the
 * game. It contains two QHBoxLayouts because i wanted a nice 2x2 grid of buttons that can be used easily (i
 * wanted to avoid using for loops like u did in chessBoard bc im lazy af). If you dont already know, a
 * QHBoxLayout is a horizontal layout.*/

class TitleScreen : public QWidget
{
    Q_OBJECT
public:
    explicit TitleScreen(QWidget* parent = nullptr);

    friend class MainMenu;

private:
    QHBoxLayout* const topButtonLayout;
    QHBoxLayout* const bottomButtonLayout;
    QGridLayout* const titleScreenLayout;

    // Im gonna draw an image when i have time
    QLabel*      m_titleImage;
    QPushButton* m_newGameButton;
    QPushButton* m_endGameButton;
    QPushButton* m_creditsButton;
    QPushButton* m_exitGameButton;

private slots:
    void exit();
};


#endif // TITLESCREEN_H
