#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			/*if (event.type == sf::Event::KeyPressed) {
				std::cout << "Pressed" << std::endl;
			}*/
		}
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			cout << "Pressed" << endl;
		}*/
		window.clear();
		//window.draw(shape);
		window.display();
	}

	return 0;
}