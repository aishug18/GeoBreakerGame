#include "resultpage.h"
#include "mainwindow.h"
#include "mappage.h"
#include <QSettings>
#include <algorithm>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QListWidget>

ResultPage::ResultPage(int finalScore,
                       int correctCount,
                       int wrongCount,
                       QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle("Game Over");

    // Main layout setup
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(80, 80, 80, 80);
    layout->setSpacing(40);

    // Score display
    auto* scoreLabel = new QLabel(
        QString("Your Final Score:\n%1").arg(finalScore), this);
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setStyleSheet(
        "font-size: 48px; font-weight: bold; color: black;");
    layout->addWidget(scoreLabel);

    // Correct/wrong counters
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

    // High score handling (from dev branch)
    QSettings settings("MyCompany", "GeoBreaker");
    QStringList scores = settings.value("highScores").toStringList();
    scores << QString::number(finalScore);
    std::sort(scores.begin(), scores.end(),
              [](const QString &a, const QString &b) {
                  return a.toInt() > b.toInt();
              });
    if(scores.size() > 5) scores.resize(5);
    settings.setValue("highScores", scores);

    // High score list (from dev branch, styled for test branch)
    auto* highScoreList = new QListWidget(this);
    highScoreList->addItems(scores);
    highScoreList->setStyleSheet(
        "font-size: 24px; background-color: rgba(255, 255, 255, 200);"
        "border-radius: 10px; padding: 10px;");
    highScoreList->setFixedHeight(150);
    layout->addWidget(highScoreList);

    // Button layout (from test branch with improved styling)
    auto* btnLayout = new QHBoxLayout;
    auto* mainMenuBtn = new QPushButton("🏠 Main Menu", this);
    auto* mapBtn = new QPushButton("🗺️ Map", this);

    QString btnStyle = 
        "font-size: 24px; padding: 20px 40px;"
        "border-radius: 10px; min-width: 200px;";
    mainMenuBtn->setStyleSheet(btnStyle + "background-color: #4CAF50; color: white;");
    mapBtn->setStyleSheet(btnStyle + "background-color: #2196F3; color: white;");

    btnLayout->addStretch();
    btnLayout->addWidget(mainMenuBtn);
    btnLayout->addSpacing(40);
    btnLayout->addWidget(mapBtn);
    btnLayout->addStretch();
    layout->addLayout(btnLayout);

    // Connect buttons (from both branches)
    connect(mainMenuBtn, &QPushButton::clicked,
            this, &ResultPage::onMainMenuClicked);
    connect(mapBtn, &QPushButton::clicked,
            this, &ResultPage::onMapClicked);
}

ResultPage::~ResultPage() {}

void ResultPage::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QPixmap bg(":/images/assets/result_background.jpg");
    painter.drawPixmap(0, 0, width(), height(), bg);
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