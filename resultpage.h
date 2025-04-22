#ifndef RESULTPAGE_H
#define RESULTPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>

class ResultPage : public QWidget {
    Q_OBJECT

public:
    explicit ResultPage(int finalScore,
                        int correctCount,
                        int wrongCount,
                        QWidget* parent = nullptr);
    ~ResultPage();

private slots:
    void onMainMenuClicked();
    void onMapClicked();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    // UI elements from test branch
    QLabel* scoreLabel;
    QLabel* correctLabel;
    QLabel* wrongLabel;
    QListWidget* highScoreList;
    QPushButton* mainMenuBtn;
    QPushButton* mapBtn;

    // Score tracking from dev branch
    int finalScore;
};

#endif // RESULTPAGE_H
