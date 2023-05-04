
#include "creditsscreen.hpp"
#include "layouts.hpp"

CreditsScreen::CreditsScreen(const QString& creditsText, QWidget* parent) :
    QWidget(parent),
    credits_(new QLabel(creditsText, this)),
    backButton_(new QPushButton(tr("take me back to main menu"), this )),
    creditsScreenLayout_(new QVBoxLayout(this))
{
    // Setup credits page UI
    creditsScreenLayout_->addWidget(credits_, 0, Qt::AlignHCenter);
    creditsScreenLayout_->addWidget(backButton_);
    backButton_->setStyleSheet(layouts::menuButtonFont);
}
