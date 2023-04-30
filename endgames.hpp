
#ifndef ENDGAMES_HPP
#define ENDGAMES_HPP

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>

class EndGamesScreen : public QWidget
{
    Q_OBJECT
public:
    explicit EndGamesScreen(QWidget* parent = nullptr);

    friend class MainMenu;

private:
    QVBoxLayout* verticalButtonLayout_;

    // Im gonna draw an image when i have time
    QPushButton* endGameButton1_;
    QPushButton* endGameButton2_;
    QPushButton* endGameButton3_;
    QPushButton* endGameButton4_;
    QPushButton* endGameButton5_;

    inline static const int buttonSize_{100};

};

#endif // ENDGAMES_HPP
