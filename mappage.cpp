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
    mapMusicPlayer->setSource(QUrl("qrc:/images/assets/map_music.mp3"));
    mapAudioOutput->setVolume(0.2);
    mapMusicPlayer->play();
    mapMusicPlayer->setLoops(QMediaPlayer::Infinite);

    clickAudio = new QAudioOutput(this);
    clickPlayer = new QMediaPlayer(this);
    clickPlayer->setAudioOutput(clickAudio);
    clickPlayer->setSource(QUrl("qrc:/images/assets/button_click_sound_1.mp3"));
    clickAudio->setVolume(0.5);

    ui->backToMapButton->setVisible(false);

    ui->textBrowser->setVisible(false);
    ui->textBrowser_2->setVisible(false);
    ui->textBrowser_3->setVisible(false);
    ui->textBrowser_4->setVisible(false);
    ui->textBrowser_5->setVisible(false);
    ui->textBrowser_6->setVisible(false);
    ui->textBrowser_7->setVisible(false);
    ui->textBrowser_8->setVisible(false);
    ui->textBrowser_9->setVisible(false);
    ui->textBrowser_10->setVisible(false);
    ui->textBrowser_11->setVisible(false);
    ui->textBrowser_12->setVisible(false);
    ui->textBrowser_13->setVisible(false);
    ui->textBrowser_14->setVisible(false);
    ui->textBrowser_15->setVisible(false);
    ui->textBrowser_16->setVisible(false);
    ui->textBrowser_17->setVisible(false);
    ui->textBrowser_18->setVisible(false);
    ui->textBrowser_19->setVisible(false);
    ui->textBrowser_20->setVisible(false);


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


void MapPage::on_commandLinkButton_clicked()
{
    clickPlayer->play();

    ui->textBrowser->setVisible(true);
    ui->backToMapButton->setVisible(true);
    ui->enterGameButton->setVisible(false);
    ui->returnToMenuButton->setVisible(false);

    ui->commandLinkButton->setVisible(false);
    ui->commandLinkButton2->setVisible(false);
    ui->commandLinkButton3->setVisible(false);
    ui->commandLinkButton4->setVisible(false);
    ui->commandLinkButton5->setVisible(false);
    ui->commandLinkButton6->setVisible(false);
    ui->commandLinkButton7->setVisible(false);
    ui->commandLinkButton8->setVisible(false);
    ui->commandLinkButton9->setVisible(false);
    ui->commandLinkButton10->setVisible(false);
    ui->commandLinkButton11->setVisible(false);
    ui->commandLinkButton12->setVisible(false);
    ui->commandLinkButton13->setVisible(false);
    ui->commandLinkButton14->setVisible(false);
    ui->commandLinkButton15->setVisible(false);
    ui->commandLinkButton16->setVisible(false);
    ui->commandLinkButton17->setVisible(false);
    ui->commandLinkButton18->setVisible(false);
    ui->commandLinkButton19->setVisible(false);
    ui->commandLinkButton20->setVisible(false);


    ui->textBrowser->setText(
        "<h2>🇦🇺 Australia</h2>"
        "<p><b>Flag:</b> 🇦🇺</p>"
        "<p><b>Capital:</b> Canberra</p>"
        "<p><b>Famous indigenous wind instrument:</b> Digeridoo</p>"
        "<p><b>Animal only found naturally in Austrailia:</b> Kangaroo</p>"
        "<p><b>Largest natural coral reef:</b> Great Barrier Reef</p>"
        );
}

