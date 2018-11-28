#include <player_character.h>
#include <Box2D/Box2D.h>
#include "physics.h"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Joystick.hpp"
#include <iostream>
#include "SFML/Audio.hpp"

PlayerCharacter::PlayerCharacter(b2World& world, sf::Vector2f position, sf::Vector2f size): position(position)
{
	if (!playerTexture.loadFromFile("data/megaSprite.png"))
	{
		std::cerr << "fail to load\n.";
	}
	//definition of the play size, position and texture
	playerShape.setPosition(position);
	playerShape.setSize(size);
	playerShape.setOrigin(size / 2.0f);
	playerShape.setTexture(&playerTexture);

	//definition of the player movement behavior
	b2BodyDef bodyDef;;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position = pixel2meter(position);
	bodyDef.userData = this;
	body = world.CreateBody(&bodyDef);

	//definition of the player shape and collision comportment
	b2FixtureDef rectFixtureDef;
	b2PolygonShape rectShape;
	rectShape.SetAsBox(pixel2meter(size.x / 2.0f), pixel2meter(size.y / 2.0f));
	rectFixtureDef.shape = &rectShape;
	rectFixtureDef.userData = this;
	rectFixtureDef.density = 1;
	rectFixtureDef.friction = 0;
	body->CreateFixture(&rectFixtureDef);
}

void PlayerCharacter::ManageInput()
{


	float horizontalInput = 0.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		horizontalInput = -1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		horizontalInput = 1.0f;
	}

	float verticalJump = body->GetLinearVelocity().y;
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && 
		!wasJumpKeyPressed && isOnGround)
	{
		//Jump
		verticalJump = -8.0f;
		
	}

	//Joystick input TODO debug constant movement
	if (sf::Joystick::isConnected(0))
	{
		float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::X))
		{
			if (x < 90.0f)
			{
				horizontalInput = -1.0f;
			}
		}

		if (sf::Joystick::getAxisPosition(0, sf::Joystick::X))
		{
			if (x > 90.0f)
			{
				horizontalInput = 1.0f;
			}
		}

		if (sf::Joystick::isButtonPressed(0, 0) && !wasJumpKeyPressed && isOnGround)
		{
			//Jump
			verticalJump = -8.0f;
		
		}
	}
	body->SetLinearVelocity(b2Vec2(pixel2meter(playerSpeed) * horizontalInput, verticalJump));

	wasJumpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(
		sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0,0);
}

void PlayerCharacter::Update(float dt)
{
	//Update player position with body
	position = meter2pixel(body->GetPosition());
	playerShape.setPosition(position);
}

void PlayerCharacter::Draw(sf::RenderWindow& window)
{
	window.draw(playerShape);
}

sf::Vector2f PlayerCharacter::GetPosition()
{
	return position;
}

void PlayerCharacter::SetPosition(sf::Vector2f v)
{
	position = v;
}

void PlayerCharacter::SetOnGround(bool contact)
{
	isOnGround = contact;
}

