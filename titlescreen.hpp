
#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QApplication>

namespace view{

class TitleScreen : public QWidget
{
    Q_OBJECT
public:
    explicit TitleScreen(QWidget* parent = nullptr);

    QPushButton* newGameButton_;
    QPushButton* endGameButton_;
    QPushButton* creditsButton_;
    QPushButton* exitGameButton_;

private:
    QVBoxLayout* const titleScreenLayout_;
    QLabel*      title_;
    QGridLayout* const buttonLayout_;
    QString      const titleText_{"QtChess ♚"};

private slots:
    void exit();
};

}
#endif // TITLESCREEN_H
