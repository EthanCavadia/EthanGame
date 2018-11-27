#include <GameManager.h>
#include <Globals.h>
#include "PlayerCharacter.h"
#include "Menu.h"
#include <ContactListener.h>
#include <json.hpp>
#include <iostream>

GameManager::GameState GameManager::gameState = Uninitialized;

void GameManager::Game()
{
	if (gameState != Uninitialized)
	{
		return;
	}

	// then create (or automatically recreate) the RenderWindow
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(60u);
	gameState = ShowingMenu;

	while (!IsExiting())
	{
		GameLoop();
	}
	window.close();
}

bool GameManager::IsExiting()
{
	if (gameState == Exiting)
	{
		return true;
	}
	return false;
}

void GameManager::GameLoop()
{
	switch (gameState)
	{
	case ShowingMenu:
		ShowMenu();
		break;
	case ShowingPauseMenu: //TODO
		ShowPauseMenu();
		break;

	case Playing:
		//Setting the world and the contact listener
		b2World world(b2Vec2(0.0f, 9.81f));
		PlayerContactListener contactListener;
		world.SetContactListener(&contactListener);

		sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(window.getSize().x, window.getSize().y));
		PlayerCharacter playerCharacter(world, sf::Vector2f(PLAYER_SPAWN, PLAYER_SPAWN),
			sf::Vector2f(PLAYER_WIDTH,PLAYER_HEIGHT));

		auto grounds = std::vector<Ground>{
			{world, sf::Vector2f(400.0f, 600.0f), sf::Vector2f(800.0f, 50.0f)},
			{world, sf::Vector2f(800.0f, 300.0f), sf::Vector2f(600.0f, 50.0f)}
		};

		
		sf::Event event;
		sf::Time dt = clock.restart();

		while (window.isOpen())
		{
			while (window.pollEvent(event))
			{
				// "close requested" event: we close the window
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					ResizedView(window, view);
					break;
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Key::P:
						ShowPauseMenu();
						break;
					}

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
				}

				playerCharacter.InputManager();
				world.Step(dt.asSeconds(), 10, 10);
				playerCharacter.Update(dt.asSeconds());
				view.setCenter(playerCharacter.GetPosition());
				window.setView(view);
				window.clear(sf::Color::Black);
				//DrawMap();
				for (auto& g : grounds)
				{
					g.Draw(window);
				}
				playerCharacter.Draw(window);
				window.display();
			}
			break;
		}
	}
}
void GameManager::ResizedView(sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(WINDOW_HEIGHT * aspectRatio, WINDOW_HEIGHT);
}

void GameManager::ShowMenu()
{
	MainMenu mainMenu(window.getSize().x / 2, window.getSize().y);
	MainMenu::MenuAction action = mainMenu.GetMenuAction(window);
	switch (action)
	{
	case MainMenu::Exit:
		gameState = Exiting;
		break;

	case MainMenu::Play:
		gameState = Playing;
		break;
	}
}

void GameManager::ShowPauseMenu()
{
	PauseMenu pauseMenu(window.getSize().x/2 , window.getSize().y);
	MainMenu::MenuAction action = pauseMenu.GetPauseAction(window);

	switch (action)
	{
	case PauseMenu::Exit:
		gameState = Exiting;
		break;

	case PauseMenu::Play:
		gameState = Playing;
		break;
	}
}
