#pragma once

#include <SFML\Graphics.hpp>

#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(float scale, std::string name, sf::Font textfont, sf::Vector2f startpos, int angle);
	~Bullet();
	void update();
private:
	int Damage;
	float Speed;
	std::string Owner;
	sf::Vector2f StartPos;
	int Angle;
};

