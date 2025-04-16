#include "ball.h"
#include <Box2D/Box2D.h>
#include <cstdint>

Ball::Ball(b2World* world) : startPosition(400.0f, 600.0f) {
    // Define and create the ball's physics body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(startPosition.x(), startPosition.y());
    bodyDef.bullet = true;  // Treats the object as a high speed collision
    body = world->CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = 10.0f;  // Ball radius, adjust accordingly

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
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
    painter.setBrush(Qt::red);  // Adjust color of ball
    painter.drawEllipse(position, 10.0, 10.0);  // adjust radius if needed
}

void Ball::setVelocity(const QPointF& velocity) {
    if(body) {
        body->SetLinearVelocity(b2Vec2(velocity.x(), velocity.y()));
    }
}

void Ball::resetPosition() {
    body->SetTransform(b2Vec2(startPosition.x(), startPosition.y()), 0.0f);
    body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));    // Stop movement
}



void Ball::launch() {
    if (body) {
        body->ApplyLinearImpulse(
            b2Vec2(0.5f, -5.0f),
            body->GetWorldCenter(),
            true
            );
    }
}

// void Ball::handleCollision(GameObject* other) {
//     // Collision handling logic
//     other->getBody();
// }

