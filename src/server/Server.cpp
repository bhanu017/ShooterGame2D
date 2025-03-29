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
		cout << "Failed to start server on port 5400" << endl;
		return;
	}

	cout << "Server successfully started on port 5400" << endl;
	cout << "Server IP: " << sf::IpAddress::getLocalAddress().toString() << endl;

	selector.add(listener);
	done = false;
	sf::Clock clock;
	clock.restart();
	int playerCount = 0;

	cout << "Waiting for players to connect..." << endl;

	while (!done && clock.getElapsedTime().asSeconds() < timer)
	{
		if (selector.wait(sf::milliseconds(100)))
		{
			if (selector.isReady(listener))
			{
				sf::TcpSocket* socket = new sf::TcpSocket;
				if (listener.accept(*socket) == sf::Socket::Done)
				{
					cout << "New client connected from " << socket->getRemoteAddress().toString() << endl;
					sf::Packet packet;
					string name;

					if (socket->receive(packet) == sf::Socket::Done)
					{
						packet >> name;
						int id = playerCount;
						names[id] = name;
						clients[id] = socket;
						selector.add(*socket);

						cout << name << " has been connected with id == " << id << endl;

						// Send ID to the new client
						packet.clear();
						packet << id;
						if (socket->send(packet) != sf::Socket::Done) {
							cout << "Failed to send ID to client " << name << endl;
							continue;
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
								cout << "Failed to send player list to a client" << endl;
							}
						}

						playerCount++;
					}
					else
					{
						cout << "Failed to receive player name from " << socket->getRemoteAddress().toString() << endl;
						delete socket;
					}
				}
				else
				{
					cout << "Failed to accept connection" << endl;
					delete socket;
				}
			}
			else
			{
				
			}
		}
		else
		{
			auto elapsed = clock.getElapsedTime().asMilliseconds();
			if (elapsed % 1000 > 0 && elapsed % 1000 < 100)
			{
				cout << "Game starts in " << (timer - elapsed / 1000) << " seconds" << endl;
			}
		}
	}

	if (clients.empty())
	{
		cout << "No players connected. Server shutting down." << endl;
		return;
	}
	else
	{
		cout << "Server running with " << clients.size() << " players connected" << endl;

		// Send start signal to all clients
		sf::Packet packet;
		packet << 0; // 0 means game can start
		for (auto& client : clients) {
			if (client.second->send(packet) != sf::Socket::Done) {
				cout << "Failed to send start signal" << endl;
				return;
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
									cout << "Failed to broadcast message to client " << pair.first << endl;
								}
							}
						}

						++it;
					}
					else if (it->second->receive(packet) == sf::Socket::Disconnected)
					{
						// Handle client disconnection
						cout << "Client " << it->first << " disconnected" << endl;
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
	cout << "Server destroyed" << endl;
}
