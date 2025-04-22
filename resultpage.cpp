#include "resultpage.h"
#include "mainwindow.h"
#include "mappage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPainter>

ResultPage::ResultPage(int finalScore,
                       int correctCount,
                       int wrongCount,
                       QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle("Game Over");

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(80, 80, 80, 80);
    layout->setSpacing(40);

    auto* scoreLabel = new QLabel(
        QString("Your Final Score:\n%1").arg(finalScore), this);
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setStyleSheet("font-size: 48px; font-weight: bold; color: black;");
    layout->addWidget(scoreLabel);

    auto* correctLabel = new QLabel(
        QString("✅ Correct Answers: %1").arg(correctCount), this);
    auto* wrongLabel = new QLabel(
        QString("❌ Wrong Answers: %1").arg(wrongCount), this);

    correctLabel->setAlignment(Qt::AlignCenter);
    wrongLabel->setAlignment(Qt::AlignCenter);

    correctLabel->setStyleSheet("font-size: 32px; color: green;");
    wrongLabel->setStyleSheet("font-size: 32px; color: red;");

    layout->addWidget(correctLabel);
    layout->addWidget(wrongLabel);

    auto* btnLayout = new QHBoxLayout;
    auto* mainMenuBtn = new QPushButton("🏠 Main Menu", this);
    auto* mapBtn = new QPushButton("🗺️ Map", this);

    // Styling buttons for a big-screen look
    QString btnStyle = "font-size: 24px; padding: 40px 80px; border-radius: 10px;";
    mainMenuBtn->setStyleSheet(btnStyle);
    mapBtn->setStyleSheet(btnStyle);

    btnLayout->addStretch();
    btnLayout->addWidget(mainMenuBtn);
    btnLayout->addSpacing(40);
    btnLayout->addWidget(mapBtn);
    btnLayout->addStretch();
    layout->addLayout(btnLayout);

    connect(mainMenuBtn, &QPushButton::clicked, this, &ResultPage::onMainMenuClicked);
    connect(mapBtn, &QPushButton::clicked, this, &ResultPage::onMapClicked);
}

void ResultPage::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QPixmap bg(":/images/assets/result_background.jpg");

    // Scale the pixmap to fit the entire window
    QPixmap scaled = bg.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, scaled);
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
