#ifndef TUTORIALPAGE_H
#define TUTORIALPAGE_H

#include <QDialog>

namespace Ui {
class TutorialPage;
}

class TutorialPage : public QDialog
{
    Q_OBJECT

public:
    explicit TutorialPage(QWidget *parent = nullptr);
    ~TutorialPage();

private:
    Ui::TutorialPage *ui;
};

#endif // TUTORIALPAGE_H
