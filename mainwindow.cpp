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

    // Example: pushButton_1 -> soft blue
    ui->play->setStyleSheet("QPushButton { background-color: #add8e6; color: black; border-radius: 8px; padding: 6px; }");

    // Example: pushButton_2 -> pastel pink
    ui->Tutorial->setStyleSheet("QPushButton { background-color: #ffb6c1; color: black; border-radius: 8px; padding: 6px; }");

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
