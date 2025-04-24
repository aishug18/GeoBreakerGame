#ifndef BRICK_H
#define BRICK_H

#include <QString>
#include <QRectF>
#include <QPainter>
#include <Box2D/Box2D.h>

enum class BrickType { Normal, TimeBonus };

class GamePage;  // forward

/**
 * @class Brick
 * @brief Represents an interactive brick object with physics, text, and game logic integration.
 */
class Brick {
public:
    /**
     * @brief Constructs a Brick object with a physics body and text label.
     * @param world Pointer to the Box2D world for body creation.
     * @param positionPx Position of the brick in pixels.
     * @param labelText Text to display on the brick.
     * @param isCorrect Whether this brick represents the correct answer.
     * @param type Type of the brick (normal or time bonus).
     */
    Brick(b2World* world,
          const QPointF& positionPx,
          const QString& labelText,
          bool isCorrect,
          BrickType type = BrickType::Normal);

    /**
     * Destructor. Removes the brick from the physics world.
     */
    virtual ~Brick();

    /**
     * Returns the Box2D body of the brick.
     * @return Pointer to the Box2D body.
     */
    b2Body*        getBody() const;

    /**
     * Indicates whether this brick is the correct answer.
     * @return True if correct, false otherwise.
     */
    bool           isCorrectAnswer() const;

    /**
     * Returns the type of this brick (normal or time bonus).
     * @return Enum value of type BrickType.
     */
    BrickType      getType() const;

    /**
     * Called when the brick is hit. Triggers bonus effects (if any).
     * @param gp Pointer to the game page for context access.
     */
    virtual void   onHit(GamePage* gp);

    /**
     * Renders the brick using the provided painter.
     * @param painter The QPainter used to draw the brick.
     */
    void           draw(QPainter& painter);

    /**
     * Destroys the Box2D body associated with this brick.
     */
    void           destroy();

private:
    BrickType m_type;   //Type of the brick (normal or time bonus)
    bool      correct;  //Whether the brick is a correct answer
    QString   m_text;   //Text displayed on the brick
    QRectF    m_rect;   //Drawing rectangle in pixels
    b2Body*   body = nullptr;   //Pointer to the Box2D body
};

#endif // BRICK_H
