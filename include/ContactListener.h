#ifndef PLAYERCONTACTLISTENER_H
#define PLAYERCONTACTLISTENER_H

#include "Box2D/Dynamics/b2WorldCallbacks.h"

class PlayerContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
};
#endif