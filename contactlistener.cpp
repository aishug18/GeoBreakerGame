#include "contactlistener.h"
#include "gamepage.h"

ContactListener::ContactListener(GamePage* page)
    : page(page)
{}

void ContactListener::BeginContact(b2Contact* contact) {
    b2Body* A = contact->GetFixtureA()->GetBody();
    b2Body* B = contact->GetFixtureB()->GetBody();
    page->handleContact(A, B);
}
