/**
* Program that defines the methods of the CreditsScreen class (UI configurations).
* \file   creditsscreen.cpp
* \author Abdul-Wahab et Hiba
* \date   4 mai 2023
* Créé le 9 avril 2023
*/

#include "creditsscreen.hpp"
#include "layouts.hpp"

namespace view{

CreditsScreen::CreditsScreen(QWidget* parent) :
    QWidget(parent),
    credits_(new QLabel(this)),
    backButton_(new QPushButton("take me back to main menu", this )),
    creditsScreenLayout_(new QVBoxLayout(this))
{
    // Setup credits page UI
    credits_->setText(creditsText_);
    credits_->setFont(layouts::creditsFont);
    creditsScreenLayout_->addWidget(credits_, 0, Qt::AlignHCenter);
    creditsScreenLayout_->addWidget(backButton_);
    backButton_->setStyleSheet(layouts::menuButtonFont);
}

}
