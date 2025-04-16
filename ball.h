#ifndef BALL_H
#define BALL_H

#include <Box2D/Box2D.h>
#include <QPainter>
#include <QPointF>

class Ball {
public:
    Ball(b2World* world);
    ~Ball();

    void draw(QPainter& painter);   // Render/draw ball
    void setVelocity(const QPointF& velocity);  // Used to control the movement of the ball; simulates physics
    void resetPosition();   // Reset the position of the ball to startPosition
    b2Body* getBody() const { return body; }


    void launch();
    //void handleCollision(GameObject* other);

private:
    b2Body* body;   // Ball's physics body
    QPointF startPosition;   // Start position of ball, adjust values accordingly
    QPixmap sprite;
};

#endif // BALL_H
