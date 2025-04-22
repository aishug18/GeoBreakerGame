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

class GamePage : public QWidget {
    Q_OBJECT
    friend class ContactListener;

public:
    explicit GamePage(QWidget *parent = nullptr);
    ~GamePage();

    void addTime(int secs);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void onTimerTick();
    void homeButtonClicked();
    void mapButtonClicked();

signals:
    void scoreChanged(int newScore);

private:
    Ui::GamePage* ui;
    b2World* world;
    ContactListener* contactListener;
    Ball* ball;
    std::vector<Brick*> bricks;
    std::vector<Wall*> walls;
    b2Body* platformBody;

    std::mt19937 rng;
    RoundState roundState;
    int currentFactIndex;
    struct CountryInfo { QString name, capital; QList<QString> facts; };
    QList<CountryInfo> allCountries, selectedCountries;
    CountryInfo targetCountry;

    int score, correctCount, wrongCount;
    QTimer* countdownTimer;
    int remainingTime;

    QMediaPlayer *gameMusicPlayer, *clickPlayer, *correctPlayer, *wrongPlayer;
    QAudioOutput *gameAudioOutput, *clickAudio, *correctAudio, *wrongAudio;

    QPointF aimStart, aimEnd;

    void setupObjects();
    void setupRoundOne();
    void setupRoundTwo();
    void populateCountryData();
    // void setupCountrySpecificRound();
    void destroyAllBricks();
    void updatePhysics();
    void handleContact(b2Body* A, b2Body* B);

    std::vector<Brick*> pendingDestroy;
    void drawGame(QPainter& painter);
    void drawPlatform(QPainter& painter);
    void drawReflectedLine(QPainter& p, const QPointF& A, const QPointF& B);
    void endGame();

    void playCorrectSound() { correctPlayer->play(); }
    void playWrongSound()   { wrongPlayer->play();   }
};

#endif // GAMEPAGE_H
