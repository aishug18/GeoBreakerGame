#include "mainwindow.h"
#include "mappage.h"
#include "tutorialpage.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Geo Breaker");
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor("#f5f5dc")); // beige
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    QPixmap image(":/images/assets/ge.png");  // or full path e.g. "C:/Users/kunj/Pictures/pic.png"
    ui->imageLabel->setScaledContents(true);
    ui->imageLabel->setPixmap(image);

    QString menuButtonStyle = R"(
    QPushButton {
        border-image: url(:/images/assets/wood_button.png);
        color: white;
        font-weight: bold;
        font-size: 18px;
        padding: 10px;
    }
    QPushButton:hover {
        opacity: 0.9;
    }
)";

    ui->play->setStyleSheet(menuButtonStyle);
    ui->Tutorial->setStyleSheet(menuButtonStyle);

    connect(ui->Tutorial, &QPushButton::clicked, this, [=]() {
        TutorialPage tutorial(this);
        tutorial.exec();  // Opens as modal pop-up
    });

    connect(ui->play, &QPushButton::clicked, this, [=]() {
        MapPage *mapWindow = new MapPage();
        mapWindow->show();   // show the new map window
        this->close();       // close the current main menu window
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
