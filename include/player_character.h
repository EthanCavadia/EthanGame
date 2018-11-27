#ifndef TACOS_PLAYER_H
#define TACOS_PLAYER_H

#include <Box2D/Dynamics/b2World.h>
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics.hpp"
class PlayerCharacter
{
public:
	PlayerCharacter(b2World& world, sf::Vector2f position,sf::Vector2f size);

	void ManageInput();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
	
	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f v);
	void SetOnGround(bool contact);
	void Shoot(b2World& world);
	
private:
	sf::RectangleShape playerShape;
	sf::Texture playerTexture;
	b2Body* body;
	sf::Vector2f position;
	const float playerSpeed = 500.0f;
	bool wasJumpKeyPressed = false;
	bool isOnGround = false;
};


#endif
