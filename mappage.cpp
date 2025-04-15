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
    this->setStyleSheet(
        "MapPage {"
        " background-image: url(:/images/assets/world_map.jpg);"
        " background-repeat: no-repeat;"
        " background-position: center;"
        " }"
        );

    QString buttonStyle = R"(
    QPushButton {
        border-image: url(:/images/assets/wood_button.png);
        color: black     ;
        font-weight: bold;
        font-size: 16px;
        padding: 10px;
    }
    QPushButton:hover {
        opacity: 0.85;
    }
)";

    ui->enterGameButton->setStyleSheet(buttonStyle);
    ui->returnToMenuButton->setStyleSheet(buttonStyle);

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

