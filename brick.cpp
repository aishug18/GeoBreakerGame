#include "brick.h"
#include "gamepage.h"
#include <QPainter>
#include <QColor>
#include <QFont>

// pixels‑to‑meters ratio
static constexpr float PTM = 30.0f;

Brick::Brick(b2World* world,
             const QPointF& positionPx,
             const QString& labelText,
             bool isCorrect,
             BrickType type)
    : m_type(type)
    , correct(isCorrect)
    , m_text(labelText)
{
    const float W = 120.0f, H = 40.0f;
    m_rect = QRectF(positionPx.x() - W/2, positionPx.y() - H/2, W, H);

    float x = positionPx.x()/PTM, y = positionPx.y()/PTM;
    float w = W/PTM,          h = H/PTM;

    b2BodyDef bd;
    bd.type     = b2_staticBody;
    bd.position.Set(x, y);
    body = world->CreateBody(&bd);

    b2PolygonShape box;
    box.SetAsBox(w/2, h/2);

    b2FixtureDef fd;
    fd.shape       = &box;
    fd.density     = 0.0f;
    fd.friction    = 0.3f;
    fd.restitution = 0.5f;   // standard brick bounce
    body->CreateFixture(&fd);
}

Brick::~Brick() {
    destroy();
}

b2Body* Brick::getBody() const {
    return body;
}

bool Brick::isCorrectAnswer() const {
    return correct;
}

BrickType Brick::getType() const {
    return m_type;
}

void Brick::onHit(GamePage* gp) {
    if (m_type == BrickType::TimeBonus) {
        gp->addTime(10);   // +10 seconds
    }
    // else: scoring handled in GamePage
}

void Brick::draw(QPainter& painter) {
    painter.save();
    painter.setBrush(QColor(139,69,19));  // uniform wood look
    painter.setPen(Qt::black);
    painter.drawRect(m_rect);

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial",12,QFont::Bold));
    painter.drawText(m_rect, Qt::AlignCenter, m_text);
    painter.restore();
}

void Brick::destroy() {
    if (body && body->GetWorld()) {
        body->GetWorld()->DestroyBody(body);
        body = nullptr;
    }
}
