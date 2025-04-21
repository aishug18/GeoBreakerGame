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
        color: black;
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
        clickPlayer1->play();  // Play click sound 1
        tutorial.exec();  // Opens as modal pop-up
    });

    connect(ui->play, &QPushButton::clicked, this, [=]() {
        MapPage *mapWindow = new MapPage();
        clickPlayer1->play();  // Play click sound 1
        musicPlayer->stop(); // Stop menu music
        mapWindow->show();   // show the new map window
        this->close();       // close the current main menu window
    });

    // Create the audio output and player
    audioOutput = new QAudioOutput(this);
    musicPlayer = new QMediaPlayer(this);

    // Set audio output
    musicPlayer->setAudioOutput(audioOutput);

    // Load and play music
    musicPlayer->setSource(QUrl("qrc:/images/assets/menu_music.mp3"));
    audioOutput->setVolume(0.1);  // volume
    musicPlayer->play();
    musicPlayer->setLoops(QMediaPlayer::Infinite);

    clickAudio1 = new QAudioOutput(this);
    clickAudio1->setVolume(0.5);
    clickPlayer1 = new QMediaPlayer(this);
    clickPlayer1->setAudioOutput(clickAudio1);
    clickPlayer1->setSource(QUrl("qrc:/images/assets/button_click_sound_1.mp3"));

}

MainWindow::~MainWindow()
{
    delete ui;
}
