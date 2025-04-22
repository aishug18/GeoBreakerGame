#ifndef WALL_H
#define WALL_H

#include <QRectF>
#include <Box2D/Box2D.h>
#include <QPixmap>

class QPainter;

class Wall {
public:
    Wall(b2World* world, const QRectF& rect);
    ~Wall();

    void draw(QPainter& painter);
    b2Body* getBody() const { return body; }

private:
    b2Body* body;
    QRectF m_rect;  // Add this member variable to store rectangle for drawing
    QPixmap sprite; // Sprite for the wall
};

#endif // WALL_H
