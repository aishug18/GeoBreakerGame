#include "ball.h"
#include <Box2D/Box2D.h>
#include <QPainter>
#include <QRadialGradient>
#include <cmath>

// pixels‑to‑meters ratio
static constexpr float PTM = 30.0f;

Ball::Ball(b2World* world)
    : startPosition(400.0f, 675.0f)
{
    b2BodyDef bd;
    bd.type   = b2_dynamicBody;
    bd.bullet = true;
    bd.position.Set(startPosition.x() / PTM,
                    startPosition.y() / PTM);
    body = world->CreateBody(&bd);

    b2CircleShape circle;
    circle.m_radius = radius / PTM;

    b2FixtureDef fd;
    fd.shape       = &circle;
    fd.density     = 1.0f;
    fd.friction    = 0.0f;
    fd.restitution = 0.9f;
    body->CreateFixture(&fd);

    body->SetLinearDamping(0.1f);
    body->SetAngularDamping(0.1f);
}

Ball::~Ball() {
    if (body && body->GetWorld()) {
        body->GetWorld()->DestroyBody(body);
    }
}

void Ball::draw(QPainter& painter) {
    // physics (m) → screen (px)
    b2Vec2  posM = body->GetPosition();
    QPointF posPx(posM.x * PTM, posM.y * PTM);

    QRadialGradient grad(posPx, radius);
    grad.setColorAt(0.0, QColor(255,255,255));
    grad.setColorAt(0.3, Qt::red);
    grad.setColorAt(1.0, Qt::darkRed);

    painter.save();
    painter.setBrush(grad);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(posPx, radius, radius);
    painter.restore();
}

void Ball::setVelocity(const QPointF& velocityPx) {
    // convert px/s → m/s
    b2Vec2 velM(velocityPx.x() / PTM,
                velocityPx.y() / PTM);
    body->SetLinearVelocity(velM);
}

void Ball::resetPosition() {
    body->SetTransform(
        b2Vec2(startPosition.x()/PTM,
               startPosition.y()/PTM),
        0.0f
        );
    body->SetLinearVelocity(b2Vec2(0,0));
    body->SetAngularVelocity(0);
}
