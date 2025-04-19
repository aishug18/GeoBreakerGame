#include "resultpage.h"
#include "ui_resultpage.h"
#include "mainwindow.h"
#include "mappage.h"
#include <QSettings>
#include <algorithm>

ResultPage::ResultPage(int finalScore,
                       int correctCount,
                       int wrongCount,
                       QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ResultPage)
{
    ui->setupUi(this);

    // 1) Persist & load top‑5 high scores
    QSettings settings("MyCompany","GeoBreaker");
    QStringList scores = settings.value("highScores").toStringList();
    scores << QString::number(finalScore);
    std::sort(scores.begin(), scores.end(),
              [](auto &a, auto &b){ return a.toInt() > b.toInt(); });
    if (scores.size()>5) scores.resize(5);
    settings.setValue("highScores", scores);

    // 2) Populate the QListWidget in the UI
    ui->highScoreList->clear();
    ui->highScoreList->addItems(scores);

    // 3) Update the rest of the widgets
    ui->yourScoreLabel->setText(
        QString("Your Final Score:\n%1").arg(finalScore));
    ui->correctLabel->setText(
        QString("✅ Correct: %1").arg(correctCount));
    ui->wrongLabel->setText(
        QString("❌ Wrong: %1").arg(wrongCount));

    // 4) Wire up buttons
    connect(ui->mainMenuBtn, &QPushButton::clicked,
            this, &ResultPage::onMainMenuClicked);
    connect(ui->mapBtn,      &QPushButton::clicked,
            this, &ResultPage::onMapClicked);
}

ResultPage::~ResultPage() {
    delete ui;
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
