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

    mapAudioOutput = new QAudioOutput(this);
    mapMusicPlayer = new QMediaPlayer(this);
    mapMusicPlayer->setAudioOutput(mapAudioOutput);
    mapMusicPlayer->setSource(QUrl("qrc:/images/assets/map_music.mp3"));  // or whatever file
    mapAudioOutput->setVolume(0.2); // volume
    mapMusicPlayer->play();
    mapMusicPlayer->setLoops(QMediaPlayer::Infinite);

    clickAudio = new QAudioOutput(this);
    clickPlayer = new QMediaPlayer(this);
    clickPlayer->setAudioOutput(clickAudio);
    clickPlayer->setSource(QUrl("qrc:/images/assets/button_click_sound_1.mp3"));
    clickAudio->setVolume(0.5); // volume setting


}

MapPage::~MapPage()
{
    delete ui;
}

void MapPage::on_enterGameButton_clicked()
{
    GamePage *gameWindow = new GamePage();
    clickPlayer->play();  // Play click sound 1
    mapMusicPlayer->stop(); // Stop map page music
    gameWindow->show();
    this->close();  // Close the map window
}

void MapPage::on_returnToMenuButton_clicked()
{
    MainWindow *mainMenu = new MainWindow();
    clickPlayer->play();  // Play click sound 1
    mapMusicPlayer->stop(); // Stop map page music
    mainMenu->show();
    this->close();  // Close the current MapPage
}

