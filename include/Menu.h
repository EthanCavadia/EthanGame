#ifndef BUTTON_H
constexpr auto MAX_BUTTON_ITEM = 2;

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
<<<<<<< HEAD

=======
#include "SFML/Window/Event.hpp"
>>>>>>> master
class MainMenu
{
public:
	MainMenu(float width, float height);
	~MainMenu();

	void MoveUp();
	void MoveDown();
	void Draw(sf::RenderWindow& window);
	
	enum MenuAction{ Nothing, Exit, Play };

	MenuAction GetMenuAction(sf::RenderWindow& window);

protected:
<<<<<<< HEAD

=======
	sf::Event menuEvent;
>>>>>>> master
	sf::Font menuFont;
	sf::Text menuText[MAX_BUTTON_ITEM];
	int selectedItem;
	int GetPressedItem() { return selectedItem; }
};
#endif

class PauseMenu : public MainMenu
{
public:
	PauseMenu(float width, float height);
	~PauseMenu();

	void MoveUp();
	void MoveDown();
	void Draw(sf::RenderWindow& window);

	MenuAction GetPauseAction(sf::RenderWindow& window);
};