#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "SFML/System/Vector2.hpp"
#include "Box2D/Box2D.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Window/Joystick.hpp"
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
	b2Body* body;
	sf::Vector2f position;
	const float playerSpeed = 500.0f;
	bool isOnGround = false;
	bool wasJumpKeyPressed = false;
};

#endif
