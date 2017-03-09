#pragma once
#include<SFML\Network.hpp>

class Server
{
public:
	Server();
	~Server();
	std::vector <sf::TcpSocket * > clients;
	sf::SocketSelector selector;
	bool done = false;
	std::vector <string> names;
};

