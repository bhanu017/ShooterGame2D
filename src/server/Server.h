#pragma once
#include<SFML/Network.hpp>
#include <map>
#include <string>
#include <vector>

class Server
{
public:
	Server();
	~Server();
	std::map<int, sf::TcpSocket*> clients;  // Map of player ID to socket
	sf::SocketSelector selector;
	bool done;
	std::map<int, std::string> names;  // Map of player ID to name
};

