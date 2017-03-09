#include <vector>
#include <math.h>
#include "Weapon.h"
#include "Collision.h"


#define PI 3.14159265

Weapon::Weapon(std::string name, sf::Font textfont, sf::Vector2f pos)
{
	Movable = false;
	Font = textfont;
	Scale = 0.5f;	//change for hdr (approx. 0.5f) test for this - change this (may)
	Text.setString("Me ..the Destroyer");		//if we want to rename bullet to damage taker, we can write bullet, grenade so on
	Text.setFont(Font);
	Name = name;
	if (name == "doublebarrel") {
		TextureSize = sf::Vector2i(100, 100);	//164, 265 for hdr - change this
		No_bullets = 56;
		if (!Texture.loadFromFile("textures/doublebarrel.png")) {

		}
	}
	else if (name == "weapon1") {
		TextureSize = sf::Vector2i(100, 100);	//164, 265 for hdr - change this
		No_bullets = 156;
		if (!Texture.loadFromFile("textures/weapon1.png")) {

		}
	}
	else if (name == "weapon2") {
		TextureSize = sf::Vector2i(100, 100);	//164, 265 for hdr - change this
		No_bullets = 134;
		if (!Texture.loadFromFile("textures/weapon2.png")) {

		}
	}
	Sprite.setTexture(Texture);
	Sprite.setTextureRect(sf::IntRect(0, 0, TextureSize.x, TextureSize.y));
	Sprite.setScale(sf::Vector2f(Scale, Scale));
	if (Name == "weapon1") {
		Sprite.setOrigin(41, 41);
	}
	else if (Name == "weapon2") {
		Sprite.setOrigin(36, 44);
	}
	else if (Name == "doublebarrel") {
		Sprite.setOrigin(20, 45);
	}
	else {
		Sprite.setOrigin(TextureSize.x / 3, TextureSize.y / 2);
	}
	Sprite.setPosition(pos.x + TextureSize.x / 20, pos.y - TextureSize.y / 8);
	Velocity.x = 0.0f;
	Velocity.y = 200.0f;
	Angle = 0;
}


Weapon::~Weapon()
{
}

void Weapon::freefall(World &world)
{
	sf::Vector2f prevPos = Sprite.getPosition();
	Sprite.move(Velocity.x / 30, Velocity.y / 30);
	if (Collision::WeaponWall(this, world)) {
		Sprite.setPosition(prevPos);
		Movable = false;
	}
}

void Weapon::update(sf::Vector2f pos, int angle, sf::RenderWindow &window)
{
	if (sf::Mouse::getPosition(window).x  == window.getSize().x/2) {
		if (sf::Mouse::getPosition(window).y == window.getSize().y/2 - TextureSize.y/25) {
			angle = 0;
		}
		else if (sf::Mouse::getPosition(window).y > window.getSize().y / 2 - TextureSize.y / 25) {
			angle = 90;
		}
		else {
			angle = 270;
		}
		Sprite.setPosition(pos.x, pos.y - TextureSize.y / 25);
	}
	else if (sf::Mouse::getPosition(window).x >  window.getSize().x / 2) {
		Sprite.setTextureRect(sf::IntRect(0, 0, TextureSize.x, TextureSize.y));
		if (Name == "weapon1") Sprite.setOrigin(41, 41);
		else if (Name == "weapon2") Sprite.setOrigin(36, 44);
		else if (Name == "doublebarrel") Sprite.setOrigin(20, 45);
		Sprite.setPosition(pos.x + TextureSize.x / 20, pos.y - TextureSize.y / 8);
	}
	else {
		Sprite.setTextureRect(sf::IntRect(TextureSize.x, 0, -TextureSize.x, TextureSize.y));
		if (Name == "weapon1") Sprite.setOrigin(59, 41);
		else if (Name == "weapon2") Sprite.setOrigin(64, 44);
		else if (Name == "doublebarrel") Sprite.setOrigin(80, 45);
		Sprite.setPosition(pos.x - TextureSize.x / 20, pos.y - TextureSize.y / 8);
	}
	Angle = angle;
	Sprite.setRotation(angle);
}

