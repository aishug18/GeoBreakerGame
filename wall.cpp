#include "wall.h"

Wall::Wall(b2World* world, const QRectF& rect) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;   // Walls are static
    bodyDef.position.Set(rect.center().x(), rect.center().y());
    body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(rect.width() / 2.0f, rect.height() / 2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.restitution = 1.0f;  // Bouncy walls
    body->CreateFixture(&fixtureDef);

    sprite.load(":/images/assets/wall_sprite.jpg");

}

Wall::~Wall() {
    if (body && body->GetWorld()) {
        body->GetWorld()->DestroyBody(body);
    }
}

void Wall::draw(QPainter& painter) {
    // Get the current position of the wall's physics body
    QPointF position(body->GetPosition().x, body->GetPosition().y); // the center of the wall

    // Get the dimensions of the wall
    b2Fixture* fixture = body->GetFixtureList();
    b2PolygonShape* shape = dynamic_cast<b2PolygonShape*>(fixture->GetShape());

    if(shape) {
        // The Box2D shape stores the half-width and half-height
        float halfWidth = shape->m_vertices[1].x;   // half-width from the shape's vertices
        float halfHeight = shape->m_vertices[2].y;   // half-height from the shape's vertices

        // Now draw the wall

        QRect rect(
            position.x() - halfWidth,   // left
            position.y() - halfHeight,  // top
            halfWidth * 2,              // width
            halfHeight * 2);           // height

        painter.drawPixmap(rect, sprite);   // stretches a lot
    }
}


// void Wall::handleCollision(GameObject* other) {
//     // Probably do nothing or log collision
//     // You can add logic if you want later
//     // make ball bounce
// }



