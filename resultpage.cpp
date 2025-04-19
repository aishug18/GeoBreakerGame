#include "resultpage.h"
#include "mainwindow.h"
#include "mappage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

ResultPage::ResultPage(int finalScore,
                       int correctCount,
                       int wrongCount,
                       QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle("Game Over");
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(40,40,40,40);
    layout->setSpacing(20);

    // Big score
    auto* scoreLabel = new QLabel(
        QString("Your final score:\n%1").arg(finalScore), this);
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setStyleSheet("font-size:24px; font-weight:bold;");
    layout->addWidget(scoreLabel);

    // Correct / Wrong stats
    auto* correctLabel = new QLabel(
        QString("Correct answers: %1").arg(correctCount), this);
    auto* wrongLabel   = new QLabel(
        QString("Wrong answers:   %1").arg(wrongCount),   this);
    correctLabel->setAlignment(Qt::AlignCenter);
    wrongLabel  ->setAlignment(Qt::AlignCenter);
    correctLabel->setStyleSheet("font-size:18px;");
    wrongLabel  ->setStyleSheet("font-size:18px;");
    layout->addWidget(correctLabel);
    layout->addWidget(wrongLabel);

    // Buttons
    auto* btnLayout = new QHBoxLayout;
    auto* mainMenuBtn = new QPushButton("Main Menu", this);
    auto* mapBtn      = new QPushButton("Map", this);
    btnLayout->addWidget(mainMenuBtn);
    btnLayout->addWidget(mapBtn);
    layout->addLayout(btnLayout);

    connect(mainMenuBtn, &QPushButton::clicked, this, &ResultPage::onMainMenuClicked);
    connect(mapBtn,      &QPushButton::clicked, this, &ResultPage::onMapClicked);
}


void ResultPage::onMainMenuClicked() {
    auto* mw = new MainWindow();
    mw->show();
    close();
}

void ResultPage::onMapClicked() {
    auto* mp = new MapPage();
    mp->show();
    close();
}
