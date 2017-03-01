#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Menu.h"
#include "Mapping.h"
#include <string>

using namespace std;
int main()
{
	int windowHeight = 640; /*Vertical length*/
	int windowWidth = 640; /*Horizontal length*/
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "FunShooter", sf::Style::Default);/**/
	bool fullscreen = false;
	Menu menu(window.getSize().x, window.getSize().y);
	int selection = 0;
	while (window.isOpen() && !selection)
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						selection = 1;
						break;

					case 1:
						selection = 2;
						break;

					case 2:
						window.close();
						break;
					}
					break;
				}
				break;
			}
		}
		window.clear();

		menu.draw(window);

		window.display();
	}
	std::string name = "bhanu";
	bool isfiring;
	sf::Font font;
	int justfired = 0;
	font.loadFromFile("fonts/arial.ttf");	//3 other Fonts Available
	/*showing Health on screen*/
	sf::RectangleShape healthbar(sf::Vector2f(200.0f, 8.0f));
	sf::RectangleShape healthstatus(sf::Vector2f(200.0f, 8.0f));
	healthbar.setOutlineColor(sf::Color::White);
	healthbar.setOutlineThickness(2.0f);
	healthbar.setOrigin(sf::Vector2f(0.0f, 4.0f));
	healthstatus.setOrigin(sf::Vector2f(0.0f, 4.0f));
	healthbar.setPosition(sf::Vector2f(window.getSize().x - 250, 20.0f));
	healthstatus.setPosition(sf::Vector2f(window.getSize().x - 250, 20.0f));
	healthbar.setFillColor(sf::Color::Transparent);
	/*showing Nitro on screen*/
	sf::RectangleShape nitrobar(sf::Vector2f(200.0f, 8.0f));
	sf::RectangleShape nitrostatus(sf::Vector2f(200.0f, 8.0f));
	nitrobar.setOutlineColor(sf::Color::White);
	nitrobar.setOutlineThickness(2.0f);
	nitrobar.setOrigin(sf::Vector2f(0.0f, 4.0f));
	nitrostatus.setOrigin(sf::Vector2f(0.0f, 4.0f));
	nitrobar.setPosition(sf::Vector2f(window.getSize().x - 250, 40.0f));
	nitrostatus.setPosition(sf::Vector2f(window.getSize().x - 250, 40.0f));
	nitrobar.setFillColor(sf::Color::Transparent);
	if (selection == 1) { 
		//Once the Game starts
		// Load an image file from a file
		// let's define a view
		sf::View player_view(sf::FloatRect(0, 0, windowWidth, windowHeight));/**/

		// want to do visibility checks? retrieve the view
		sf::View currentView = window.getView();
		sf::Texture background;
		bool isLoaded;
		isLoaded = background.loadFromFile("textures/bg_new.png");
		if (!isLoaded)
			return -1;
		background.setRepeated(true);
		sf::Sprite bgSprite;
		bgSprite.setTexture(background);
		bgSprite.setTextureRect(sf::IntRect(0, 0, windowWidth, windowHeight));/**/
		Mapping::mapping();

		Player player(name, font);
		vector<Weapon *> unacquiredWeapons;
		vector<Bullet *> releasedBullets;
		sf::Texture spark;
		spark.loadFromFile("textures/spark.png");
		sf::Sprite Spark;
		Spark.setTexture(spark);
		window.setFramerateLimit(30);
		while (window.isOpen())
		{
			isfiring = false;
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::KeyPressed) {
					switch (event.key.code) {
					case sf::Keyboard::Escape:
						if (fullscreen) {
							window.create(sf::VideoMode(windowWidth, windowHeight), "FunShooter", sf::Style::Default);/**/
							fullscreen = false;
						}
						else {
							window.close();
						}
						break;
					case sf::Keyboard::Return:
						if (!fullscreen) {
							window.create(sf::VideoMode(windowWidth, windowHeight), "FunShooter", sf::Style::Fullscreen);/**/
							fullscreen = true;
						}
						break;
					case sf::Keyboard::LAlt:
						player.changeweapon();
						break;
					case sf::Keyboard::L:
						player.releaseWeapon(unacquiredWeapons);
						break;
					case sf::Keyboard::G:
						player.acquireweapon(unacquiredWeapons);
						break;
					}
				}
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
				if (player.CurrentWeapon->fire(player.Name, releasedBullets, window, Spark) == true) {
					isfiring = true;
				}
			}
			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				cout << "Pressed" << endl;
			}*/
			window.clear();
			//window.draw(shape);
			window.draw(bgSprite);
			/*Draw Health Bar*/
			healthstatus.setSize(sf::Vector2f(2*player.Health, 8.0f));
			healthstatus.setFillColor(sf::Color::Magenta);
			window.draw(healthstatus);
			window.draw(healthbar);
			/*Draw Health Bar*/
			/*Draw Nitro Bar*/
			nitrostatus.setSize(sf::Vector2f(player.Nitro/10, 8.0f));
			nitrostatus.setFillColor(sf::Color::Cyan);
			window.draw(nitrostatus);
			window.draw(nitrobar);
			/*Draw Nitro Bar*/
			player.update(window);
			for (int i = 0; i < releasedBullets.size(); i++) {		//WORK here. we need to damage the player if it passes
				//through the player and destroy the bullet
				releasedBullets[i]->update();
				releasedBullets[i]->draw(window);
				//window.draw(releasedBullets[i]->Text);
			}
			for (int i = 0; i < unacquiredWeapons.size(); i++) {	//WORK here.we need to make Movable to false, as soon as it gets to rest
				//Then the weapon will be available for use by another player (work of colliders)
				//also destroy the guns if there are no bullets in it after touching the ground (whatever you feel)
				if (unacquiredWeapons[i]->Movable) unacquiredWeapons[i]->freefall();
				unacquiredWeapons[i]->draw(window);
			}
			//player_view.setCenter(player.Sprite.getPosition());
			//window.setView(player_view);
			player.draw(window);
			if (isfiring) {
				window.draw(Spark);
			}
			if (player.CurrentWeapon != NULL) player.CurrentWeapon->draw(window);
			/*if (player.VSpeed > 200.0f) {
				window.close();
			}*/
			//activate it
			window.display();
		}
	}
	if (selection == 2) {
		sf::Text t;
		t.setFont(font);
		t.setString("Page is Under Construction");
		t.setFillColor(sf::Color::Yellow);
		t.setCharacterSize(42);
		window.clear();
		window.draw(t);
		window.display();
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::KeyPressed) {
					switch (event.key.code) {
					case sf::Keyboard::Escape:
						if (fullscreen) {
							window.create(sf::VideoMode(windowWidth, windowHeight), "FunShooter", sf::Style::Default);/**/
							fullscreen = false;
						}
						else {
							window.close();
						}
						break;
					case sf::Keyboard::Return:
						if (!fullscreen) {
							window.create(sf::VideoMode(windowWidth, windowHeight), "FunShooter", sf::Style::Fullscreen);/**/
							fullscreen = true;
						}
						break;
					}

				}
			}
		}

	}

	return 0;
}