#include "Server.h"
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

Server::Server()
{
	sf::TcpListener listener;
	auto timer = 15;

	// Try to bind to all available network interfaces
	if (listener.listen(5400) != sf::Socket::Done) {
		throw runtime_error("Failed to start server on port 5400");
	}

	std::cout << "Server successfully started on port 5400" << std::endl;
	std::cout << "Server IP: " << sf::IpAddress::getLocalAddress().toString() << std::endl;

	selector.add(listener);
	done = false;
	sf::Clock clock;
	clock.restart();
	int playerCount = 0;

	std::cout << "Waiting for players to connect..." << std::endl;

	while (!done && clock.getElapsedTime().asSeconds() < timer)
	{
		if (selector.wait(sf::milliseconds(100)))
		{
			if (selector.isReady(listener))
			{
				sf::TcpSocket* socket = new sf::TcpSocket;
				if (listener.accept(*socket) == sf::Socket::Done)
				{
					std::cout << "New client connected from " << socket->getRemoteAddress().toString() << std::endl;
					sf::Packet packet;
					std::string name;

					if (socket->receive(packet) == sf::Socket::Done)
					{
						packet >> name;
						int id = playerCount;
						names[id] = name;
						clients[id] = socket;
						selector.add(*socket);

						std::cout << name << " has been connected with id == " << id << std::endl;

						// Send ID to the new client
						packet.clear();
						packet << id;
						if (socket->send(packet) != sf::Socket::Done) {
							throw runtime_error("Failed to send ID to client " + name);
						}

						// Send updated player list to all clients
						packet.clear();
						packet << static_cast<sf::Uint32>(clients.size());
						for (const auto& pair : clients)
						{
							packet << static_cast<sf::Uint32>(pair.first) << names[pair.first];
						}
						for (const auto& pair : clients)
						{
							if (pair.second->send(packet) != sf::Socket::Done) {
								throw runtime_error("Failed to send player list to a client " + names[pair.first]);
							}
						}

						playerCount++;
					}
					else
					{
						throw runtime_error("Failed to receive player name from " + socket->getRemoteAddress().toString());
					}
				}
				else
				{
					throw runtime_error("Failed to accept connection");
					delete socket;
				}
			}
		}
		else
		{
			auto elapsed = clock.getElapsedTime().asMilliseconds();
			if (elapsed % 1000 > 0 && elapsed % 1000 < 100)
			{
				std::cout << "Game starts in " << (timer - elapsed / 1000) << " seconds" << std::endl;
			}
		}
	}

	if (clients.empty())
	{
		std::cout << "No players connected. Server shutting down." << std::endl;
		return;
	}
	else
	{
		std::cout << "Server running with " << clients.size() << " players connected" << std::endl;

		// Send start signal to all clients
		sf::Packet packet;
		packet << 0; // 0 means game can start
		for (auto& client : clients) {
			if (client.second->send(packet) != sf::Socket::Done) {
				throw runtime_error("Failed to send start signal");
			}
		}
		packet.clear();

		while (!done && selector.wait())
		{
			// Server broadcast loop
			for (auto it = clients.begin(); it != clients.end();)
			{
				if (done)
					break;

				if (selector.isReady(*it->second))
				{
					if (done)
						break;

					sf::Packet packet;
					if (it->second->receive(packet) == sf::Socket::Done)
					{
						// Broadcast the message to all other clients
						for (const auto& pair : clients)
						{
							if (pair.first != it->first)
							{
								if (pair.second->send(packet) != sf::Socket::Done) {
									throw runtime_error("Failed to broadcast message to client " + std::to_string(pair.first));
								}
							}
						}

						++it;
					}
					else if (it->second->receive(packet) == sf::Socket::Disconnected)
					{
						// Handle client disconnection
						std::cout << "Client " << it->first << " disconnected" << std::endl;
						selector.remove(*it->second);
						delete it->second;
						names.erase(it->first);
						it = clients.erase(it);

						// TODO: Notify remaining clients about the disconnection
						// packet.clear();
						// packet << static_cast<sf::Uint32>(clients.size());
						// for (const auto& pair : clients)
						// {
						// 	packet << static_cast<sf::Uint32>(pair.first) << names[pair.first];
						// }
						// for (const auto& pair : clients)
						// {
						// 	if (pair.second->send(packet) != sf::Socket::Done) {
						// 		cout << "Failed to send updated player list after disconnection" << endl;
						// 	}
						// }
						// break;

						if (clients.size() == 0)
						{
							done = true;
						}
					}
				}
				else
				{
					++it;
				}
			}
		}
	}
}

Server::~Server()
{
	for (const auto& pair : clients)
	{
		delete pair.second;
	}
	std::cout << "Server destroyed" << std::endl;
}
