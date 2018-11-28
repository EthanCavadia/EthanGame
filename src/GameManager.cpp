#include "global.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "player_character.h"
#include "GameManager.h"
#include "ground.h"
#include "Menu.h"

GameManager::GameState GameManager::gameState = Uninitialized;

void GameManager::Game()
{
	if (GameManager::gameState != GameManager::Uninitialized)
	{
		return;
	}

	// then create (or automatically recreate) the RenderWindow
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(60u);
	music.openFromFile("data/OffLimits.wav");
	music.setLoop(true);
	music.setVolume(10u);
	music.play();

	gameState = ShowingMenu;

	while (!IsExiting())
	{
		GameLoop();
	}
	window.close();
}

class PlayerContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact) override
	{
		auto* userDataA = contact->GetFixtureA()->GetUserData();
		auto* userDataB = contact->GetFixtureB()->GetUserData();
		PlayerCharacter* pCharPtr = nullptr;
		if (userDataA)
		{
			pCharPtr = static_cast<PlayerCharacter*>(userDataA);
		}
		if (userDataB)
		{
			pCharPtr = static_cast<PlayerCharacter*>(userDataB);
		}
		if (pCharPtr)
		{
			pCharPtr->SetOnGround(true);
		}
	}

	void EndContact(b2Contact* contact) override
	{
		auto* userDataA = contact->GetFixtureA()->GetUserData();
		auto* userDataB = contact->GetFixtureB()->GetUserData();
		PlayerCharacter* pCharPtr = nullptr;
		if (userDataA)
		{
			pCharPtr = static_cast<PlayerCharacter*>(userDataA);
		}
		if (userDataB)
		{
			pCharPtr = static_cast<PlayerCharacter*>(userDataB);
		}
		if (pCharPtr)
		{
			pCharPtr->SetOnGround(false);
		}
	}
};

void GameManager::GameLoop()
{
	switch (gameState)
	{
	case ShowingMenu:
		ShowMenu();
		break;

	case Playing:
		b2World world(b2Vec2(0.0f, 9.81f));
		PlayerContactListener contactListener;
		world.SetContactListener(&contactListener);

		sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));

		PlayerCharacter playerCharacter(world, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(64.0f, 96.0f));
		auto grounds = std::vector<Ground>{
			{world, sf::Vector2f(400.0f, 600.0f), sf::Vector2f(800.0f, 50.0f)},
			{world, sf::Vector2f(800.0f, 300.0f), sf::Vector2f(600.0f, 50.0f)}
		};
		sf::Clock clock;

		while (window.isOpen())
		{
			sf::Time dt = clock.restart();
			// check all the window's events that were triggered since the last iteration of the loop
			sf::Event event;
			while (window.pollEvent(event))
			{
				// "close requested" event: we close the window
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					gameState = Exiting;
					break;
				case sf::Event::Resized:
					ResizedView(window, view);
					break;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
				{
					window.close();
					gameState = Exiting;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				{
					ShowMenu();
				}
			}

			playerCharacter.ManageInput();
			world.Step(dt.asSeconds(), 10, 10);
			//Update of PlayerCharacter and Grounds
			playerCharacter.Update(dt.asSeconds());
			view.setCenter(playerCharacter.GetPosition());
			window.setView(view);
			window.clear(sf::Color::Black);
			//Draw PlayerCharacter and Grounds
			for (auto& g : grounds)
			{
				g.Draw(window);
			}

			playerCharacter.Draw(window);
			window.display();
		}
	}
}

bool GameManager::IsExiting()
{
	if (gameState == Exiting)
	{
		return true;
	}
	return false;
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

void GameManager::ResizedView(sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(WINDOW_WIDTH * aspectRatio, WINDOW_HEIGHT);
}
