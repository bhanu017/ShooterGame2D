#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <string>

class Player : public GameObject
{
public:
	Player(std::string &Name, sf::Font textfont);
	~Player();
	float Speed;
	float VSpeed;
	bool IsFlying = false;
	bool IsWalking = false;
	std::string Name;
	int Health;
	int Nitro;
	void update();
private:
	int SpeedLimit;
	int TextureCounter = 0;
	sf::Vector2i TextureFlySize;
	sf::Texture TextureFly;
	float GForce;
	float JetForce;
protected:
};

