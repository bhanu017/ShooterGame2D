#pragma once
#include <SFML/Graphics.hpp>
#include "Weapon.h"
#include "GameObject.h"
#include "core/World.h"
#include <string>
#include <vector>

class Player : public GameObject
{
public:
	Player(std::string &Name, sf::Font textfont, int id, sf::Vector2f scale, sf::RenderWindow &window);
	~Player();
	float HSpeed;
	float VSpeed;
	bool IsFlying = false;
	bool IsWalking = false;
	std::string Name;
	int Health;
	int Id;
	Weapon *CurrentWeapon;
	Weapon *OtherWeapon;
	std::string LastDamager;
	int Nitro;
	void update(sf::RenderWindow &window, World &world);
	void releaseWeapon(std::vector<Weapon *> &unacquired);
	void acquireweapon(std::vector<Weapon*>& unacquired);
	void changeweapon();
	void draw(sf::RenderWindow & window, int id);
private:
	float HSpeedFly;
	float HSpeedWalk;
	sf::RectangleShape focusline;
	int SpeedLimit;
	int TextureCounter = 0;
	float GForce;
	float JetForce;
	sf::Vector2f TextureFlySize;
	sf::Texture TextureFly;
protected:
};

