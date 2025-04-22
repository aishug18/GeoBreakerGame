#include "wall.h"
#include <QPainter>

static constexpr float PTM = 30.0f;

Wall::Wall(b2World* world, const QRectF& rectPx) {
    m_rect = rectPx;

    float x = rectPx.x()/PTM, y = rectPx.y()/PTM;
    float w = rectPx.width()/PTM, h = rectPx.height()/PTM;

    b2BodyDef bd;
    bd.type = b2_staticBody;
    bd.position.Set(x + w/2, y + h/2);
    body = world->CreateBody(&bd);

    b2PolygonShape box;
    box.SetAsBox(w/2, h/2);

    b2FixtureDef fd;
    fd.shape       = &box;
    fd.density     = 0.0f;
    fd.friction    = 0.3f;
    fd.restitution = 1.0f;   // **FULL** bounce
    body->CreateFixture(&fd);
}

Wall::~Wall() {
    if (body && body->GetWorld())
        body->GetWorld()->DestroyBody(body);
}

void Wall::draw(QPainter& painter) {
    painter.save();
    painter.setBrush(Qt::darkGray);
    painter.setPen(Qt::NoPen);
    painter.drawRect(m_rect);
    painter.restore();
}
