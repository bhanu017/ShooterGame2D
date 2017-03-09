#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Player.h"
#include "World.h"
#include "Bullet.h"
#include "Weapon.h"

class Collision
{
public:
	Collision();
	~Collision();

	//void setWorld(World world);
	static bool PlayerWall(sf::RenderWindow &window, Player *player, World &world);
	static void resolveBounds(sf::RenderWindow &window, Player *player, World &world);
	static bool BulletWall(Bullet *bullet, World &world);
	static bool WeaponWall(Weapon *weapon, World &world);
};