void MapPage::on_commandLinkButton2_clicked()
{
    clickPlayer->play();

    ui->textBrowser_2->setVisible(true);
    ui->backToMapButton->setVisible(true);
    ui->enterGameButton->setVisible(false);
    ui->returnToMenuButton->setVisible(false);

    ui->commandLinkButton->setVisible(false);
    ui->commandLinkButton2->setVisible(false);
    ui->commandLinkButton3->setVisible(false);
    ui->commandLinkButton4->setVisible(false);
    ui->commandLinkButton5->setVisible(false);
    ui->commandLinkButton6->setVisible(false);
    ui->commandLinkButton7->setVisible(false);
    ui->commandLinkButton8->setVisible(false);
    ui->commandLinkButton9->setVisible(false);
    ui->commandLinkButton10->setVisible(false);
    ui->commandLinkButton11->setVisible(false);
    ui->commandLinkButton12->setVisible(false);
    ui->commandLinkButton13->setVisible(false);
    ui->commandLinkButton14->setVisible(false);
    ui->commandLinkButton15->setVisible(false);
    ui->commandLinkButton16->setVisible(false);
    ui->commandLinkButton17->setVisible(false);
    ui->commandLinkButton18->setVisible(false);
    ui->commandLinkButton19->setVisible(false);
    ui->commandLinkButton20->setVisible(false);


    ui->textBrowser_2->setText(
        "<h2>🇳🇿 New Zealand</h2>"
        "<p><b>Flag:</b> 🇳🇿</p>"
        "<p><b>Capital:</b> Wellington</p>"
        "<p><b>Famous film location:</b> Lord of the Rings</p>"
        "<p><b>Indigenous name:</b> Aotearoa – Land of the Long White Cloud</p>"
        "<p><b>Sheep-to-people ratio:</b> Around 5:1</p>"
        "<p><b>Historic first:</b> First country to grant women the right to vote (1893)</p>"
        );
}
void MapPage::on_commandLinkButton3_clicked()
{
    clickPlayer->play();

    ui->textBrowser_3->setVisible(true);
    ui->backToMapButton->setVisible(true);
    ui->enterGameButton->setVisible(false);
    ui->returnToMenuButton->setVisible(false);

    ui->commandLinkButton->setVisible(false);
    ui->commandLinkButton2->setVisible(false);
    ui->commandLinkButton3->setVisible(false);
    ui->commandLinkButton4->setVisible(false);
    ui->commandLinkButton5->setVisible(false);
    ui->commandLinkButton6->setVisible(false);
    ui->commandLinkButton7->setVisible(false);
    ui->commandLinkButton8->setVisible(false);
    ui->commandLinkButton9->setVisible(false);
    ui->commandLinkButton10->setVisible(false);
    ui->commandLinkButton11->setVisible(false);
    ui->commandLinkButton12->setVisible(false);
    ui->commandLinkButton13->setVisible(false);
    ui->commandLinkButton14->setVisible(false);
    ui->commandLinkButton15->setVisible(false);
    ui->commandLinkButton16->setVisible(false);
    ui->commandLinkButton17->setVisible(false);
    ui->commandLinkButton18->setVisible(false);
    ui->commandLinkButton19->setVisible(false);
    ui->commandLinkButton20->setVisible(false);


    ui->textBrowser_3->setText(
        "<h2>🇨🇳 China</h2>"
        "<p><b>Flag:</b> 🇨🇳</p>"
        "<p><b>Capital:</b> Beijing</p>"
        "<p><b>Population:</b> Most populous country (though India is catching up)</p>"
        "<p><b>Landmark:</b> Great Wall of China – over 13,000 miles long</p>"
        "<p><b>Time zone:</b> Uses only one time zone</p>"
        "<p><b>Fun fact:</b> Invented toilet paper over 1,400 years ago</p>"
        );
}
void MapPage::on_commandLinkButton4_clicked()
{
    clickPlayer->play();

    ui->textBrowser_4->setVisible(true);
    ui->backToMapButton->setVisible(true);
    ui->enterGameButton->setVisible(false);
    ui->returnToMenuButton->setVisible(false);

    ui->commandLinkButton->setVisible(false);
    ui->commandLinkButton2->setVisible(false);
    ui->commandLinkButton3->setVisible(false);
    ui->commandLinkButton4->setVisible(false);
    ui->commandLinkButton5->setVisible(false);
    ui->commandLinkButton6->setVisible(false);
    ui->commandLinkButton7->setVisible(false);
    ui->commandLinkButton8->setVisible(false);
    ui->commandLinkButton9->setVisible(false);
    ui->commandLinkButton10->setVisible(false);
    ui->commandLinkButton11->setVisible(false);
    ui->commandLinkButton12->setVisible(false);
    ui->commandLinkButton13->setVisible(false);
    ui->commandLinkButton14->setVisible(false);
    ui->commandLinkButton15->setVisible(false);
    ui->commandLinkButton16->setVisible(false);
    ui->commandLinkButton17->setVisible(false);
    ui->commandLinkButton18->setVisible(false);
    ui->commandLinkButton19->setVisible(false);
    ui->commandLinkButton20->setVisible(false);


    ui->textBrowser_4->setText(
        "<h2>🇯🇵 Japan</h2>"
        "<p><b>Flag:</b> 🇯🇵</p>"
        "<p><b>Capital:</b> Tokyo</p>"
        "<p><b>Geography:</b> Over 6,800 islands</p>"
        "<p><b>Iconic mountain:</b> Mount Fuji</p>"
        "<p><b>Transport:</b> Shinkansen bullet trains exceed 300 km/h</p>"
        "<p><b>Fun tradition:</b> Crying sumo baby contest for good luck</p>"
        );
}
void MapPage::on_commandLinkButton5_clicked()
{
    clickPlayer->play();

    ui->textBrowser_5->setVisible(true);
    ui->backToMapButton->setVisible(true);
    ui->enterGameButton->setVisible(false);
    ui->returnToMenuButton->setVisible(false);

    ui->commandLinkButton->setVisible(false);
    ui->commandLinkButton2->setVisible(false);
    ui->commandLinkButton3->setVisible(false);
    ui->commandLinkButton4->setVisible(false);
    ui->commandLinkButton5->setVisible(false);
    ui->commandLinkButton6->setVisible(false);
    ui->commandLinkButton7->setVisible(false);
    ui->commandLinkButton8->setVisible(false);
    ui->commandLinkButton9->setVisible(false);
    ui->commandLinkButton10->setVisible(false);
    ui->commandLinkButton11->setVisible(false);
    ui->commandLinkButton12->setVisible(false);
    ui->commandLinkButton13->setVisible(false);
    ui->commandLinkButton14->setVisible(false);
    ui->commandLinkButton15->setVisible(false);
    ui->commandLinkButton16->setVisible(false);
    ui->commandLinkButton17->setVisible(false);
    ui->commandLinkButton18->setVisible(false);
    ui->commandLinkButton19->setVisible(false);
    ui->commandLinkButton20->setVisible(false);


    ui->textBrowser_5->setText(
        "<h2>🇮🇳 India</h2>"
        "<p><b>Flag:</b> 🇮🇳</p>"
        "<p><b>Capital:</b> New Delhi</p>"
        "<p><b>Population:</b> Second-most populous country</p>"
        "<p><b>Inventions:</b> Birthplace of chess, yoga, and the concept of zero</p>"
        "<p><b>Diet:</b> Largest vegetarian population globally</p>"
        "<p><b>Unique temple:</b> Worships a motorbike – Om Banna Temple</p>"
        );
}
void MapPage::on_commandLinkButton6_clicked()
{
    clickPlayer->play();

    ui->textBrowser_6->setVisible(true);
    ui->backToMapButton->setVisible(true);
    ui->enterGameButton->setVisible(false);
    ui->returnToMenuButton->setVisible(false);

    ui->commandLinkButton->setVisible(false);
    ui->commandLinkButton2->setVisible(false);
    ui->commandLinkButton3->setVisible(false);
    ui->commandLinkButton4->setVisible(false);
    ui->commandLinkButton5->setVisible(false);
    ui->commandLinkButton6->setVisible(false);
    ui->commandLinkButton7->setVisible(false);
    ui->commandLinkButton8->setVisible(false);
    ui->commandLinkButton9->setVisible(false);
    ui->commandLinkButton10->setVisible(false);
    ui->commandLinkButton11->setVisible(false);
    ui->commandLinkButton12->setVisible(false);
    ui->commandLinkButton13->setVisible(false);
    ui->commandLinkButton14->setVisible(false);
    ui->commandLinkButton15->setVisible(false);
    ui->commandLinkButton16->setVisible(false);
    ui->commandLinkButton17->setVisible(false);
    ui->commandLinkButton18->setVisible(false);
    ui->commandLinkButton19->setVisible(false);
    ui->commandLinkButton20->setVisible(false);


    ui->textBrowser_6->setText(
        "<h2>🇷🇺 Russia</h2>"
        "<p><b>Flag:</b> 🇷🇺</p>"
        "<p><b>Capital:</b> Moscow</p>"
        "<p><b>Size:</b> Largest country by land area</p>"
        "<p><b>Railway:</b> Trans-Siberian Railway – longest in the world</p>"
        "<p><b>Time zones:</b> Spans 11 time zones</p>"
        "<p><b>Climate:</b> Oymyakon – coldest inhabited place on Earth</p>"
        );
}
void MapPage::on_commandLinkButton7_clicked()
{
    clickPlayer->play();

    ui->textBrowser_7->setVisible(true);
    ui->backToMapButton->setVisible(true);
    ui->enterGameButton->setVisible(false);
    ui->returnToMenuButton->setVisible(false);

    ui->commandLinkButton->setVisible(false);
    ui->commandLinkButton2->setVisible(false);
    ui->commandLinkButton3->setVisible(false);
    ui->commandLinkButton4->setVisible(false);
    ui->commandLinkButton5->setVisible(false);
    ui->commandLinkButton6->setVisible(false);
    ui->commandLinkButton7->setVisible(false);
    ui->commandLinkButton8->setVisible(false);
    ui->commandLinkButton9->setVisible(false);
    ui->commandLinkButton10->setVisible(false);
    ui->commandLinkButton11->setVisible(false);
    ui->commandLinkButton12->setVisible(false);
    ui->commandLinkButton13->setVisible(false);
    ui->commandLinkButton14->setVisible(false);
    ui->commandLinkButton15->setVisible(false);
    ui->commandLinkButton16->setVisible(false);
    ui->commandLinkButton17->setVisible(false);
    ui->commandLinkButton18->setVisible(false);
    ui->commandLinkButton19->setVisible(false);
    ui->commandLinkButton20->setVisible(false);


    ui->textBrowser_7->setText(
        "<h2>🇮🇹 Italy</h2>"
        "<p><b>Flag:</b> 🇮🇹</p>"
        "<p><b>Capital:</b> Rome</p>"
        "<p><b>History:</b> Birthplace of the Renaissance (Florence)</p>"
        "<p><b>Unique feature:</b> Home to Vatican City – world’s smallest country</p>"
        "<p><b>Food origin:</b> Pizza began in Naples, 18th century</p>"
        "<p><b>Strange fact:</b> Ancient Romans used urine to whiten teeth</p>"
        );
}
void MapPage::on_commandLinkButton8_clicked()
{
    clickPlayer->play();

    ui->textBrowser_8->setVisible(true);
    ui->backToMapButton->setVisible(true);
    ui->enterGameButton->setVisible(false);
    ui->returnToMenuButton->setVisible(false);

    ui->commandLinkButton->setVisible(false);
    ui->commandLinkButton2->setVisible(false);
    ui->commandLinkButton3->setVisible(false);
    ui->commandLinkButton4->setVisible(false);
    ui->commandLinkButton5->setVisible(false);
    ui->commandLinkButton6->setVisible(false);
    ui->commandLinkButton7->setVisible(false);
    ui->commandLinkButton8->setVisible(false);
    ui->commandLinkButton9->setVisible(false);
    ui->commandLinkButton10->setVisible(false);
    ui->commandLinkButton11->setVisible(false);
    ui->commandLinkButton12->setVisible(false);
    ui->commandLinkButton13->setVisible(false);
    ui->commandLinkButton14->setVisible(false);
    ui->commandLinkButton15->setVisible(false);
    ui->commandLinkButton16->setVisible(false);
    ui->commandLinkButton17->setVisible(false);
    ui->commandLinkButton18->setVisible(false);
    ui->commandLinkButton19->setVisible(false);
    ui->commandLinkButton20->setVisible(false);


    ui->textBrowser_8->setText(
        "<h2>🏴 England (UK)</h2>"
        "<p><b>Flag:</b> 🏴</p>"
        "<p><b>Capital:</b> London</p>"
        "<p><b>Cultural icons:</b> Birthplace of Shakespeare and The Beatles</p>"
        "<p><b>Fun fact:</b> Big Ben is actually the bell, not the clock</p>"
        "<p><b>Tea culture:</b> Tea came from China via India</p>"
        "<p><b>Royal quirk:</b> The Queen owns all unmarked swans on the Thames</p>"
        );
}
void MapPage::on_commandLinkButton9_clicked()
{
    clickPlayer->play();

    ui->textBrowser_9->setVisible(true);
    ui->backToMapButton->setVisible(true);
    ui->enterGameButton->setVisible(false);
    ui->returnToMenuButton->setVisible(false);

    ui->commandLinkButton->setVisible(false);
    ui->commandLinkButton2->setVisible(false);
    ui->commandLinkButton3->setVisible(false);
    ui->commandLinkButton4->setVisible(false);
    ui->commandLinkButton5->setVisible(false);
    ui->commandLinkButton6->setVisible(false);
    ui->commandLinkButton7->setVisible(false);
    ui->commandLinkButton8->setVisible(false);
    ui->commandLinkButton9->setVisible(false);
    ui->commandLinkButton10->setVisible(false);
    ui->commandLinkButton11->setVisible(false);
    ui->commandLinkButton12->setVisible(false);
    ui->commandLinkButton13->setVisible(false);
    ui->commandLinkButton14->setVisible(false);
    ui->commandLinkButton15->setVisible(false);
    ui->commandLinkButton16->setVisible(false);
    ui->commandLinkButton17->setVisible(false);
    ui->commandLinkButton18->setVisible(false);
    ui->commandLinkButton19->setVisible(false);
    ui->commandLinkButton20->setVisible(false);


    ui->textBrowser_9->setText(
        "<h2>🇫🇷 France</h2>"
        "<p><b>Flag:</b> 🇫🇷</p>"
        "<p><b>Capital:</b> Paris</p>"
        "<p><b>Landmark:</b> Eiffel Tower was meant to be temporary</p>"
        "<p><b>Food:</b> More cheese varieties than days in the year</p>"
        "<p><b>History:</b> French Revolution briefly abolished monarchy</p>"
        "<p><b>Weird town name:</b> Y – just one letter</p>"
        );
}
void MapPage::on_commandLinkButton10_clicked()
{
    clickPlayer->play();

    ui->textBrowser_10->setVisible(true);
    ui->backToMapButton->setVisible(true);
    ui->enterGameButton->setVisible(false);
    ui->returnToMenuButton->setVisible(false);

    ui->commandLinkButton->setVisible(false);
    ui->commandLinkButton2->setVisible(false);
    ui->commandLinkButton3->setVisible(false);
    ui->commandLinkButton4->setVisible(false);
    ui->commandLinkButton5->setVisible(false);
    ui->commandLinkButton6->setVisible(false);
    ui->commandLinkButton7->setVisible(false);
    ui->commandLinkButton8->setVisible(false);
    ui->commandLinkButton9->setVisible(false);
    ui->commandLinkButton10->setVisible(false);
    ui->commandLinkButton11->setVisible(false);
    ui->commandLinkButton12->setVisible(false);
    ui->commandLinkButton13->setVisible(false);
    ui->commandLinkButton14->setVisible(false);
    ui->commandLinkButton15->setVisible(false);
    ui->commandLinkButton16->setVisible(false);
    ui->commandLinkButton17->setVisible(false);
    ui->commandLinkButton18->setVisible(false);
    ui->commandLinkButton19->setVisible(false);
    ui->commandLinkButton20->setVisible(false);


    ui->textBrowser_10->setText(
        "<h2>🇿🇦 South Africa</h2>"
        "<p><b>Flag:</b> 🇿🇦</p>"
        "<p><b>Capital(s):</b> Pretoria (administrative), Cape Town (legislative), Bloemfontein (judicial)</p>"
        "<p><b>Nickname:</b> Rainbow Nation</p>"
        "<p><b>Sports:</b> First African nation to host the soccer World Cup (2010)</p>"
        "<p><b>Nature:</b> Home to Table Mountain</p>"
        "<p><b>Languages:</b> 11 official languages</p>"
        );
}
void MapPage::on_commandLinkButton11_clicked()
{
    clickPlayer->play();

    ui->textBrowser_11->setVisible(true);
    ui->backToMapButton->setVisible(true);
    ui->enterGameButton->setVisible(false);
    ui->returnToMenuButton->setVisible(false);

    ui->commandLinkButton->setVisible(false);
    ui->commandLinkButton2->setVisible(false);
    ui->commandLinkButton3->setVisible(false);
    ui->commandLinkButton4->setVisible(false);
    ui->commandLinkButton5->setVisible(false);
    ui->commandLinkButton6->setVisible(false);
    ui->commandLinkButton7->setVisible(false);
    ui->commandLinkButton8->setVisible(false);
    ui->commandLinkButton9->setVisible(false);
    ui->commandLinkButton10->setVisible(false);
    ui->commandLinkButton11->setVisible(false);
    ui->commandLinkButton12->setVisible(false);
    ui->commandLinkButton13->setVisible(false);
    ui->commandLinkButton14->setVisible(false);
    ui->commandLinkButton15->setVisible(false);
    ui->commandLinkButton16->setVisible(false);
    ui->commandLinkButton17->setVisible(false);
    ui->commandLinkButton18->setVisible(false);
    ui->commandLinkButton19->setVisible(false);
    ui->commandLinkButton20->setVisible(false);


    ui->textBrowser_11->setText(
        "<h2>🇳🇬 Nigeria</h2>"
        "<p><b>Flag:</b> 🇳🇬</p>"
        "<p><b>Capital:</b> Abuja</p>"
        "<p><b>Population:</b> Most populous country in Africa</p>"
        "<p><b>Film industry:</b> Nollywood – second-largest by volume</p>"
        "<p><b>Culture:</b> Rich Yoruba and Igbo mythology</p>"
        "<p><b>Unique place:</b> Makoko – floating slum on stilts</p>"
        );
}
void MapPage::on_commandLinkButton12_clicked()
{
    clickPlayer->play();

    ui->textBrowser_12->setVisible(true);
    ui->backToMapButton->setVisible(true);
    ui->enterGameButton->setVisible(false);
    ui->returnToMenuButton->setVisible(false);

    ui->commandLinkButton->setVisible(false);
    ui->commandLinkButton2->setVisible(false);
    ui->commandLinkButton3->setVisible(false);
    ui->commandLinkButton4->setVisible(false);
    ui->commandLinkButton5->setVisible(false);
    ui->commandLinkButton6->setVisible(false);
    ui->commandLinkButton7->setVisible(false);
    ui->commandLinkButton8->setVisible(false);
    ui->commandLinkButton9->setVisible(false);
    ui->commandLinkButton10->setVisible(false);
    ui->commandLinkButton11->setVisible(false);
    ui->commandLinkButton12->setVisible(false);
    ui->commandLinkButton13->setVisible(false);
    ui->commandLinkButton14->setVisible(false);
    ui->commandLinkButton15->setVisible(false);
    ui->commandLinkButton16->setVisible(false);
    ui->commandLinkButton17->setVisible(false);
    ui->commandLinkButton18->setVisible(false);
    ui->commandLinkButton19->setVisible(false);
    ui->commandLinkButton20->setVisible(false);


    ui->textBrowser_12->setText(
        "<h2>🇪🇬 Egypt</h2>"
        "<p><b>Flag:</b> 🇪🇬</p>"
        "<p><b>Capital:</b> Cairo</p>"
        "<p><b>History:</b> Home of the pyramids and Sphinx</p>"
        "<p><b>River:</b> Nile – longest river in the world</p>"
        "<p><b>Fun fact:</b> Cleopatra was Greek (Ptolemaic dynasty)</p>"
        "<p><b>Animal love:</b> Ancient Egyptians worshipped cats</p>"
        );
}
void MapPage::on_commandLinkButton13_clicked()
{
    clickPlayer->play();

    ui->textBrowser_13->setVisible(true);
    ui->backToMapButton->setVisible(true);
    ui->enterGameButton->setVisible(false);
    ui->returnToMenuButton->setVisible(false);

    ui->commandLinkButton->setVisible(false);
    ui->commandLinkButton2->setVisible(false);
    ui->commandLinkButton3->setVisible(false);
    ui->commandLinkButton4->setVisible(false);
    ui->commandLinkButton5->setVisible(false);
    ui->commandLinkButton6->setVisible(false);
    ui->commandLinkButton7->setVisible(false);
    ui->commandLinkButton8->setVisible(false);
    ui->commandLinkButton9->setVisible(false);
    ui->commandLinkButton10->setVisible(false);
    ui->commandLinkButton11->setVisible(false);
    ui->commandLinkButton12->setVisible(false);
    ui->commandLinkButton13->setVisible(false);
    ui->commandLinkButton14->setVisible(false);
    ui->commandLinkButton15->setVisible(false);
    ui->commandLinkButton16->setVisible(false);
    ui->commandLinkButton17->setVisible(false);
    ui->commandLinkButton18->setVisible(false);
    ui->commandLinkButton19->setVisible(false);
    ui->commandLinkButton20->setVisible(false);


    ui->textBrowser_13->setText(
        "<h2>🇧🇷 Brazil</h2>"
        "<p><b>Flag:</b> 🇧🇷</p>"
        "<p><b>Capital:</b> Brasília</p>"
        "<p><b>Nature:</b> Amazon – largest tropical rainforest</p>"
        "<p><b>Sports:</b> Most FIFA World Cup wins (5)</p>"
        "<p><b>Landmark:</b> Christ the Redeemer statue – 98 feet tall</p>"
        "<p><b>Scary spot:</b> Snake Island (Ilha da Queimada Grande)</p>"
        );
}
void MapPage::on_commandLinkButton14_clicked()
{
    clickPlayer->play();

    ui->textBrowser_14->setVisible(true);
    ui->backToMapButton->setVisible(true);
    ui->enterGameButton->setVisible(false);
    ui->returnToMenuButton->setVisible(false);

    ui->commandLinkButton->setVisible(false);
    ui->commandLinkButton2->setVisible(false);
    ui->commandLinkButton3->setVisible(false);
    ui->commandLinkButton4->setVisible(false);
    ui->commandLinkButton5->setVisible(false);
    ui->commandLinkButton6->setVisible(false);
    ui->commandLinkButton7->setVisible(false);
    ui->commandLinkButton8->setVisible(false);
    ui->commandLinkButton9->setVisible(false);
    ui->commandLinkButton10->setVisible(false);
    ui->commandLinkButton11->setVisible(false);
    ui->commandLinkButton12->setVisible(false);
    ui->commandLinkButton13->setVisible(false);
    ui->commandLinkButton14->setVisible(false);
    ui->commandLinkButton15->setVisible(false);
    ui->commandLinkButton16->setVisible(false);
    ui->commandLinkButton17->setVisible(false);
    ui->commandLinkButton18->setVisible(false);
    ui->commandLinkButton19->setVisible(false);
    ui->commandLinkButton20->setVisible(false);


    ui->textBrowser_14->setText(
        "<h2>🇦🇷 Argentina</h2>"
        "<p><b>Flag:</b> 🇦🇷</p>"
        "<p><b>Capital:</b> Buenos Aires</p>"
        "<p><b>Culture:</b> Birthplace of tango</p>"
        "<p><b>Geography:</b> Ushuaia – one of the southernmost cities</p>"
        "<p><b>Food:</b> Famous for beef and Mendoza wine</p>"
        "<p><b>Weird event:</b> Had 5 presidents in 10 days (2001)</p>"
        );
}
void MapPage::on_commandLinkButton15_clicked()
{
    clickPlayer->play();

    ui->textBrowser_15->setVisible(true);
    ui->backToMapButton->setVisible(true);
    ui->enterGameButton->setVisible(false);
    ui->returnToMenuButton->setVisible(false);

    ui->commandLinkButton->setVisible(false);
    ui->commandLinkButton2->setVisible(false);
    ui->commandLinkButton3->setVisible(false);
    ui->commandLinkButton4->setVisible(false);
    ui->commandLinkButton5->setVisible(false);
    ui->commandLinkButton6->setVisible(false);
    ui->commandLinkButton7->setVisible(false);
    ui->commandLinkButton8->setVisible(false);
    ui->commandLinkButton9->setVisible(false);
    ui->commandLinkButton10->setVisible(false);
    ui->commandLinkButton11->setVisible(false);
    ui->commandLinkButton12->setVisible(false);
    ui->commandLinkButton13->setVisible(false);
    ui->commandLinkButton14->setVisible(false);
    ui->commandLinkButton15->setVisible(false);
    ui->commandLinkButton16->setVisible(false);
    ui->commandLinkButton17->setVisible(false);
    ui->commandLinkButton18->setVisible(false);
    ui->commandLinkButton19->setVisible(false);
    ui->commandLinkButton20->setVisible(false);


    ui->textBrowser_15->setText(
        "<h2>🇲🇽 Mexico</h2>"
        "<p><b>Flag:</b> 🇲🇽</p>"
        "<p><b>Capital:</b> Mexico City</p>"
        "<p><b>Origin:</b> Chocolate – gift of the Aztecs</p>"
        "<p><b>Ancient cultures:</b> Maya and Aztec civilizations</p>"
        "<p><b>Landmark:</b> Great Pyramid of Cholula – largest by volume</p>"
        "<p><b>Unique animal:</b> Volcano rabbit – native to Mexico</p>"
        );
}
void MapPage::on_commandLinkButton16_clicked()
{
    clickPlayer->play();

    ui->textBrowser_16->setVisible(true);
    ui->backToMapButton->setVisible(true);
    ui->enterGameButton->setVisible(false);
    ui->returnToMenuButton->setVisible(false);

    ui->commandLinkButton->setVisible(false);
    ui->commandLinkButton2->setVisible(false);
    ui->commandLinkButton3->setVisible(false);
    ui->commandLinkButton4->setVisible(false);
    ui->commandLinkButton5->setVisible(false);
    ui->commandLinkButton6->setVisible(false);
    ui->commandLinkButton7->setVisible(false);
    ui->commandLinkButton8->setVisible(false);
    ui->commandLinkButton9->setVisible(false);
    ui->commandLinkButton10->setVisible(false);
    ui->commandLinkButton11->setVisible(false);
    ui->commandLinkButton12->setVisible(false);
    ui->commandLinkButton13->setVisible(false);
    ui->commandLinkButton14->setVisible(false);
    ui->commandLinkButton15->setVisible(false);
    ui->commandLinkButton16->setVisible(false);
    ui->commandLinkButton17->setVisible(false);
    ui->commandLinkButton18->setVisible(false);
    ui->commandLinkButton19->setVisible(false);
    ui->commandLinkButton20->setVisible(false);


    ui->textBrowser_16->setText(
        "<h2>🇺🇸 USA</h2>"
        "<p><b>Flag:</b> 🇺🇸</p>"
        "<p><b>Capital:</b> Washington, D.C.</p>"
        "<p><b>States:</b> 50 states, 330+ million people</p>"
        "<p><b>Historic event:</b> First moon landing (1969)</p>"
        "<p><b>Independence:</b> Declaration signed in 1776</p>"
        "<p><b>Weird place:</b> Barrow, Alaska – 65 days of darkness</p>"
        );
}
void MapPage::on_commandLinkButton17_clicked()
{
    clickPlayer->play();

    ui->textBrowser_17->setVisible(true);
    ui->backToMapButton->setVisible(true);
    ui->enterGameButton->setVisible(false);
    ui->returnToMenuButton->setVisible(false);

    ui->commandLinkButton->setVisible(false);
    ui->commandLinkButton2->setVisible(false);
    ui->commandLinkButton3->setVisible(false);
    ui->commandLinkButton4->setVisible(false);
    ui->commandLinkButton5->setVisible(false);
    ui->commandLinkButton6->setVisible(false);
    ui->commandLinkButton7->setVisible(false);
    ui->commandLinkButton8->setVisible(false);
    ui->commandLinkButton9->setVisible(false);
    ui->commandLinkButton10->setVisible(false);
    ui->commandLinkButton11->setVisible(false);
    ui->commandLinkButton12->setVisible(false);
    ui->commandLinkButton13->setVisible(false);
    ui->commandLinkButton14->setVisible(false);
    ui->commandLinkButton15->setVisible(false);
    ui->commandLinkButton16->setVisible(false);
    ui->commandLinkButton17->setVisible(false);
    ui->commandLinkButton18->setVisible(false);
    ui->commandLinkButton19->setVisible(false);
    ui->commandLinkButton20->setVisible(false);


    ui->textBrowser_17->setText(
        "<h2>🇨🇦 Canada</h2>"
        "<p><b>Flag:</b> 🇨🇦</p>"
        "<p><b>Capital:</b> Ottawa</p>"
        "<p><b>Size:</b> Second-largest country by land area</p>"
        "<p><b>Culture:</b> Maple syrup, hockey, politeness</p>"
        "<p><b>Geography:</b> Longest coastline in the world</p>"
        "<p><b>Fun fail:</b> Tried ketchup-flavored soda (didn't work)</p>"
        );
}
void MapPage::on_commandLinkButton18_clicked()
{
    clickPlayer->play();

    ui->textBrowser_18->setVisible(true);
    ui->backToMapButton->setVisible(true);
    ui->enterGameButton->setVisible(false);
    ui->returnToMenuButton->setVisible(false);

    ui->commandLinkButton->setVisible(false);
    ui->commandLinkButton2->setVisible(false);
    ui->commandLinkButton3->setVisible(false);
    ui->commandLinkButton4->setVisible(false);
    ui->commandLinkButton5->setVisible(false);
    ui->commandLinkButton6->setVisible(false);
    ui->commandLinkButton7->setVisible(false);
    ui->commandLinkButton8->setVisible(false);
    ui->commandLinkButton9->setVisible(false);
    ui->commandLinkButton10->setVisible(false);
    ui->commandLinkButton11->setVisible(false);
    ui->commandLinkButton12->setVisible(false);
    ui->commandLinkButton13->setVisible(false);
    ui->commandLinkButton14->setVisible(false);
    ui->commandLinkButton15->setVisible(false);
    ui->commandLinkButton16->setVisible(false);
    ui->commandLinkButton17->setVisible(false);
    ui->commandLinkButton18->setVisible(false);
    ui->commandLinkButton19->setVisible(false);
    ui->commandLinkButton20->setVisible(false);


    ui->textBrowser_18->setText(
        "<h2>🇬🇱 Greenland</h2>"
        "<p><b>Flag:</b> 🇬🇱</p>"
        "<p><b>Capital:</b> Nuuk</p>"
        "<p><b>Status:</b> Autonomous territory of Denmark</p>"
        "<p><b>Climate:</b> Mostly ice-covered</p>"
        "<p><b>Transport:</b> No roads between towns – use boats, sleds, planes</p>"
        "<p><b>Sunlight:</b> Weeks of darkness or daylight depending on season</p>"
        );
}
void MapPage::on_commandLinkButton19_clicked()
{
    clickPlayer->play();

    ui->textBrowser_19->setVisible(true);
    ui->backToMapButton->setVisible(true);
    ui->enterGameButton->setVisible(false);
    ui->returnToMenuButton->setVisible(false);

    ui->commandLinkButton->setVisible(false);
    ui->commandLinkButton2->setVisible(false);
    ui->commandLinkButton3->setVisible(false);
    ui->commandLinkButton4->setVisible(false);
    ui->commandLinkButton5->setVisible(false);
    ui->commandLinkButton6->setVisible(false);
    ui->commandLinkButton7->setVisible(false);
    ui->commandLinkButton8->setVisible(false);
    ui->commandLinkButton9->setVisible(false);
    ui->commandLinkButton10->setVisible(false);
    ui->commandLinkButton11->setVisible(false);
    ui->commandLinkButton12->setVisible(false);
    ui->commandLinkButton13->setVisible(false);
    ui->commandLinkButton14->setVisible(false);
    ui->commandLinkButton15->setVisible(false);
    ui->commandLinkButton16->setVisible(false);
    ui->commandLinkButton17->setVisible(false);
    ui->commandLinkButton18->setVisible(false);
    ui->commandLinkButton19->setVisible(false);
    ui->commandLinkButton20->setVisible(false);


    ui->textBrowser_19->setText(
        "<h2>🇳🇴 Norway</h2>"
        "<p><b>Flag:</b> 🇳🇴</p>"
        "<p><b>Capital:</b> Oslo</p>"
        "<p><b>Nature:</b> Famous fjords</p>"
        "<p><b>Energy:</b> Runs mostly on hydropower</p>"
        "<p><b>Peace:</b> Hosts Nobel Peace Prize ceremony</p>"
        "<p><b>TV trend:</b> Slow TV – people watch knitting or train rides</p>"
        );
}
void MapPage::on_commandLinkButton20_clicked()
{
    clickPlayer->play();

    ui->textBrowser_20->setVisible(true);
    ui->backToMapButton->setVisible(true);
    ui->enterGameButton->setVisible(false);
    ui->returnToMenuButton->setVisible(false);

    ui->commandLinkButton->setVisible(false);
    ui->commandLinkButton2->setVisible(false);
    ui->commandLinkButton3->setVisible(false);
    ui->commandLinkButton4->setVisible(false);
    ui->commandLinkButton5->setVisible(false);
    ui->commandLinkButton6->setVisible(false);
    ui->commandLinkButton7->setVisible(false);
    ui->commandLinkButton8->setVisible(false);
    ui->commandLinkButton9->setVisible(false);
    ui->commandLinkButton10->setVisible(false);
    ui->commandLinkButton11->setVisible(false);
    ui->commandLinkButton12->setVisible(false);
    ui->commandLinkButton13->setVisible(false);
    ui->commandLinkButton14->setVisible(false);
    ui->commandLinkButton15->setVisible(false);
    ui->commandLinkButton16->setVisible(false);
    ui->commandLinkButton17->setVisible(false);
    ui->commandLinkButton18->setVisible(false);
    ui->commandLinkButton19->setVisible(false);
    ui->commandLinkButton20->setVisible(false);


    ui->textBrowser_20->setText(
        "<h2>🇮🇩 Indonesia</h2>"
        "<p><b>Flag:</b> 🇮🇩</p>"
        "<p><b>Capital:</b> Jakarta</p>"
        "<p><b>Geography:</b> Largest island nation – over 17,000 islands</p>"
        "<p><b>Wildlife:</b> Home to Komodo dragons</p>"
        "<p><b>Population:</b> Fourth most populous country</p>"
        "<p><b>Volcanoes:</b> More active volcanoes than anywhere else – 120+</p>"
        );
}

