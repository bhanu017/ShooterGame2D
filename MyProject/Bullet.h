#pragma once

#include <SFML\Graphics.hpp>

#include "GameObject.h"
#include "World.h"

class Bullet : public GameObject
{
public:
	Bullet(float scale, std::string name, sf::Font textfont, sf::Vector2f startpos, int angle);
	~Bullet();
	bool update(World &world);
private:
	int Damage;
	float Speed;
	std::string Owner;
	sf::Vector2f StartPos;
	int Angle;
};

