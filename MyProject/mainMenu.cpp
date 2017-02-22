#include "SFML/Graphics.hpp"
#include "Menu.h"
#include <iostream>
using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Shooter Game");

	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
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
						cout << "You pressed PLAY" << endl;
						break;

					case 1:
						cout << "You pressed OPTIONS" << endl;
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
}