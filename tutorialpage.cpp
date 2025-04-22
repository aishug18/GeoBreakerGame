#include "tutorialpage.h"
#include "ui_tutorialpage.h"

TutorialPage::TutorialPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TutorialPage)
{
    ui->setupUi(this);
    this->setWindowTitle("Tutorial");

    this->setStyleSheet(R"(
    QDialog {
        background-image: url(:/images/assets/tutorial_background.jpg);
        background-repeat: no-repeat;
        background-position: center;
        background-attachment: fixed;
    }
)");

    QString buttonStyle = R"(
    QPushButton {
        border-image: url(:/images/assets/wood_button.png);
        color: black;
        font-weight: bold;
        font-size: 20px;
        padding: 10px;
    }
    QPushButton:hover {
        opacity: 0.85;
    }
)";

    ui->closeButton->setStyleSheet(buttonStyle);

}

TutorialPage::~TutorialPage()
{
    delete ui;
}



void TutorialPage::on_closeButton_clicked()
{
    this->close();
}

