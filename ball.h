#ifndef BALL_H
#define BALL_H

#include <Box2D/Box2D.h>
#include <QPainter>
#include <QPointF>

/**
 * @class Ball
 * @brief Represents the main ball object in the game, including physics, rendering, and control.
 */
class Ball {
public:
    /**
     * Constructs the Ball in the given Box2D world.
     */
    Ball(b2World* world);

    /**
     * Destructor. Removes the body from the Box2D world.
     */
    ~Ball();

    /**
     * Renders the ball using the given QPainter.
     */
    void draw(QPainter& painter);

    /**
     * Sets the ball's velocity (in pixel/s).
     * @param velocity The velocity vector in pixels.
     */
    void setVelocity(const QPointF& velocity);

    /**
     * Resets the ball to its initial starting position with no velocity.
     */
    void resetPosition();

    /**
     * Gets the Box2D body of the ball.
     * @return Pointer to the b2Body object.
     */
    b2Body* getBody() const { return body; }

private:
    b2Body* body;   // Ball's physics body
    QPointF startPosition;   // Start position of ball, adjust values accordingly
    float radius = 15.0f;
    static constexpr float PTM = 30.0f;  // pixels‑to‑meters

};

#endif // BALL_H
