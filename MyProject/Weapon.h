#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Bullet.h"

class Weapon : public GameObject
{
public:
	Weapon(std::string name, sf::Font textfont, sf::Vector2f pos);
	~Weapon();
	void freefall();
	void update(sf::Vector2f pos, int angle, sf::RenderWindow &window);
	bool fire(std::string pname, std::vector<Bullet *> &list, sf::RenderWindow &window, sf::Sprite &Spark);
	std::string Name;
	sf::Vector2f Velocity;
	int No_bullets;
	int Angle;
private:

};

