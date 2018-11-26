#include <ContactListener.h>
#include "PlayerCharacter.h"

void PlayerContactListener::BeginContact(b2Contact* contact)
{
	auto* userDataA = contact->GetFixtureA()->GetUserData();
	auto* userDataB = contact->GetFixtureB()->GetUserData();
	PlayerCharacter* pCharPtr = nullptr;
	if (userDataA)
	{
		pCharPtr = static_cast<PlayerCharacter*>(userDataA);
	}
	if (userDataB)
	{
		pCharPtr = static_cast<PlayerCharacter*>(userDataB);
	}
	if (pCharPtr)
	{
		pCharPtr->SetOnGround(true);
	}
}

void PlayerContactListener::EndContact(b2Contact* contact)
{

	auto* userDataA = contact->GetFixtureA()->GetUserData();
	auto* userDataB = contact->GetFixtureB()->GetUserData();
	PlayerCharacter* pCharPtr = nullptr;
	if (userDataA)
	{
		pCharPtr = static_cast<PlayerCharacter*>(userDataA);
	}
	if (userDataB)
	{
		pCharPtr = static_cast<PlayerCharacter*>(userDataB);
	}
	if (pCharPtr)
	{
		pCharPtr->SetOnGround(false);
	}

}

