
#ifndef TITLESCREEN_H
#define TITLESCREEN_H


#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QApplication>


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

    QPushButton* m_newGameButton;
    QPushButton* m_endGameButton;
    QPushButton* m_creditsButton;
    QPushButton* m_exitGameButton;

private slots:
    void exit();
};


#endif // TITLESCREEN_H
