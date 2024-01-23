
#ifndef CREDITSSCREEN_H
#define CREDITSSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

namespace view{

class CreditsScreen : public QWidget
{
    Q_OBJECT
public:
    explicit CreditsScreen(QWidget* parent);

    QPushButton* const backButton_;

private:
    QLabel*      const credits_;

    QVBoxLayout* const creditsScreenLayout_;

    QString      const creditsText_
    {
        "QtChess\n"
        "Abdul Chaarani\t1793305\n"
        "Hiba Chaarani\t2205674\n"
        "INF1015 - 2023\n\n"
        "License: MIT License\n"

    };
};
}
#endif // CREDITSSCREEN_H
