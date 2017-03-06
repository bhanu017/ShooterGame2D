#pragma once
#include <SFML\Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include "World.h"

class Resolver
{
public:
	Resolver();
	~Resolver();
	
	static void CollisionResolver(sf::RenderWindow &window, Player *player, World &world);
};

