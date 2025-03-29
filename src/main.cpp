#include <SFML/Graphics.hpp>
#include "entities/Player.h"
#include "core/Menu.h"
#include "core/Mapping.h"
#include "core/World.h"
#include <string>
#include <fstream>
#include "physics/Collision.h"
#include <iostream>
#include "server/Server.h"
#include <SFML/Network.hpp>

using namespace std;

map<int, Player *> player;
vector<Weapon *> unacquiredWeapons;
vector<Bullet *> releasedBullets;

void handlePlayerInput(sf::RenderWindow& window, Player* currentPlayer, World& world, sf::Sprite& Spark)
{
	if (currentPlayer == nullptr) return;

	// Handle weapon switching
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
		currentPlayer->changeweapon();
	}
	
	// Handle weapon dropping
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		currentPlayer->releaseWeapon(unacquiredWeapons);
	}
	
	// Handle weapon pickup
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		currentPlayer->acquireweapon(unacquiredWeapons);
	}

	// Handle shooting
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (currentPlayer->CurrentWeapon && 
			currentPlayer->CurrentWeapon->fire(currentPlayer->Name, releasedBullets, window, Spark))
		{
			// Bullet fired successfully
		}
	}

	// Update player position and state
	currentPlayer->update(window, world);
}

int main()
{
	int choice;
	std::cout << "Mini Mayhem" << " - 1 for server, 0 for client" << endl;
	std::cin >> choice;

	sf::TcpSocket socket;
	sf::Packet packet;
	string buffer;

	if (choice == 1) {
		/*Server*/
		Server server;
	}
	else if (choice != 0) {
		cout << "Invalid choice" << endl;
		return 0;
	}

	/*Client*/
	int id;
	int windowHeight = 1080;
	int windowWidth = 1920;

	ifstream inFile;
	inFile.open("assets/maps/map.txt");
	if (!inFile.is_open()) {
		cout << "Failed to open map file" << endl;
		return -1;
	}

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Mini Mayhem", sf::Style::Default);
	bool fullscreen = false;
	Menu menu(window.getSize().x, window.getSize().y);
	int selection = 0;

	// Menu loop
	while (window.isOpen() && !selection)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
			else if (event.type == sf::Event::KeyReleased)
			{
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
				default:
					break;
				}
			}
		}
		window.clear();
		menu.draw(window);
		window.display();
	}

	if (selection == 1) {
		sf::Font font;
		if (!font.loadFromFile("assets/fonts/sans.ttf")) {
			cout << "Failed to load font" << endl;
			return -1;
		}

		std::string name;
		std::cout << "......Enter the Server Address..." << endl;
		std::cin >> buffer;
		sf::IpAddress ip(buffer);

		if (socket.connect(ip, 5400, sf::seconds(10.0f)) != sf::Socket::Done) {
			cout << "Failed to connect to server" << endl;
			return -1;
		}

		std::cout << "Enter your Display Name: " << endl;
		std::cin >> name;

		// Send name to server
		packet << name;
		if (socket.send(packet) != sf::Socket::Done) {
			cout << "Failed to send name to server" << endl;
			return -1;
		}
		packet.clear();

		// Receive player ID
		if (socket.receive(packet) != sf::Socket::Done) {
			cout << "Failed to receive player ID" << endl;
			return -1;
		}
		packet >> id;
		packet.clear();

		cout << "Received my ID: " << id << endl;

		// Wait for either player list update or game start signal
		while (true) {
			packet.clear();
			if (socket.receive(packet) != sf::Socket::Done) {
				cout << "Failed to receive server message" << endl;
				return -1;
			}

			int messageType;
			packet >> messageType;

			if (messageType == 0) {
				// Game start signal received
				cout << "Game starting..." << endl;
				break;
			} else {
				for (auto& p : player) {
					delete p.second;
				}
				player.clear();

				// Player list update received
				cout << "Player list updated. Total players: " << messageType << endl;
				for (int i = 0; i < messageType; i++) {
					int tmp_id;
					string tmp_name;
					packet >> tmp_id >> tmp_name;

					// Only create new player if it doesn't exist
					if (player.find(tmp_id) == player.end()) {
						player[tmp_id] = new Player(tmp_name, font, tmp_id);
					}
					cout << "Player ID: " << tmp_id << " Name: " << tmp_name << endl;
				}
			}
		}

		// Game setup
		sf::RectangleShape healthbar(sf::Vector2f(200.0f, 8.0f));
		sf::RectangleShape healthstatus(sf::Vector2f(200.0f, 8.0f));
		healthbar.setOutlineColor(sf::Color::White);
		healthbar.setOutlineThickness(2.0f);
		healthbar.setOrigin(sf::Vector2f(0.0f, 4.0f));
		healthstatus.setOrigin(sf::Vector2f(0.0f, 4.0f));
		healthbar.setFillColor(sf::Color::Transparent);

		sf::RectangleShape nitrobar(sf::Vector2f(200.0f, 8.0f));
		sf::RectangleShape nitrostatus(sf::Vector2f(200.0f, 8.0f));
		nitrobar.setOutlineColor(sf::Color::White);
		nitrobar.setOutlineThickness(2.0f);
		nitrobar.setOrigin(sf::Vector2f(0.0f, 4.0f));
		nitrostatus.setOrigin(sf::Vector2f(0.0f, 4.0f));
		nitrobar.setFillColor(sf::Color::Transparent);

		sf::View player_view(sf::FloatRect(0, 0, windowWidth, windowHeight));
		sf::View currentView = window.getView();

		sf::Texture background;
		if (!background.loadFromFile("assets/textures/bg.png")) {
			cout << "Failed to load background texture" << endl;
			return -1;
		}
		background.setRepeated(true);
		sf::Sprite bgSprite;
		bgSprite.setTexture(background);
		bgSprite.setOrigin(sf::Vector2f(1010, 669));
		bgSprite.setScale((float)windowWidth / 2020.0f, (float)windowHeight / 1338.0f);

		World world(1);

		sf::Texture spark;
		if (!spark.loadFromFile("assets/textures/spark.png")) {
			cout << "Failed to load spark texture" << endl;
			return -1;
		}
		sf::Sprite Spark;
		Spark.setTexture(spark);
		window.setFramerateLimit(30);

		// Main game loop
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) {
					packet << "esc";
					socket.send(packet);
					window.close();
					break;
				}
			}

			if (!window.isOpen()) break;

			// Handle input for current player
			if (id >= 0 && static_cast<size_t>(id) < player.size()) {
				handlePlayerInput(window, player[id], world, Spark);
			}

			// Update bullets
			for (auto it = releasedBullets.begin(); it != releasedBullets.end();) {
				if (!(*it)->update(world)) {
					delete *it;
					it = releasedBullets.erase(it);
				} else {
					++it;
				}
			}

			// Draw everything
			window.clear();
			window.draw(bgSprite);
			world.draw(window);
			
			// Draw all players
			for (auto& p : player) {
				if (p.second) p.second->draw(window, id);
			}

			// Draw bullets
			for (auto& bullet : releasedBullets) {
				window.draw(bullet->Sprite);
			}

			// Draw UI elements
			if (id >= 0 && static_cast<size_t>(id) < player.size()) {
				Player* currentPlayer = player[id];
				healthstatus.setSize(sf::Vector2f(200.0f * (currentPlayer->Health / 100.0f), 8.0f));
				healthstatus.setFillColor(sf::Color::Red);
				healthbar.setPosition(10, 10);
				healthstatus.setPosition(10, 10);
				window.draw(healthbar);
				window.draw(healthstatus);

				nitrostatus.setSize(sf::Vector2f(200.0f * (currentPlayer->Nitro / 2000.0f), 8.0f));
				nitrostatus.setFillColor(sf::Color::Blue);
				nitrobar.setPosition(10, 30);
				nitrostatus.setPosition(10, 30);
				window.draw(nitrobar);
				window.draw(nitrostatus);
			}

			window.display();
		}
	}
	else if (selection == 2) {
		sf::Font font;
		if (!font.loadFromFile("assets/fonts/sans.ttf")) {
			cout << "Failed to load font" << endl;
			return -1;
		}
		
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
							window.create(sf::VideoMode(windowWidth, windowHeight), "Mini Mayhem", sf::Style::Default);
							fullscreen = false;
						}
						else {
							window.close();
						}
						break;
					case sf::Keyboard::Return:
						if (!fullscreen) {
							window.create(sf::VideoMode(windowWidth, windowHeight), "Mini Mayhem", sf::Style::Fullscreen);
							fullscreen = true;
						}
						break;
					default:
						break;
					}
				}
			}
		}
	}

	// Cleanup
	for (auto& p : player) delete p.second;
	for (auto& w : unacquiredWeapons) delete w;
	for (auto& b : releasedBullets) delete b;
	return 0;
}
