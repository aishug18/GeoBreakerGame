#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <random>
#include "brick.h"
#include "ball.h"
#include "wall.h"

enum class RoundState { MultipleChoice, TrueFalse };

namespace Ui { class GamePage; }

class ContactListener;

/**
 * @class GamePage
 * @brief Main gameplay window. Manages game objects, physics, timer, rounds, scoring, and UI.
 */
class GamePage : public QWidget {
    Q_OBJECT
    friend class ContactListener;

public:
    /**
     * Constructs the GamePage and initializes the game.
     * @param parent Parent QWidget.
     */
    explicit GamePage(QWidget *parent = nullptr);

    /**
     * Destructor. Cleans up dynamically allocated resources.
     */
    ~GamePage();

    /**
     * Adds additional seconds to the game timer.
     * @param secs Number of seconds to add.
     */
    void addTime(int secs);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    /**
     * Called every second to update the countdown timer.
     */
    void onTimerTick();

    /**
     * Triggered when Home button is clicked.
     */
    void homeButtonClicked();

    /**
     * Triggered when Map button is clicked.
     */
    void mapButtonClicked();

signals:
    /**
     * Signal emitted when the score is changed.
     * @param newScore New score value.
     */
    void scoreChanged(int newScore);

private:
    Ui::GamePage* ui;   //Pointer to UI
    b2World* world;     //Box2D physics world
    ContactListener* contactListener;   //Handles collision detection
    Ball* ball;     //Player ball
    std::vector<Brick*> bricks;     //Active bricks
    std::vector<Wall*> walls;   //Static walls
    b2Body* platformBody;   //Platform physics body

    std::mt19937 rng;   //Random number generator
    RoundState roundState;  //Current round mode
    int currentFactIndex;   //Index of current fact
    struct CountryInfo { QString name, capital; QList<QString> facts; };
    QList<CountryInfo> allCountries, selectedCountries;
    CountryInfo targetCountry;

    int score, correctCount, wrongCount;    //Score and performance counters
    QTimer* countdownTimer;     //Game countdown timer
    int remainingTime;  //Remaining seconds

    QMediaPlayer *gameMusicPlayer, *clickPlayer, *correctPlayer, *wrongPlayer;
    QAudioOutput *gameAudioOutput, *clickAudio, *correctAudio, *wrongAudio;

    QPointF aimStart, aimEnd;   //Mouse aiming positions

    void setupObjects();
    void setupRoundOne();
    void setupRoundTwo();
    void populateCountryData();
    void destroyAllBricks();
    void updatePhysics();
    void handleContact(b2Body* A, b2Body* B);

    std::vector<Brick*> pendingDestroy;     //Bricks scheduled for destruction
    void drawGame(QPainter& painter);
    void drawPlatform(QPainter& painter);
    void drawReflectedLine(QPainter& p, const QPointF& A, const QPointF& B);
    void endGame();

    void playCorrectSound() { correctPlayer->play(); }
    void playWrongSound()   { wrongPlayer->play();   }
};

#endif // GAMEPAGE_H
