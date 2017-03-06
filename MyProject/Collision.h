#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Player.h"
#include "World.h"

class Collision
{
public:
	Collision();
	~Collision();

	//void setWorld(World world);
	static bool PlayerWall(sf::RenderWindow &window, Player *player, World &world);
	static bool PlayerBullet();
	static bool BulletWall();
};

