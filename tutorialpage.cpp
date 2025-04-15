#include "tutorialpage.h"
#include "ui_tutorialpage.h"

TutorialPage::TutorialPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TutorialPage)
{
    ui->setupUi(this);
    this->setWindowTitle("Tutorial");
}

TutorialPage::~TutorialPage()
{
    delete ui;
}
