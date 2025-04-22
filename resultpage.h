#ifndef RESULTPAGE_H
#define RESULTPAGE_H

#include <QWidget>

class QLabel;
class QPushButton;

class ResultPage : public QWidget {
    Q_OBJECT

public:
   explicit ResultPage(int finalScore,
                         int correctCount,
                        int wrongCount,
                       QWidget* parent = nullptr);
private slots:
    void onMainMenuClicked();
    void onMapClicked();

private:
    int score;
    QLabel* scoreLabel;
    QPushButton* mainMenuBtn;
    QPushButton* mapBtn;

protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif // RESULTPAGE_H
