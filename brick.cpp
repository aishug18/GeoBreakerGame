#include "brick.h"

Brick::Brick(b2World* world, const QPointF& position, const QString& answer, bool isCorrect)
    : answer(answer), correct(isCorrect)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;   // Bricks are static
    bodyDef.position.Set(position.x(), position.y());
    body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(30.0f, 15.0f); // Brick dimensions, change accordingly

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    body->CreateFixture(&fixtureDef);
}

Brick::~Brick() {
    if (body && body->GetWorld()) {
        body->GetWorld()->DestroyBody(body);
    }
}

void Brick::draw(QPainter& painter) {
    QPointF position(body->GetPosition().x, body->GetPosition().y); // the center of the brick
    painter.setBrush(Qt::green);    // change color as needed
    painter.drawRect(QRectF(position.x() - 30, position.y() - 15, 60, 30)); // (left, top, width, height)

    painter.setPen(Qt::black);
    painter.drawText(QRectF(position.x() - 30, position.y() - 15, 60, 30), Qt::AlignCenter, answer);
}

void Brick::destroy() {
    // destroy brick with some animations?
    body->GetWorld()->DestroyBody(body);
    body = nullptr;
}


// void Brick::handleCollision(GameObject* other) {
//     if (dynamic_cast<Ball*>(other)) {
//         markedForDestruction = true;
//     }
// }
