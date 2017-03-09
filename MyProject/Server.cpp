#include "Server.h"
#include <conio.h>
#include <vector>
#include <iostream>

using namespace std;

Server::Server()
{
	sf::TcpListener listener;
	sf::SocketSelector selector;
	bool done = false;
	std::vector <sf::TcpSocket * > clients;
	std::vector <string> names;

	listener.listen(2000);
	selector.add(listener);

	sf::Clock clock;
	clock.restart();
	int playerCount = 0;
	int id;

	while ((clock.getElapsedTime()).asSeconds() < 120)
	{
		if (selector.isReady(listener))
		{
			sf::TcpSocket *socket = new	sf::TcpSocket;
			listener.accept(*socket);
			sf::Packet packet;
			string name;
			if (socket->receive(packet) == sf::Socket::Done)
				packet >> name;

			id = playerCount;					// Ids start from 0.
			names[0] = name;
			playerCount++;

			packet << id;
			clients[id]->send(packet);

			cout << name << " has been connected with id == " << id << endl;
			clients.push_back(socket);
			selector.add(*socket);
		}
	}
	for (int i = 0; i < clients.size(); i++)
	{
		sf::Packet sendPacket;
		sendPacket << i << names[i];
		for (int j = 0; j < clients.size(); j++)
		{
			clients[j]->send(sendPacket);
		}
	}

	/*			for (int i = 0; i < clients.size(); i++)
				{
					if (selector.isReady(*clients[i]))
					{
						sf::Packet packet, sendPacket;
						if (clients[i]->receive(packet) == sf::Socket::Done)
						{
							string text;
							packet >> text;
							sendPacket << text;
							for (int j = 0; j < clients.size(); j++)
							{
								if (i != j)
								{
									clients[j]->send(sendPacket);
								}
							}
						}
					}
				}
			}
		}
	}*/
	for (vector <sf::TcpSocket * >::iterator it = clients.begin(); it != clients.end(); it++)
	{
		delete *it;
	}
}

Server::~Server() 
{

}