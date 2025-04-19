#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <Box2D/Box2D.h>
class GamePage;

class ContactListener : public b2ContactListener {
public:
    explicit ContactListener(GamePage* page);
    void BeginContact(b2Contact* contact) override;
private:
    GamePage* page;
};

#endif // CONTACTLISTENER_H
