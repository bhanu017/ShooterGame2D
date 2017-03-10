#include "Server.h"
#include <conio.h>
#include <vector>
#include <iostream>

using namespace std;

Server::Server()
{
	sf::TcpListener listener;

	listener.listen(5400);
	selector.add(listener);
	done = false;
	sf::Clock clock;
	clock.restart();
	int playerCount = 0;
	int id;
	cout << sf::IpAddress::getLocalAddress().toString() << endl;

	while (clock.getElapsedTime().asSeconds() < 120)
	{

		if (selector.isReady(listener))
		{
			cout << "connected" << endl;
			sf::TcpSocket *socket = new	sf::TcpSocket;
			listener.accept(*socket);
			cout << "connected1" << endl;
			sf::Packet packet;
			string name;
			//socket->receive(packet);
			if (socket->receive(packet) == sf::Socket::Done)
				packet >> name;

			id = playerCount;					// Ids start from 0.
			names[0] = name;
			playerCount++;

			cout << name << " has been connected with id == " << id << endl;

			packet << id;
			clients[id]->send(packet);

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
}

Server::~Server() 
{
	for (vector <sf::TcpSocket * >::iterator it = clients.begin(); it != clients.end(); it++)
	{
		delete *it;
	}
}