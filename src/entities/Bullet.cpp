#include "Bullet.h"
#include "physics/Collision.h"

#include <cmath>
#include <math.h>
#include <exception>
#define PI 3.14159265

Bullet::Bullet(sf::Vector2f scale, std::string player, sf::Font textfont, sf::Vector2f startpos, int angle)
{
	Movable = true;
	Owner = player;
	Font = textfont;
	Scale = scale;
	StartPos = startpos;
	Text.setString("boom");
	Text.setFont(Font);
	TextureSize = sf::Vector2f(12, 6);
	if (!Texture.loadFromFile("assets/textures/bullet_new.png")) {
		throw std::runtime_error("Failed to load texture");
	}
	Sprite.setTexture(Texture);
	Sprite.setScale(Scale);
	Sprite.setTextureRect(sf::IntRect(0, 0, TextureSize.x, TextureSize.y));
	Sprite.setOrigin(TextureSize.x / 2, TextureSize.y / 2);
	Speed = 100.0f;
	Damage = 35;
	Angle = angle;
	Sprite.setPosition(StartPos);
	Sprite.setRotation(Angle);
}


Bullet::~Bullet()
{
	//when should bullet be destroyed
}

bool Bullet::update(World &world)
{
	Sprite.move(Speed*cos(Angle*PI / 180), Speed*sin(Angle*PI / 180));// check for collision of bullet.
	//Player - Bullet
	if (Collision::BulletWall(this, world)) return false;
	//Text.setString(std::to_string(Angle));
	//Destroyer Condition
	return true;
}
