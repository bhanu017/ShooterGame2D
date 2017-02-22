#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Menu.h"
#include <string>

using namespace std;
int main()
{
	sf::RenderWindow window(sf::VideoMode(1366, 768), "FunShooter", sf::Style::Default);
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
	sf::Font font;
	font.loadFromFile("fonts/arial.ttf");	//3 other Fonts Available
	if (selection == 1) {
		//Once the Game starts
		// Load an image file from a file
		sf::Texture background;
		if (!background.loadFromFile("textures/bg_new.png"))
			return -1;
		background.setRepeated(true);
		sf::Sprite bgSprite;
		bgSprite.setTexture(background);
		bgSprite.setTextureRect(sf::IntRect(0, 0, 1366, 768));
		Player player(name, font);
		window.setFramerateLimit(30);
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
							window.create(sf::VideoMode(800, 600), "FunShooter", sf::Style::Default);
							fullscreen = false;
						}
						else {
							window.close();
						}
						break;
					case sf::Keyboard::Return:
						if (!fullscreen) {
							window.create(sf::VideoMode(800, 600), "FunShooter", sf::Style::Fullscreen);
							fullscreen = true;
						}
						break;
					}

				}
			}
			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				cout << "Pressed" << endl;
			}*/
			window.clear();
			//window.draw(shape);
			window.draw(bgSprite);
			player.update();
			player.draw(window);
			/*if (player.VSpeed > 200.0f) {
				window.close();
			}*/
			window.display();
		}
	}
	if (selection == 2) {
		sf::Text t;
		t.setFont(font);
		t.setString("Page is Under Construction");
		t.setFillColor(sf::Color::Yellow);
		t.setCharacterSize(42);
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
							window.create(sf::VideoMode(800, 600), "FunShooter", sf::Style::Default);
							fullscreen = false;
						}
						else {
							window.close();
						}
						break;
					case sf::Keyboard::Return:
						if (!fullscreen) {
							window.create(sf::VideoMode(800, 600), "FunShooter", sf::Style::Fullscreen);
							fullscreen = true;
						}
						break;
					}

				}
			}
			window.clear();
			window.draw(t);
			window.display();
		}

	}

	return 0;
}