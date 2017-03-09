#include <math.h>
#include "Bullet.h"
#include "Collision.h"

#define PI 3.14159265

Bullet::Bullet(float scale, std::string player, sf::Font textfont, sf::Vector2f startpos, int angle)
{
	Movable = true;
	Owner = player;
	Font = textfont;
	TextureSize = sf::Vector2i(12, 6);	//for hdr - change this
	Scale = scale;	//change for hdr (approx. 0.5f) test for this - change this (may)
	Text.setString("boom");		//if we want to rename bullet to damage taker, we can write bullet, grenade so on
	Text.setFont(Font);
	if (!Texture.loadFromFile("textures/bullet_new.png")) {

	}
	Sprite.setTexture(Texture);
	Sprite.setTextureRect(sf::IntRect(0, 0, TextureSize.x, TextureSize.y));
	Sprite.setOrigin(TextureSize.x / 2, TextureSize.y / 2);
	Sprite.setScale(sf::Vector2f(Scale, Scale));
	Speed = 100.0f;
	StartPos = startpos;
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
