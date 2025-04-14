#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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


}

MainWindow::~MainWindow()
{
    delete ui;
}
