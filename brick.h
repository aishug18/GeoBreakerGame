#ifndef BRICK_H
#define BRICK_H

#include <QString>
#include <QRectF>
#include <QPainter>
#include <Box2D/Box2D.h>

enum class BrickType { Normal, TimeBonus };

class GamePage;  // forward

class Brick {
public:
    // now takes both “correct?” and “power‑up type”
    Brick(b2World* world,
          const QPointF& positionPx,
          const QString& labelText,
          bool isCorrect,
          BrickType type = BrickType::Normal);
    virtual ~Brick();

    b2Body*        getBody() const;
    bool           isCorrectAnswer() const;
    BrickType      getType() const;
    virtual void   onHit(GamePage* gp);
    void           draw(QPainter& painter);
    void           destroy();

private:
    BrickType m_type;
    bool      correct;
    QString   m_text;
    QRectF    m_rect;
    b2Body*   body = nullptr;
};

#endif // BRICK_H
