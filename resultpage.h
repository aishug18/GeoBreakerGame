#ifndef RESULTPAGE_H
#define RESULTPAGE_H

#include <QWidget>

namespace Ui {
class ResultPage;    // forward‑declare the UI class
}

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

private:
    Ui::ResultPage *ui;   // pointer to the UI
};

#endif // RESULTPAGE_H
