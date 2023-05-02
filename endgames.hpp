
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

    QPushButton* queenRookButton_;
    QPushButton* philidorButton_;
    QPushButton* gelfandButton_;
    QPushButton* ponzianiButton_;

    inline static const int buttonSize_{100};

};

#endif // ENDGAMES_HPP
