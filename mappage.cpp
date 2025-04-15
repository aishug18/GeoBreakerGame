#include "mappage.h"
#include "gamepage.h"
#include "mainwindow.h"
#include "ui_mappage.h"

MapPage::MapPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MapPage)
{
    ui->setupUi(this);
    this->setWindowTitle("Map Page");
}

MapPage::~MapPage()
{
    delete ui;
}

void MapPage::on_enterGameButton_clicked()
{
    GamePage *gameWindow = new GamePage();
    gameWindow->show();
    this->close();  // Close the map window
}

void MapPage::on_returnToMenuButton_clicked()
{
    MainWindow *mainMenu = new MainWindow();
    mainMenu->show();
    this->close();  // Close the current MapPage
}

