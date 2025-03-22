#pragma once
#include<SFML/Network.hpp>
#include <vector>
#include <string>
class Server
{
public:
	Server();
	~Server();
	std::vector <sf::TcpSocket * > clients;
	sf::SocketSelector selector;
	bool done;
	std::vector <std::string> names;
};

