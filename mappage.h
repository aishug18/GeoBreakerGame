#ifndef MAPPAGE_H
#define MAPPAGE_H

#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>

namespace Ui {
class MapPage;
}

class MapPage : public QWidget
{
    Q_OBJECT

public:
    explicit MapPage(QWidget *parent = nullptr);
    ~MapPage();

private:
    Ui::MapPage *ui;
    QMediaPlayer *mapMusicPlayer;
    QAudioOutput *mapAudioOutput;

    QMediaPlayer *clickPlayer;
    QAudioOutput *clickAudio;

private slots:
    void on_enterGameButton_clicked();
    void on_returnToMenuButton_clicked();
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
    void on_backToMapButton_clicked();
};


#endif // MAPPAGE_H
