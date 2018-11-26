#include <Ennemy.h>
#include "physics.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "PlayerCharacter.h"

Enemies::Enemies(b2World& world, sf::Vector2f position, sf::Vector2f size) : position(position)
{
	//Setting the player proprieties
	enemiesShape.setPosition(position);
	enemiesShape.setSize(size);
	enemiesShape.setOrigin(size / 2.0f);
	enemiesShape.setFillColor(sf::Color::Blue);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position = pixel2meter(position);
	bodyDef.userData = this;
	bodyDef.angle = 0;
	body = world.CreateBody(&bodyDef);

	b2FixtureDef rectFixtureDef;
	b2PolygonShape rectShape;
	rectShape.SetAsBox(pixel2meter(size.x / 2.0f), pixel2meter(size.y / 2.0f));
	rectFixtureDef.shape = &rectShape;
	rectFixtureDef.userData = this;
	rectFixtureDef.density = 1;
	rectFixtureDef.friction = 0;
	body->CreateFixture(&rectFixtureDef);
}

void Enemies::TargetPlayer(PlayerCharacter& playerCharacter, sf::RenderWindow& window)
{
	
}

void Enemies::Draw(sf::RenderWindow& window)
{
	window.draw(enemiesShape);
}
