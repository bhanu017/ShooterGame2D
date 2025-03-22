#pragma once
#include <SFML/Graphics.hpp>
#include "entities/Player.h"
#include "entities/Bullet.h"
#include "core/World.h"

class Resolver
{
public:
	Resolver();
	~Resolver();
	
	static void CollisionResolver(sf::RenderWindow &window, Player *player, World &world);
};

