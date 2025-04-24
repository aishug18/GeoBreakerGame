#ifndef WALL_H
#define WALL_H

#include <QRectF>
#include <Box2D/Box2D.h>
#include <QPixmap>

class QPainter;

/**
 * @class Wall
 * @brief Represents a static wall in the game world with a physics body and textured appearance.
 */
class Wall {
public:
    /**
     * @brief Constructs a Wall and adds it to the Box2D world.
     * @param world Pointer to the Box2D world.
     * @param rect Rectangle defining the wall's position and size in pixels.
     */
    Wall(b2World* world, const QRectF& rect);

    /**
     * Destructor. Removes the wall body from the Box2D world.
     */
    ~Wall();

    /**
     * Draws the wall with a textured sprite using a QPainter.
     * @param painter The QPainter used to render the wall.
     */
    void draw(QPainter& painter);

    /**
     * Gets the Box2D physics body for the wall.
     * @return Pointer to the b2Body object.
     */
    b2Body* getBody() const { return body; }

private:
    b2Body* body;   //Box2D body representing the wall in the physics world
    QRectF m_rect;  //Rectangle used for drawing the wall
    QPixmap sprite; //Texture used to render the wall visually
};

#endif // WALL_H
