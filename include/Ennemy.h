#ifndef ENNEMY_H
#define ENNEMY_H
#include "SFML/System/Vector2.hpp"
#include "Box2D/Box2D.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"


class PlayerCharacter;

class Enemies
{
public:
	Enemies(b2World& world, sf::Vector2f position, sf::Vector2f size);
	void Draw(sf::RenderWindow& window);
	void TargetPlayer(PlayerCharacter& playerCharacter, sf::RenderWindow& window);
private:
	sf::RectangleShape enemiesShape;
	sf::Vector2f position;
	b2Body* body;
	b2Fixture* fixture;
	const float enemiesSpeed = 400.0f;
};
#endif