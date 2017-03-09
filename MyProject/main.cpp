#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Menu.h"
#include "Mapping.h"
#include "World.h"
#include <string>
#include <fstream>
#include "Collision.h"
#include <iostream>
#include <SFML/Network.hpp>

using namespace std;

vector<Player *> player;
vector<Weapon *> unacquiredWeapons;
vector<Bullet *> releasedBullets;

void runplayer(void *window) {
	/*bool isfiring = false;
	int justfired = 0;
	case sf::Keyboard::LAlt:
		player[id]->changeweapon();
		break;
	case sf::Keyboard::L:
		player[id]->releaseWeapon(unacquiredWeapons);
		break;
	case sf::Keyboard::G:
		player[id]->acquireweapon(unacquiredWeapons);
		break;
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
					if (player.CurrentWeapon->fire(player.Name, releasedBullets, window, Spark) == true) {
						isfiring = true;
					}
	}
	player.update(window, world);
	*/
}

int main()
{
	int choice;
	char n;
	std::cout << "FunShooter" << "Press Any Key to continue" << endl;
	std::cin >> n;
	std::cout << "1 for server , 0 for client" << endl;
	std::cin >> choice;
	sf::TcpSocket socket;
	sf::Packet packet;
	string buffer;
	std::size_t received;
	int No_of_players;
	if (choice == 1) {
		/*Server*/

		return 0;
	}
	else if (choice == 0) {
		/*Client*/
		int id;
		int windowHeight = 720; /*Vertical length*/
		int windowWidth = 1280; /*Horizontal length*/
		ifstream inFile;
		inFile.open("map.txt");


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
		


		

		

		
		
		
		
		
		
		
		
		
		
		

		sf::Font font;
		font.loadFromFile("fonts/arial.ttf");	//3 other Fonts Available
		if (selection == 1) {
			std::string name;
			std::cout << "......Enter the Server Address..." << endl;
			std::cin >> buffer;
			sf::IpAddress ip(buffer);
			std::cout << "Enter your Display Name: " << endl;
			std::cin >> name;
			socket.connect(ip, 2000);
			packet << name;
			socket.send(packet);
			packet.clear();
			socket.receive(packet);
			packet >> id;
			packet.clear();
			socket.receive(packet);
			packet >> No_of_players;
			packet.clear();
			player.resize(No_of_players);
			
			vector<int> ids;
			ids.resize(No_of_players);
			for (int i = 0; i < No_of_players; i++) {
				socket.receive(packet);
				packet >> ids[i] >> name;
				packet.clear();
				player[i] = new Player(name, font, ids[i]);
			}


			/*showing Health on screen*/
			sf::RectangleShape healthbar(sf::Vector2f(200.0f, 8.0f));
			sf::RectangleShape healthstatus(sf::Vector2f(200.0f, 8.0f));
			healthbar.setOutlineColor(sf::Color::White);
			healthbar.setOutlineThickness(2.0f);
			healthbar.setOrigin(sf::Vector2f(0.0f, 4.0f));
			healthstatus.setOrigin(sf::Vector2f(0.0f, 4.0f));

			healthbar.setFillColor(sf::Color::Transparent);
			/*showing Nitro on screen*/
			sf::RectangleShape nitrobar(sf::Vector2f(200.0f, 8.0f));
			sf::RectangleShape nitrostatus(sf::Vector2f(200.0f, 8.0f));
			nitrobar.setOutlineColor(sf::Color::White);
			nitrobar.setOutlineThickness(2.0f);
			nitrobar.setOrigin(sf::Vector2f(0.0f, 4.0f));
			nitrostatus.setOrigin(sf::Vector2f(0.0f, 4.0f));
			nitrobar.setFillColor(sf::Color::Transparent);
			//Once the Game starts
			// Load an image file from a file
			// let's define a view
			sf::View player_view(sf::FloatRect(0, 0, windowWidth, windowHeight));/**/

																				 // want to do visibility checks? retrieve the view
			sf::View currentView = window.getView();
			sf::Texture background;
			bool isLoaded;
			float zoomlevel = 1.0f;
			isLoaded = background.loadFromFile("textures/bg.png");
			if (!isLoaded)
				return -1;
			background.setRepeated(true);
			sf::Sprite bgSprite;
			bgSprite.setTexture(background);
			bgSprite.setOrigin(sf::Vector2f(1010, 669));
			bgSprite.setScale((float)(windowWidth + 150.0f) / 2020.0f, (float)(windowHeight + 150.0f) / 1338.0f);
			//Mapping::mapping();			// creates the map.txt and map here.
			World world(1);

			sf::Texture spark;
			spark.loadFromFile("textures/spark.png");
			sf::Sprite Spark;
			Spark.setTexture(spark);
			window.setFramerateLimit(30);
			socket.receive(packet);
			packet >> choice;
			if (choice != 0) return 1;
			packet.clear();
			while (window.isOpen())
			{
				sf::Event event;
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed) {
						packet << "esc";
						socket.send(packet);
						packet.clear();
						while (1) {
							socket.receive(packet);
							packet >> buffer;
							if (buffer == "Bye") {
								cout << "Bye.." << endl;
								window.close();
								return 0;
							}
						}
					}
					if (event.type == sf::Event::KeyPressed) {
						switch (event.key.code) {
						case sf::Keyboard::Escape:
							if (fullscreen) {
								window.create(sf::VideoMode(windowWidth, windowHeight), "FunShooter", sf::Style::Default);/**/
								fullscreen = false;
							}
							else {
								packet << "esc";
								socket.send(packet);
								packet.clear();
								while (1) {
									socket.receive(packet);
									packet >> buffer;
									if (buffer == "Bye") {
										cout << "Bye.." << endl;
										window.close();
										return 0;
									}
								}
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
				/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				cout << "Pressed" << endl;
				}*/

				window.clear();

				//window.draw(shape);
				/*healthbar.setPosition(sf::Vector2f(player.Sprite.getPosition().x + window.getSize().x / 2 - 250, player.Sprite.getPosition().y - window.getSize().y / 2 + 20.0f));
				healthstatus.setPosition(sf::Vector2f(player.Sprite.getPosition().x + window.getSize().x / 2 - 250, player.Sprite.getPosition().y - window.getSize().y / 2 + 20.0f));
				nitrobar.setPosition(sf::Vector2f(player.Sprite.getPosition().x + window.getSize().x / 2 - 250, player.Sprite.getPosition().y - window.getSize().y / 2 + 40.0f));
				nitrostatus.setPosition(sf::Vector2f(player.Sprite.getPosition().x + window.getSize().x / 2 - 250, player.Sprite.getPosition().y - window.getSize().y / 2 + 40.0f));
				bgSprite.setPosition(player.Sprite.getPosition());
				window.draw(bgSprite);
				/*Draw Tiles*/
				/*world.draw(window);
				/*Draw Tiles*/
				/*Draw Health Bar*/
				/*healthstatus.setSize(sf::Vector2f(2 * player.Health, 8.0f));
				healthstatus.setFillColor(sf::Color::Magenta);
				window.draw(healthstatus);
				window.draw(healthbar);
				/*Draw Health Bar*/
				/*Draw Nitro Bar*/
				/*nitrostatus.setSize(sf::Vector2f(player.Nitro / 10, 8.0f));
				nitrostatus.setFillColor(sf::Color::Cyan);
				window.draw(nitrostatus);
				window.draw(nitrobar);
				/*Draw Nitro Bar*/

				for (int i = 0; i < releasedBullets.size(); i++) {		//WORK here. we need to damage the player if it passes
																		//through the player and destroy the bullet
					if (!releasedBullets[i]->update(world)) releasedBullets.erase(releasedBullets.begin() + i);
					else releasedBullets[i]->draw(window);
					//window.draw(releasedBullets[i]->Text);
				}
				for (int i = 0; i < unacquiredWeapons.size(); i++) {	//WORK here.we need to make Movable to false, as soon as it gets to rest
																		//Then the weapon will be available for use by another player (work of colliders)
																		//also destroy the guns if there are no bullets in it after touching the ground (whatever you feel)
					if (unacquiredWeapons[i]->Movable) unacquiredWeapons[i]->freefall(world);
					unacquiredWeapons[i]->draw(window);
				}
				/*player_view.setCenter(player.Sprite.getPosition());
				window.setView(player_view);

				player.draw(window);

				if (isfiring) {
					window.draw(Spark);
				}
				if (player.CurrentWeapon != NULL) player.CurrentWeapon->draw(window);
				/*if (player.VSpeed > 200.0f) {
				window.close();
				}*/
				//activate it
				//window.display();
				
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
	else {
		return 1;
	}
} 