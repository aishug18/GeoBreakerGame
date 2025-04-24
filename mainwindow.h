#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Represents the main menu window for the game, allowing navigation to the map and tutorial pages.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * Constructs the MainWindow and sets up the UI, music, and button events.
     * @param parent Optional parent widget.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * Destructor. Cleans up UI resources.
     */
    ~MainWindow();

private:
    Ui::MainWindow *ui;     //Pointer to the UI layout
    QMediaPlayer *musicPlayer;  //Background music player
    QAudioOutput *audioOutput;  //Audio output device for background music

    QMediaPlayer *clickPlayer1;    //Click sound effect player
    QAudioOutput *clickAudio1;     //Audio output device for click sounds
};
#endif // MAINWINDOW_H
