#include "ball.h"
#include <Box2D/Box2D.h>
#include <cstdint>

Ball::Ball(b2World* world) : startPosition(400.0f, 675.0f) {
    // Define and create the ball's physics body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(startPosition.x(), startPosition.y());
    bodyDef.bullet = true;  // Treats the object as a high speed collision
    body = world->CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = radius;  // Ball radius, adjust accordingly

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.1f;
    fixtureDef.friction = 0.1f;
    fixtureDef.restitution = 1.0f;  // Bouncy ball
    body->CreateFixture(&fixtureDef);
}

Ball::~Ball() {
    if (body && body->GetWorld()) {
        body->GetWorld()->DestroyBody(body);
    }
}

void Ball::draw(QPainter& painter) {
    // Render ball based on physics body's position
    QPointF position(body->GetPosition().x, body->GetPosition().y);

    QRadialGradient gradient(position, radius);
    gradient.setColorAt(0, QColor(255, 255, 255));
    gradient.setColorAt(0.3, Qt::red);
    gradient.setColorAt(1, Qt::darkRed);

    painter.save();
    painter.setBrush(gradient);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(position, radius, radius);
    painter.restore();
}

void Ball::setVelocity(const QPointF& velocity) {
    body->SetLinearVelocity(b2Vec2(velocity.x(), velocity.y()));
}

void Ball::resetPosition() {
    body->SetTransform(b2Vec2(startPosition.x(), startPosition.y()), 0.0f);
    body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));    // Stop movement
}
