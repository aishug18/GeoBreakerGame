#ifndef BRICK_H
#define BRICK_H

#include <Box2D/Box2D.h>
#include <QString>
#include <QPointF>
#include <QPainter>

class Brick {
public:
    Brick(b2World* world, const QPointF& position, const QString& answer, bool isCorrect);
    ~Brick();

    void draw(QPainter& painter);
    void destroy(); // brick is destroyed, add some animations
    bool isCorrectAnswer() const { return correct; }
    b2Body* getBody() const { return body; }

    // do we need these?
    //void handleCollision(GameObject* other);
    bool isMarkedForDestruction() const { return markedForDestruction; }

private:
    b2Body* body;   // Brick's physics body
    QString answer; // The answer on the brick
    bool correct;   // Whether this brick has the correct answer
    QPixmap sprite; // Sprite for the brick

    // do we need this
    bool markedForDestruction = false;
};

#endif // BRICK_H
