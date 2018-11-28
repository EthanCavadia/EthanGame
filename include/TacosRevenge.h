#include "SFML/System/Clock.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

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