void MapPage::on_backToMapButton_clicked()
{
    clickPlayer->play();

    ui->backToMapButton->setVisible(false);
    ui->enterGameButton->setVisible(true);
    ui->returnToMenuButton->setVisible(true);

    ui->commandLinkButton->setVisible(true);
    ui->commandLinkButton2->setVisible(true);
    ui->commandLinkButton3->setVisible(true);
    ui->commandLinkButton4->setVisible(true);
    ui->commandLinkButton5->setVisible(true);
    ui->commandLinkButton6->setVisible(true);
    ui->commandLinkButton7->setVisible(true);
    ui->commandLinkButton8->setVisible(true);
    ui->commandLinkButton9->setVisible(true);
    ui->commandLinkButton10->setVisible(true);
    ui->commandLinkButton11->setVisible(true);
    ui->commandLinkButton12->setVisible(true);
    ui->commandLinkButton13->setVisible(true);
    ui->commandLinkButton14->setVisible(true);
    ui->commandLinkButton15->setVisible(true);
    ui->commandLinkButton16->setVisible(true);
    ui->commandLinkButton17->setVisible(true);
    ui->commandLinkButton18->setVisible(true);
    ui->commandLinkButton19->setVisible(true);
    ui->commandLinkButton20->setVisible(true);

    ui->textBrowser->setVisible(false);
    ui->textBrowser_2->setVisible(false);
    ui->textBrowser_3->setVisible(false);
    ui->textBrowser_4->setVisible(false);
    ui->textBrowser_5->setVisible(false);
    ui->textBrowser_6->setVisible(false);
    ui->textBrowser_7->setVisible(false);
    ui->textBrowser_8->setVisible(false);
    ui->textBrowser_9->setVisible(false);
    ui->textBrowser_10->setVisible(false);
    ui->textBrowser_11->setVisible(false);
    ui->textBrowser_12->setVisible(false);
    ui->textBrowser_13->setVisible(false);
    ui->textBrowser_14->setVisible(false);
    ui->textBrowser_15->setVisible(false);
    ui->textBrowser_16->setVisible(false);
    ui->textBrowser_17->setVisible(false);
    ui->textBrowser_18->setVisible(false);
    ui->textBrowser_19->setVisible(false);
    ui->textBrowser_20->setVisible(false);

}
