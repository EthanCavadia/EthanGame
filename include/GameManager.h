#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "SFML/System/Clock.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

class GameManager
{
public:
	void Game();

private:
	bool IsExiting();
	void GameLoop();
	void ResizedView(sf::RenderWindow& window, sf::View& view);
	void ShowMenu();
	void ShowPauseMenu();

	enum GameState { Uninitialized, ShowingMenu, ShowingPauseMenu, Playing, Exiting };

	static GameState gameState;
	sf::RenderWindow window;
	sf::Clock clock;
};

#endif
