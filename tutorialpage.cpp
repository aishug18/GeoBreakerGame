#include "tutorialpage.h"
#include "ui_tutorialpage.h"

TutorialPage::TutorialPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TutorialPage)
{
    ui->setupUi(this);
    this->setWindowTitle("Tutorial");
    this->showFullScreen();
}

TutorialPage::~TutorialPage()
{
    delete ui;
}