bool Weapon::fire(std::string pname, std::vector<Bullet *> &list, sf::RenderWindow &window, sf::Sprite &Spark)
{
	if (No_bullets > 0) {
		No_bullets--;
		if (Name == "doublebarrel") {
			No_bullets -= 3;
			if (sf::Mouse::getPosition(window).x >= window.getSize().x / 2) {
				Spark.setTextureRect(sf::IntRect(38, 0, -38, 25));
				Spark.setOrigin(0, 25 / 2);
				Spark.setScale(Scale, Scale);
				Spark.setPosition(sf::Vector2f(Sprite.getPosition().x + cos(PI*Angle / 180) * (85.0f - Sprite.getOrigin().x), Sprite.getPosition().y + sin(PI*Angle / 180) *(85.0f - Sprite.getOrigin().x)));
				Spark.setRotation(Angle);
				list.push_back(new Bullet(Scale, pname, Font, sf::Vector2f(Sprite.getPosition().x + cos(PI*Angle / 180) * (85.0f - Sprite.getOrigin().x), Sprite.getPosition().y + sin(PI*Angle / 180) * (85.0f - Sprite.getOrigin().x)), Angle - 15));
				list.push_back(new Bullet(Scale, pname, Font, sf::Vector2f(Sprite.getPosition().x + cos(PI*Angle / 180) *(85.0f - Sprite.getOrigin().x), Sprite.getPosition().y +sin(PI*Angle / 180) * (85.0f - Sprite.getOrigin().x)), Angle - 5));
				list.push_back(new Bullet(Scale, pname, Font, sf::Vector2f(Sprite.getPosition().x + cos(PI*Angle / 180) * (85.0f - Sprite.getOrigin().x), Sprite.getPosition().y + sin(PI*Angle / 180) * (85.0f - Sprite.getOrigin().x)), Angle + 5));
				list.push_back(new Bullet(Scale, pname, Font, sf::Vector2f(Sprite.getPosition().x + cos(PI*Angle / 180) * (85.0f - Sprite.getOrigin().x), Sprite.getPosition().y + sin(PI*Angle / 180) *(85.0f - Sprite.getOrigin().x)), Angle + 15));
			}
			else {
				Spark.setTextureRect(sf::IntRect(0, 0, 38, 25));
				Spark.setOrigin(38, 25 / 2);
				Spark.setScale(Scale, Scale);
				Spark.setPosition(sf::Vector2f(Sprite.getPosition().x - cos(PI*Angle / 180) * (Sprite.getOrigin().x - 15.0f), Sprite.getPosition().y - sin(PI*Angle / 180) * (Sprite.getOrigin().x - 15.0f)));
				Spark.setRotation(Angle);
				list.push_back(new Bullet(Scale, pname, Font, sf::Vector2f(Sprite.getPosition().x - cos(PI*Angle / 180) * (Sprite.getOrigin().x - 15.0f), Sprite.getPosition().y - sin(PI*Angle / 180) * (Sprite.getOrigin().x - 15.0f)), Angle - 15 + 180));
				list.push_back(new Bullet(Scale, pname, Font, sf::Vector2f(Sprite.getPosition().x - cos(PI*Angle / 180) * (Sprite.getOrigin().x - 15.0f), Sprite.getPosition().y - sin(PI*Angle / 180) * (Sprite.getOrigin().x - 15.0f)), Angle - 5 + 180));
				list.push_back(new Bullet(Scale, pname, Font, sf::Vector2f(Sprite.getPosition().x - cos(PI*Angle / 180) * (Sprite.getOrigin().x - 15.0f), Sprite.getPosition().y - sin(PI*Angle / 180) *(Sprite.getOrigin().x - 15.0f)), Angle + 5 + 180));
				list.push_back(new Bullet(Scale, pname, Font, sf::Vector2f(Sprite.getPosition().x - cos(PI*Angle / 180) * (Sprite.getOrigin().x - 15.0f), Sprite.getPosition().y - sin(PI*Angle / 180) * (Sprite.getOrigin().x - 15.0f)), Angle + 15 + 180));
			}
		}
		else if (Name == "weapon1") {
			if (sf::Mouse::getPosition(window).x >= window.getSize().x / 2) {
				Spark.setTextureRect(sf::IntRect(38, 0, -38, 25));
				Spark.setOrigin(0, 25 / 2);
				Spark.setScale(Scale, Scale);
				Spark.setPosition(sf::Vector2f(Sprite.getPosition().x + cos(PI*Angle / 180) * (75.0f - Sprite.getOrigin().x), Sprite.getPosition().y + sin(PI*Angle / 180) * (75.0f - Sprite.getOrigin().x)));
				Spark.setRotation(Angle);
				list.push_back(new Bullet(Scale, pname, Font, sf::Vector2f(Sprite.getPosition().x + cos(PI*Angle / 180) * (75.0f - Sprite.getOrigin().x), Sprite.getPosition().y + sin(PI*Angle / 180) * (75.0f - Sprite.getOrigin().x)), Angle));
			}
			else {
				Spark.setTextureRect(sf::IntRect(0, 0, 38, 25));
				Spark.setOrigin(38, 25 / 2);
				Spark.setScale(Scale, Scale);
				Spark.setPosition(sf::Vector2f(Sprite.getPosition().x - cos(PI*Angle / 180) * (Sprite.getOrigin().x - 25.0f), Sprite.getPosition().y - sin(PI*Angle / 180) * (Sprite.getOrigin().x - 25.0f)));
				Spark.setRotation(Angle);
				list.push_back(new Bullet(Scale, pname, Font, sf::Vector2f(Sprite.getPosition().x - cos(PI*Angle / 180) * (Sprite.getOrigin().x - 25.0f), Sprite.getPosition().y - sin(PI*Angle / 180) * (Sprite.getOrigin().x - 25.0f)), Angle + 180));
			}
		}
		else if (Name == "weapon2") {
			if (sf::Mouse::getPosition(window).x >= window.getSize().x / 2) {
				Spark.setTextureRect(sf::IntRect(38, 0, -38, 25));
				Spark.setOrigin(0, 25 / 2);
				Spark.setScale(Scale, Scale);
				Spark.setPosition(sf::Vector2f(Sprite.getPosition().x + cos(PI*Angle / 180) * (82.0f - Sprite.getOrigin().x), Sprite.getPosition().y + sin(PI*Angle / 180) * (82.0f - Sprite.getOrigin().x)));
				Spark.setRotation(Angle);
				list.push_back(new Bullet(Scale, pname, Font, sf::Vector2f(Sprite.getPosition().x + cos(PI*Angle / 180) * (82.0f - Sprite.getOrigin().x), Sprite.getPosition().y + sin(PI*Angle / 180) * (82.0f - Sprite.getOrigin().x)), Angle));
			}
			else {
				Spark.setTextureRect(sf::IntRect(0, 0, 38, 25));
				Spark.setOrigin(38, 25 / 2);
				Spark.setScale(Scale, Scale);
				Spark.setPosition(sf::Vector2f(Sprite.getPosition().x - cos(PI*Angle / 180) * (Sprite.getOrigin().x - 18.0f), Sprite.getPosition().y - sin(PI*Angle / 180) * (Sprite.getOrigin().x - 18.0f)));
				Spark.setRotation(Angle);
				list.push_back(new Bullet(Scale, pname, Font, sf::Vector2f(Sprite.getPosition().x - cos(PI*Angle / 180) * (Sprite.getOrigin().x - 18.0f), Sprite.getPosition().y - sin(PI*Angle / 180) * (Sprite.getOrigin().x - 18.0f)), Angle + 180));
			}
		}
		return true;
	}
	return false;
}
