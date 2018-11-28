#ifndef BUTTON_H
constexpr auto MAX_BUTTON_ITEM = 2;

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"

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

	sf::Event menuEvent;
	sf::Font menuFont;
	sf::Text menuText[MAX_BUTTON_ITEM];
	int selectedItem;
	int GetPressedItem() { return selectedItem; }
};
#endif
