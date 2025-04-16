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
};


#endif // MAPPAGE_H
