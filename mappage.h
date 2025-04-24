#ifndef MAPPAGE_H
#define MAPPAGE_H

#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>

namespace Ui {
class MapPage;
}

/**
 * @class MapPage
 * @brief Represents the world map screen where users select countries to view facts or start the game.
 */
class MapPage : public QWidget
{
    Q_OBJECT

public:
    /**
     * Constructs the MapPage and sets up music, button styles, and pins.
     * @param parent Optional parent widget.
     */
    explicit MapPage(QWidget *parent = nullptr);

    /**
     * Destructor. Cleans up UI resources.
     */
    ~MapPage();

private:
    Ui::MapPage *ui;    //Pointer to the UI
    QMediaPlayer *mapMusicPlayer;   //Background music player
    QAudioOutput *mapAudioOutput;   //Audio output device for music

    QMediaPlayer *clickPlayer;  //Click sound effect player
    QAudioOutput *clickAudio;   //Audio output device for clicks

private slots:
    /**
     * @brief Triggered when entering the game.
     */
    void on_enterGameButton_clicked();

    /**
     * @brief Triggered when returning to the main menu.
     */
    void on_returnToMenuButton_clicked();

    /**
     * @brief Shows fact popup for country 1 to 20.
     */
    void on_commandLinkButton_clicked();
    void on_commandLinkButton2_clicked();
    void on_commandLinkButton3_clicked();
    void on_commandLinkButton4_clicked();
    void on_commandLinkButton5_clicked();
    void on_commandLinkButton6_clicked();
    void on_commandLinkButton7_clicked();
    void on_commandLinkButton8_clicked();
    void on_commandLinkButton9_clicked();
    void on_commandLinkButton10_clicked();
    void on_commandLinkButton11_clicked();
    void on_commandLinkButton12_clicked();
    void on_commandLinkButton13_clicked();
    void on_commandLinkButton14_clicked();
    void on_commandLinkButton15_clicked();
    void on_commandLinkButton16_clicked();
    void on_commandLinkButton17_clicked();
    void on_commandLinkButton18_clicked();
    void on_commandLinkButton19_clicked();
    void on_commandLinkButton20_clicked();

    /**
     * @brief Returns the user to the full map view from a country detail.
     */
    void on_backToMapButton_clicked();
};


#endif // MAPPAGE_H
