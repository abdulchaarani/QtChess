
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

    friend class ChessCore;

private:
    QHBoxLayout* const topButtonLayout;
    QHBoxLayout* const bottomButtonLayout;
    QGridLayout* const titleScreenLayout;

    QPushButton* newGameButton_;
    QPushButton* endGameButton_;
    QPushButton* creditsButton_;
    QPushButton* exitGameButton_;

private slots:
    void exit();
};


#endif // TITLESCREEN_H
