#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <vector>
#include "ball.h"
#include "brick.h"
#include "wall.h"

#include "paddle.h"
#include "physicsmanager.h"

namespace Ui {
class GamePage;
}

class GamePage : public QWidget
{
    Q_OBJECT

public:
    explicit GamePage(QWidget *parent = nullptr);
    ~GamePage();
    void startGame();

protected:
    // these are for keyboard inputs, if we want to implement those
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    void paintEvent(QPaintEvent* event) override;   // Draw the scene
    void mousePressEvent(QMouseEvent *event) override;  // User presses the mouse, the aim line should start.
    void mouseMoveEvent(QMouseEvent *event) override;   // User drags the mouse, aim line should move accordingly.
    void mouseReleaseEvent(QMouseEvent *event) override;    // User releases the mouse, aim line should disappear and ball launches.

private slots:
    void updateGame();
    void updateTimer();

private:
    Ui::GamePage *ui;
    b2World* world; // Box2D world
    Ball* ball; // Ball object
    std::vector<Brick*> bricks; // List of Brick objects
    std::vector<Wall*> walls;   // Walls of the game
    b2Body* platformBody;   // Platform object, where the ball rests
    QPointF aimStart;   // Aim start point
    QPointF aimEnd; // Aim end point
    int score;  // Player's score

    QMediaPlayer *gameMusicPlayer;
    QAudioOutput *gameAudioOutput;
    QMediaPlayer *clickPlayer;
    QAudioOutput *clickAudio;


    // other stuff, do we need??
    PhysicsManager* physicsManager = nullptr;
    QTimer* gameLoopTimer = nullptr;
    Paddle* paddle = nullptr;
    QTimer* gameTimer = nullptr;
    //ContactListener* contactListener = nullptr;
    int remainingTime = 15;
    void incrementScore(int points);


    // Methods to set up world and check collisions
    void setupObjects();    // Set up all game objects (bricks, walls, ball)
    void updatePhysics();   // Simulate physics
    void checkCollision(); // Check collisions between the ball and bricks
    void drawGame(QPainter& painter);   // Render game components
    void drawPlatform(QPainter& painter);  // Create a platform where the ball rests

signals:
    void scoreChanged(int newScore);

private slots:
    void homeButtonClicked();
    void mapButtonClicked();
};

#endif // GAMEPAGE_H
