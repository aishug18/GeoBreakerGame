#include "gamepage.h"
#include "ui_gamepage.h"

GamePage::GamePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GamePage)
{
    ui->setupUi(this);
    this->setWindowTitle("Game");
}

GamePage::~GamePage()
{
    delete ui;
}
