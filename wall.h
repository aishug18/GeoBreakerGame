#ifndef WALL_H
#define WALL_H

#include <Box2D/Box2D.h>
#include <QPainter>

/*
 * Represents a Wall in the game.
 * If a Ball hits a Wall, the Ball will bounce.
 */
class Wall
{
public:
    Wall(b2World* world, const QRectF& rect);
    ~Wall();

    void draw(QPainter& painter);
    b2Body* getBody() const { return body; }


    //void handleCollision(GameObject* other);

private:
    b2Body* body;   // Wall's physics body
};

#endif // WALL_H
