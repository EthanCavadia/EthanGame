#include <Menu.h>
#include <iostream>
#include "Globals.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Win32/InputImpl.hpp"


MainMenu::MainMenu(float width, float height)
{
	if (!menuFont.loadFromFile("data/gummy.ttf"))
	{
		std::cout << "Fail to load.\n";
	}

	menuText[0].setFont(menuFont);
	menuText[0].setCharacterSize(50);
	menuText[0].setColor(sf::Color::Red);
	menuText[0].setString("Play Game");
	menuText[0].setPosition(sf::Vector2f(width / 2, height / (MAX_BUTTON_ITEM + 1) * 1));

	menuText[1].setFont(menuFont);
	menuText[1].setCharacterSize(50);
	menuText[1].setColor(sf::Color::Red);
	menuText[1].setString("Exit Game");
	menuText[1].setPosition(sf::Vector2f(width / 2, height / (MAX_BUTTON_ITEM + 1) * 2));

	selectedItem = 0;
}

MainMenu::~MainMenu()
{
}

void MainMenu::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_BUTTON_ITEM; i++)
	{
		window.draw(menuText[i]);
	}
}

void MainMenu::MoveUp()
{
	if (selectedItem - 1 >= 0)
	{
		menuText[selectedItem].setColor(sf::Color::Red);
		selectedItem--;
		menuText[selectedItem].setColor(sf::Color::White);
	}
}

void MainMenu::MoveDown()
{
	if (selectedItem + 1 < MAX_BUTTON_ITEM)
	{
		menuText[selectedItem].setColor(sf::Color::Red);
		selectedItem++;
		menuText[selectedItem].setColor(sf::Color::White);
	}
}

MainMenu::MenuAction MainMenu::GetMenuAction(sf::RenderWindow& window)
{
	sf::Event menuEvent;
	while (window.isOpen())
	{
		

		while (window.pollEvent(menuEvent))
		{
			switch (menuEvent.type)
			{
			case sf::Event::KeyReleased:
				switch (menuEvent.key.code)
				{
				case sf::Keyboard::Up:
					MoveUp();
					break;

				case sf::Keyboard::Down:
					MoveDown();
					break;

				case sf::Keyboard::Enter:
					switch (GetPressedItem())
					{
					case 0:
						return Play;

					case 1:
						return Exit;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				window.close();

				break;
			}
		}
		window.clear(sf::Color::Black);
		Draw(window);
		window.display();
	}
}

PauseMenu::PauseMenu(float width, float height): MainMenu(width, height)
{
	menuText[0].setFont(menuFont);
	menuText[0].setCharacterSize(50);
	menuText[0].setColor(sf::Color::Red);
	menuText[0].setString("Resume Game");
	menuText[0].setPosition(sf::Vector2f(width / 2, height / (MAX_BUTTON_ITEM + 1) * 1));

	menuText[1].setFont(menuFont);
	menuText[1].setCharacterSize(50);
	menuText[1].setColor(sf::Color::Red);
	menuText[1].setString("Exit Game");
	menuText[1].setPosition(sf::Vector2f(width / 2, height / (MAX_BUTTON_ITEM + 1) * 2));

	selectedItem = 0;
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_BUTTON_ITEM; i++)
	{
		window.draw(menuText[i]);
	}
}

void PauseMenu::MoveUp()
{
	if (selectedItem - 1 >= 0)
	{
		menuText[selectedItem].setColor(sf::Color::Red);
		selectedItem--;
		menuText[selectedItem].setColor(sf::Color::White);
	}
}

void PauseMenu::MoveDown()
{
	if (selectedItem + 1 < MAX_BUTTON_ITEM)
	{
		menuText[selectedItem].setColor(sf::Color::Red);
		selectedItem++;
		menuText[selectedItem].setColor(sf::Color::White);
	}
}

MainMenu::MenuAction PauseMenu::GetPauseAction(sf::RenderWindow& window)
{
	sf::Event pauseEvent;
	while (window.pollEvent(pauseEvent))
	{
		switch (pauseEvent.type)
		{
		case sf::Event::KeyReleased:
			switch (pauseEvent.key.code)
			{
			case sf::Keyboard::Up:
				MoveUp();
				break;

			case sf::Keyboard::Down:
				MoveDown();
				break;

			case sf::Keyboard::Enter:
				switch (GetPressedItem())
				{
				case 0:
					return Play;

				case 1:
					return Exit;
				}

				break;
			}

			break;
		case sf::Event::Closed:
			window.close();

			break;
		}
	}
	window.clear(sf::Color::Transparent);
	Draw(window);
	window.display();
}
