#pragma once
#include <SFML/Graphics.hpp>
#include "Weapon.h"
#include <string>
#include <vector>
#include "World.h"

class Player : public GameObject
{
public:
	Player(std::string &Name, sf::Font textfont);
	~Player();
	float Speed;
	float VSpeed;
	float HSpeed;
	bool IsFlying = false;
	bool IsWalking = false;
	std::string Name;
	int Health;
	Weapon *CurrentWeapon;
	Weapon *OtherWeapon;
	std::string LastDamager;
	int Nitro;
	void update(sf::RenderWindow &window, World &world);
	void releaseWeapon(std::vector<Weapon *> &unacquired);
	void acquireweapon(std::vector<Weapon*>& unacquired);
	void changeweapon();
	void draw(sf::RenderWindow & window);
private:
	sf::RectangleShape focusline;
	int SpeedLimit;
	int TextureCounter = 0;
	sf::Vector2i TextureFlySize;
	sf::Texture TextureFly;
	float GForce;
	float JetForce;
protected:
};

