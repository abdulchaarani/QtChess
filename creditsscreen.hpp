
#ifndef CREDITSSCREEN_H
#define CREDITSSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>


class CreditsScreen : public QWidget
{
    Q_OBJECT
public:
    explicit CreditsScreen(const QString& creditsText, QWidget* parent);

    friend class ChessCore;

private:
    QLabel*      const credits_;
    QPushButton* const backButton_;
    QVBoxLayout* const creditsScreenLayout_;
};

#endif // CREDITSSCREEN_H
