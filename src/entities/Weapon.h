#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "GameObject.h"
#include "Bullet.h"
#include "core/World.h"

class Weapon : public GameObject
{
public:
	Weapon(std::string name, sf::Font textfont, sf::Vector2f pos, sf::Vector2f scale);
	~Weapon();
	void freefall(World &world);
	void update(sf::Vector2f pos, int angle, sf::RenderWindow &window);
	bool fire(std::string pname, std::vector<Bullet *> &list, sf::RenderWindow &window, sf::Sprite &Spark);
	std::string Name;
	sf::Vector2f Velocity;
	int No_bullets;
	int Angle;
private:

};
