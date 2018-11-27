#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "SFML/System/Vector2.hpp"
#include "Box2D/Box2D.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include <SFML/Graphics/Texture.hpp>
#include "SFML/Graphics/Sprite.hpp"

class Ground
{
public:
	Ground(b2World& world, sf::Vector2f position, sf::Vector2f size);

	void Draw(sf::RenderWindow& window);
private:
	sf::RectangleShape rect;
	b2Body* body;
	b2Fixture* fixture;
	sf::Texture groundTexture;
	sf::Sprite groundSprite;
};

class PlayerCharacter
{
public:
	PlayerCharacter(b2World& world, sf::Vector2f position, sf::Vector2f size);

	void InputManager();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f v);
	void SetOnGround(bool contact);
private:

	sf::RectangleShape playerShape;
	sf::Texture playerTexture;
	b2Body* body;
	b2Fixture* fixture;
	sf::Vector2f position;
	const float playerSpeed = 50.0f;
	bool isOnGround = false;
	bool wasJumpKeyPressed = false;
	bool wasjumpButtonPressed = false;
};

#endif
