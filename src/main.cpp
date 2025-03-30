#include "core/Mapping.h"
#include "core/Menu.h"
#include "core/World.h"
#include "entities/Player.h"
#include "physics/Collision.h"
#include "server/Server.h"

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <fstream>
#include <iostream>
#include <set>
#include <string>

using namespace std;

map<int, Player *> player;
vector<Weapon *> unacquiredWeapons;
vector<Bullet *> releasedBullets;
sf::Vector2u window_size(1920, 1080);
int total_width = 4 * window_size.x;
int total_height = window_size.y;
sf::Vector2f scale(0.25f, 0.25f);

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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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

int main(int argc, char* argv[])
{
	if (argc != 2 || set({0, 1, 2}).count(atoi(argv[1])) == 0) {
		throw runtime_error("Usage: " + std::string(argv[0]) + " <choice>; " + "1 for server, 0 for client, 2 for testing");
	}
	int choice = atoi(argv[1]);

	sf::TcpSocket socket;
	sf::Packet packet;
	string buffer;

	if (choice == 1) {
		/*Server*/
		Server server;
		return 0;
	}

	/*Client*/
	int id = 0;
	std::string name = "test";

	sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Mini Mayhem", sf::Style::Default);
	window.setSize(window_size);
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

	if (selection == 2) {
		sf::Font font;
		if (!font.loadFromFile("assets/fonts/DejaVuSans.ttf")) {
			throw runtime_error("Failed to load font");
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
							window.create(sf::VideoMode(window_size.x, window_size.y), "Mini Mayhem", sf::Style::Default);
							fullscreen = false;
						}
						else {
							window.close();
						}
						break;
					case sf::Keyboard::Return:
						if (!fullscreen) {
							window.create(sf::VideoMode(window_size.x, window_size.y), "Mini Mayhem", sf::Style::Fullscreen);
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
	else if (selection == 1) {
		sf::Font font;
		if (!font.loadFromFile("assets/fonts/DejaVuSans.ttf")) {
			throw runtime_error("Failed to load font");
		}

		sf::Texture background;
		if (!background.loadFromFile("assets/textures/bg.png")) {
			throw runtime_error("Failed to load background texture");
		}
		background.setRepeated(true);
		sf::Sprite bgSprite;
		bgSprite.setTexture(background);
		scale = sf::Vector2f((float) window_size.x / background.getSize().x, (float) window_size.y / background.getSize().y);
		bgSprite.setScale(scale);
		bgSprite.setTextureRect(sf::IntRect(0, 0, total_width + 400, total_height + 400 /* TODO: remove this hack - added to fix black screen at the bottom and right*/));

		if (choice == 0) {
			std::cout << "......Enter the Server Address..." << std::endl;
			std::cin >> buffer;
			sf::IpAddress ip(buffer);

			if (socket.connect(ip, 5400, sf::seconds(10.0f)) != sf::Socket::Done) {
				std::cout << "Failed to connect to server" << std::endl;
				return -1;
			}

			std::cout << "Enter your Display Name: " << std::endl;
			std::cin >> name;

			// Send name to server
			packet << name;
			if (socket.send(packet) != sf::Socket::Done) {
				throw runtime_error("Failed to send name to server");
			}
			packet.clear();

			// Receive player ID
			if (socket.receive(packet) != sf::Socket::Done) {
				throw runtime_error("Failed to receive player ID");
			}
			packet >> id;
			packet.clear();

			std::cout << "Received my ID: " << id << std::endl;

			// Wait for either player list update or game start signal from server
			while (true) {
				packet.clear();
				if (socket.receive(packet) != sf::Socket::Done) {
					throw runtime_error("Failed to receive server message");
				}

				int messageType;
				packet >> messageType;

				if (messageType == 0) {
					// Game start signal received
					std::cout << "Game starting..." << std::endl;
					break;
				} else {
					for (auto& p : player) {
						delete p.second;
					}
					player.clear();

					// Player list update received
					std::cout << "Player list updated. Total players: " << messageType << std::endl;
					for (int i = 0; i < messageType; i++) {
						int tmp_id;
						string tmp_name;
						packet >> tmp_id >> tmp_name;

						// Only create new player if it doesn't exist
						if (player.find(tmp_id) == player.end()) {
							player[tmp_id] = new Player(tmp_name, font, tmp_id, sf::Vector2f(scale.x / 2, scale.y / 2), window);
						}
						std::cout << "Player ID: " << tmp_id << " Name: " << tmp_name << std::endl;
					}
				}
			}
		}
		else
		{
			player[id] = new Player(name, font, id, sf::Vector2f(scale.x / 2, scale.y / 2), window);
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

		sf::View player_view(sf::FloatRect(0, 0, window_size.x, window_size.y));
		World world(1, sf::Vector2f(scale.x / 2, scale.y / 2));

		sf::Texture spark;
		if (!spark.loadFromFile("assets/textures/spark.png")) {
			throw runtime_error("Failed to load spark texture");
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

			{
				// Camera view
				bool follow_x = false;
				bool follow_y = false;
				auto x = player[id]->Sprite.getPosition().x;
				auto y = player[id]->Sprite.getPosition().y;
				if (x > window_size.x / 3 && x < total_width - 2 * window_size.x / 3) {
					follow_x = true;
				}
				if (y > 2 * window_size.y / 3 && y < total_height - window_size.y / 3) {
					follow_y = true;
				}
				auto center = player_view.getCenter();
				player_view.setCenter(sf::Vector2f(follow_x ? x + window_size.x / 6 : center.x, follow_y ? y - window_size.y / 6 : center.y));
				window.setView(player_view);
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
				bullet->draw(window);
			}

			// Draw unacquired weapons
			for (auto& weapon : unacquiredWeapons) {
				weapon->draw(window);
			}

			// Draw UI elements
			if (id >= 0 && static_cast<size_t>(id) < player.size()) {
				auto center = player_view.getCenter();
				Player* currentPlayer = player[id];
				healthstatus.setSize(sf::Vector2f(200.0f * (currentPlayer->Health / 100.0f), 8.0f));
				healthstatus.setFillColor(sf::Color::Red);
				healthbar.setPosition(center.x - window_size.x / 2 + 10, center.y - window_size.y / 2 + 10);
				healthstatus.setPosition(center.x - window_size.x / 2 + 10, center.y - window_size.y / 2 + 10);
				window.draw(healthbar);
				window.draw(healthstatus);

				nitrostatus.setSize(sf::Vector2f(200.0f * (currentPlayer->Nitro / 2000.0f), 8.0f));
				nitrostatus.setFillColor(sf::Color::Blue);
				nitrobar.setPosition(center.x - window_size.x / 2 + 10, center.y - window_size.y / 2 + 30);
				nitrostatus.setPosition(center.x - window_size.x / 2 + 10, center.y - window_size.y / 2 + 30);
				window.draw(nitrobar);
				window.draw(nitrostatus);
			}

			window.display();
		}
	}

	// Cleanup
	for (auto& p : player) delete p.second;
	for (auto& w : unacquiredWeapons) delete w;
	for (auto& b : releasedBullets) delete b;
	return 0;
}
