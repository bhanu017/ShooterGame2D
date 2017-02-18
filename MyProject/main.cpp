#include <SFML/Graphics.hpp>
#include "Player.h"
#include <string>

using namespace std;
int main()
{
	sf::RenderWindow window(sf::VideoMode(1366, 768), "FunShooter", sf::Style::Default);
	bool fullscreen = false;
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);
	//Once the Game starts
	// Load an image file from a file
	sf::Texture background;
	if (!background.loadFromFile("textures/bg_new.png"))
		return -1;
	background.setRepeated(true);
	sf::Sprite bgSprite;
	bgSprite.setTexture(background);
	bgSprite.setTextureRect(sf::IntRect(0,0,1366,768));
	std::string name = "bhanu";
	sf::Font font;
	font.loadFromFile("fonts/arial.ttf");
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

	return 0;
}