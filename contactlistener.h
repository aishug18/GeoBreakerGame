#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <Box2D/Box2D.h>
class GamePage;

/**
 * @class ContactListener
 * @brief Custom Box2D contact listener that notifies the GamePage of collision events.
 */
class ContactListener : public b2ContactListener {
public:
    /**
     * Constructs a ContactListener linked to the given GamePage.
     * @param page Pointer to the active GamePage that handles contacts.
     */
    explicit ContactListener(GamePage* page);

    /**
     * Called by Box2D when two fixtures begin to touch.
     * @param contact Pointer to the b2Contact object representing the collision.
     */
    void BeginContact(b2Contact* contact) override;

private:
    GamePage* page; //Pointer to the GamePage, used to delegate contact handling.
};

#endif // CONTACTLISTENER_H
