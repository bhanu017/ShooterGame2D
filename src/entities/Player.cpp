#include "Player.h"
#include "physics/Collision.h"
#include "physics/Resolver.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

#include <cmath>
#include <iostream>
#include <math.h>
#include <string>

#define PI 3.14159265

using namespace std;

Player::Player(std::string &name, sf::Font textfont, int id, sf::Vector2f scale, sf::RenderWindow &window)
{
	Movable = true;
	Id = id;
	TextureSize = sf::Vector2f(95, 154);
	TextureFlySize = sf::Vector2f(101, 222);
	Font = textfont;
	Scale = scale;
	Name = name;
	Text.setString(name);
	Text.setFont(Font);
	Text.setCharacterSize((int) 24*Scale.x);
	Text.setFillColor(sf::Color::Green);
	Text.setPosition(Sprite.getPosition());
	if (!Texture.loadFromFile("assets/textures/lwalk_4.png")) {
		cout << "Failed to load texture" << endl;
	}
	if (!TextureFly.loadFromFile("assets/textures/lfly_4.png")) {
		cout << "Failed to load texture" << endl;
	}
	Sprite.setTexture(Texture);
	Sprite.setTextureRect(sf::IntRect(0,0, TextureSize.x, TextureSize.y));
	Sprite.setScale(Scale);
	Sprite.setOrigin(TextureSize.x, TextureSize.y);
	Sprite.setPosition(window.getSize().x / 3, window.getSize().y / 3);
	Health = 100;
	Nitro = 2000;
	HSpeedWalk = 90.0f;
	VSpeed = 0.0f;
	HSpeedFly = 180.0f;
	JetForce = -600.0f;
	SpeedLimit = 250.0f;
	LastDamager = "";
	GForce = 300.0f;
	TextureCounter = 0;
	Text.setPosition(Sprite.getPosition());
	Text.move(sf::Vector2f(Scale.x*TextureSize.x / 4, Scale.y*TextureSize.y/2));
	CurrentWeapon = new Weapon("weapon1", Font, Sprite.getPosition(), Scale);
	OtherWeapon = new Weapon("weapon2", Font, Sprite.getPosition(), Scale);
	focusline.setSize(sf::Vector2f(1000.0f, 1.0f));
	focusline.setOrigin(sf::Vector2f(0.0f, 0.5f));
	focusline.setFillColor(sf::Color::Red);
}


Player::~Player()
{
}

void Player::update(sf::RenderWindow &window, World &world)
{
	bool hflying = false;
	bool vflying = false;
	float temp = JetForce;
	float temp3;
	float temp4;
	float pVSpeed = VSpeed;
	bool pIsFlying = IsFlying;
	IsFlying = false;
	IsWalking = false;
	sf::Vector2f PrevPos;
	int temp_prev;
	HSpeed = 0.0f;
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W))) {
		IsFlying = true;
		if (Nitro < 50) {
			JetForce = 0;
			Nitro = 20;
		}
		else Nitro -= 4;
		PrevPos = Sprite.getPosition();
		this->Sprite.move(0.0f, VSpeed / 30 + 0.5f*(JetForce + GForce)*(1 / 900));// check for collision after this.
		Collision::resolveBounds(window, this, world);
		if (Collision::PlayerWall(window, this, world))
		{
			Sprite.setPosition(PrevPos);
			VSpeed = 0.0f;
		}
		else {
			VSpeed = VSpeed + (JetForce + GForce) / 30;
			if (VSpeed < -SpeedLimit*0.9f) VSpeed = pVSpeed;
		}
		if (!pIsFlying) Sprite.setTexture(TextureFly);
		TextureCounter = (TextureCounter + 15) % 16;
		if (sf::Mouse::getPosition(window).x > window.getSize().x / 2) this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureFlySize.x + 5, 0, TextureFlySize.x, TextureFlySize.y));	// +9 or 10 for hdr
		else this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4 + 1)*TextureFlySize.x + 5, 0, -TextureFlySize.x, TextureFlySize.y));	// +9 or 10 for hdr
		if (!pIsFlying) Sprite.setOrigin(TextureFlySize.x / 2, TextureSize.y / 2);
		if (!pIsFlying) Sprite.setScale(Scale);
		temp_prev = Sprite.getRotation();
		Sprite.setRotation(0);
		if (temp_prev != Sprite.getRotation()) {
			if (Collision::PlayerWall(window, this, world))
			{
				Sprite.setRotation(temp_prev);
			}
		}
		JetForce = temp;
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S))) {
		IsFlying = true;
		if (Nitro < 50) {
			Nitro = 20;
			JetForce = 0;
		}
		else Nitro -= 4;
		PrevPos = Sprite.getPosition();
		this->Sprite.move(0.0f, VSpeed / 30 + 0.5f*(-JetForce + GForce)*(1 / 900)); // Check for collision after this
		Collision::resolveBounds(window, this, world);
			if (Collision::PlayerWall(window, this, world))
			{
				Sprite.setPosition(PrevPos);
				VSpeed = 0.0f;
			}
			else {
				VSpeed = VSpeed + (-JetForce + GForce) / 30;
				if (VSpeed > SpeedLimit) VSpeed = pVSpeed;
			}
		if (!pIsFlying) Sprite.setTexture(TextureFly);
		TextureCounter = (TextureCounter + 15) % 16;
		if (sf::Mouse::getPosition(window).x > window.getSize().x / 2) this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4 + 1)*TextureFlySize.x + 5, 0, -TextureFlySize.x, TextureFlySize.y));	// +9 or 10 for hdr
		else this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureFlySize.x + 5, 0, TextureFlySize.x, TextureFlySize.y));	// +9 or 10 for hdr
		if (!pIsFlying) Sprite.setOrigin(TextureFlySize.x / 2, TextureSize.y / 2);
		if (!pIsFlying) Sprite.setScale(Scale);
		temp_prev = Sprite.getRotation();
		Sprite.setRotation(180);
		if (temp_prev != Sprite.getRotation()) {
			if (Collision::PlayerWall(window, this, world))
			{
				Sprite.setRotation(temp_prev);
			}
		}
		JetForce = temp;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		hflying = true;
		if (Nitro < 50) {
			Nitro = 20;
			JetForce = 0;
		}
		else Nitro -= 4;
		if (IsFlying) {
			Nitro += 1;
		}
		HSpeed = -HSpeedFly;
		PrevPos = Sprite.getPosition();
		this->Sprite.move(HSpeed / 30, 0.0f);
		Collision::resolveBounds(window, this, world);
		if (Collision::PlayerWall(window, this, world))
		{
			Sprite.setPosition(PrevPos);
			HSpeed = 0.0f;
		}
		if (!IsFlying) {
			PrevPos = Sprite.getPosition();
			this->Sprite.move(0.0f, VSpeed / 30 + 0.5f*(GForce)*(1 / 900));
			Collision::resolveBounds(window, this, world);
			if (Collision::PlayerWall(window, this, world))
			{
				Sprite.setPosition(PrevPos);
				VSpeed = 0.0f;
			}
			else {
				VSpeed = VSpeed + (GForce) / 30;
				if (VSpeed > SpeedLimit) VSpeed = pVSpeed;
			}
			Sprite.setTexture(TextureFly);
			TextureCounter = (TextureCounter + 15) % 16;
			if (sf::Mouse::getPosition(window).x > window.getSize().x / 2) this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureFlySize.x + 5, 0, TextureFlySize.x, TextureFlySize.y)); // +9 or 10 for hdr
			else this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureFlySize.x + 5, 0, TextureFlySize.x, TextureFlySize.y)); // +9 or 10 for hdr
			Sprite.setOrigin(TextureFlySize.x / 2, TextureSize.y / 2);
			Sprite.setScale(Scale);
		}
		int temp2 = Sprite.getRotation();
		if (temp2 == 0) temp2 = 360;
		if (IsFlying) {
			temp_prev = Sprite.getRotation();
			Sprite.setRotation((temp2 + 270) / 2);
			if (temp_prev != Sprite.getRotation()) {
				if (Collision::PlayerWall(window, this, world))
				{
					Sprite.setRotation(temp_prev);
				}
			}
		}
		else {
			temp_prev = Sprite.getRotation();
			Sprite.setRotation(-90);
			if (temp_prev != Sprite.getRotation()) {
				if (Collision::PlayerWall(window, this, world))
				{
					Sprite.setRotation(temp_prev);
				}
			}
		}
		IsFlying = true;
		JetForce = temp;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		hflying = true;
		if (Nitro < 50) {
			Nitro = 20;
			JetForce = 0;
		}
		else Nitro -= 4;
		if (IsFlying) {
			Nitro += 1;
		}
		HSpeed = HSpeedFly;
		PrevPos = Sprite.getPosition();
		this->Sprite.move(HSpeed / 30, 0.0f);
		Collision::resolveBounds(window, this, world);
		if (Collision::PlayerWall(window, this, world))
		{
			Sprite.setPosition(PrevPos);
			HSpeed = 0.0f;
		}
		if (!IsFlying) {
			PrevPos = Sprite.getPosition();
			this->Sprite.move(0.0f, VSpeed / 30 + 0.5f*(GForce)*(1 / 900));
			Collision::resolveBounds(window, this, world);
			if (Collision::PlayerWall(window, this, world))
			{
				Sprite.setPosition(PrevPos);
				VSpeed = 0.0f;
			}
			else {
				VSpeed = VSpeed + (GForce) / 30;
				if (VSpeed > SpeedLimit) VSpeed = pVSpeed;
			}
			Sprite.setTexture(TextureFly);
			TextureCounter = (TextureCounter + 1) % 16;
			if (sf::Mouse::getPosition(window).x > window.getSize().x / 2) this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureFlySize.x + 5, 0, TextureFlySize.x, TextureFlySize.y)); // +9 or 10 for hdr
			else this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureFlySize.x + 5, 0, TextureFlySize.x, TextureFlySize.y)); // +9 or 10 for hdr
			Sprite.setOrigin(TextureFlySize.x / 2, TextureSize.y / 2);
			if (!IsFlying) Sprite.setScale(Scale);
		}
		if (IsFlying) {

			temp_prev = Sprite.getRotation();
			Sprite.setRotation((Sprite.getRotation() + 90) / 2);
			if (temp_prev != Sprite.getRotation()) {
				if (Collision::PlayerWall(window, this, world))
				{
					Sprite.setRotation(temp_prev);
				}
			}
		}
		else {
			temp_prev = Sprite.getRotation();
			Sprite.setRotation(90);
			if (temp_prev != Sprite.getRotation()) {
				if (Collision::PlayerWall(window, this, world))
				{
					Sprite.setRotation(temp_prev);
				}
			}
		}
		IsFlying = true;
		JetForce = temp;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (!hflying)) {
		IsWalking = true;
		HSpeed = -HSpeedWalk;
		PrevPos = Sprite.getPosition();
		this->Sprite.move(HSpeed / 30, 0.0f);
		Collision::resolveBounds(window, this, world);
		if (Collision::PlayerWall(window, this, world))
		{
			Sprite.setPosition(PrevPos);
			HSpeed = 0.0f;
		}
		if (!IsFlying) {
			PrevPos = Sprite.getPosition();
			this->Sprite.move(0.0f, VSpeed / 30 + 0.5f*(GForce)*(1 / 900));
			Collision::resolveBounds(window, this, world);
			if (Collision::PlayerWall(window, this, world))
			{
				Sprite.setPosition(PrevPos);
				VSpeed = 0.0f;
			}
			else {
				VSpeed = VSpeed + (GForce) / 30;
				if (VSpeed > SpeedLimit) VSpeed = pVSpeed;
			}
			Sprite.setTexture(Texture);
			TextureCounter = (TextureCounter + 15) % 16;
			if (sf::Mouse::getPosition(window).x > window.getSize().x / 2) this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureSize.x, 0, TextureSize.x, TextureSize.y));
			else this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4 + 1)*TextureSize.x, 0, -TextureSize.x, TextureSize.y));
			Sprite.setOrigin(TextureSize.x / 2, TextureSize.y / 2);
			Sprite.setScale(Scale);
			temp_prev = Sprite.getRotation();
			Sprite.setRotation(0);
			if (temp_prev != Sprite.getRotation()) {
				if (Collision::PlayerWall(window, this, world))
				{
					Sprite.setRotation(temp_prev);
				}
			}

		}
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && (!hflying)) {
		IsWalking = true;
		HSpeed = HSpeedWalk;
		PrevPos = Sprite.getPosition();
		this->Sprite.move(HSpeed / 30, 0.0f);
		if (Collision::PlayerWall(window, this, world))
		{
			Sprite.setPosition(PrevPos);
			HSpeed = 0.0f;
		}
		if (!IsFlying) {
			PrevPos = Sprite.getPosition();
			this->Sprite.move(0.0f, VSpeed / 30 + 0.5f*(GForce)*(1 / 900));
			Collision::resolveBounds(window, this, world);
			if (Collision::PlayerWall(window, this, world))
			{
				Sprite.setPosition(PrevPos);
				VSpeed = 0.0f;
			}
			else {
				VSpeed = VSpeed + (GForce) / 30;
				if (VSpeed > SpeedLimit) VSpeed = pVSpeed;
			}
			Sprite.setTexture(Texture);
			TextureCounter = (TextureCounter + 1) % 16;
			if (sf::Mouse::getPosition(window).x > window.getSize().x / 2) this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureSize.x, 0, TextureSize.x, TextureSize.y));
			else this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4 + 1)*TextureSize.x, 0, -TextureSize.x, TextureSize.y));
			Sprite.setOrigin(TextureSize.x / 2, TextureSize.y / 2);
			Sprite.setScale(Scale);
			temp_prev = Sprite.getRotation();
			Sprite.setRotation(0);
			if (temp_prev != Sprite.getRotation()) {
				if (Collision::PlayerWall(window, this, world))
				{
					Sprite.setRotation(temp_prev);
				}
			}
		}
	}

	if (!IsFlying && !IsWalking) {
		PrevPos = Sprite.getPosition();
		this->Sprite.move(0.0f, VSpeed / 30 + 0.5f*(GForce)*(1 / 900)); // Check for collision
		Collision::resolveBounds(window, this, world);
		if (Collision::PlayerWall(window, this, world))
		{
			Sprite.setPosition(PrevPos);
			VSpeed = 0.0f;
		}
		else {
			VSpeed = VSpeed + (GForce) / 30;
			if (VSpeed > SpeedLimit) VSpeed = pVSpeed;
		}
		if (pIsFlying) {
			Sprite.setTexture(Texture);
		}
		if (sf::Mouse::getPosition(window).x > window.getSize().x/2) this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureSize.x, 0, TextureSize.x, TextureSize.y));
		else this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4 + 1)*TextureSize.x, 0, -TextureSize.x, TextureSize.y));
		if (pIsFlying) {
			Sprite.setScale(Scale);
			Sprite.setOrigin(TextureSize.x / 2, TextureSize.y / 2);
			temp_prev = Sprite.getRotation();
			Sprite.setRotation(0);
			if (temp_prev != Sprite.getRotation()) {
				if (Collision::PlayerWall(window, this, world))
				{
					Sprite.setRotation(temp_prev);
				}
			}
		}
	}
	Text.setPosition(Sprite.getPosition());
	Text.move(sf::Vector2f(Scale.x*TextureSize.x / 4, Scale.y*TextureSize.y / 2));
	if (Nitro < 1999) Nitro += 2;
	else Nitro = 2000;

	//positioning weapons
	if (CurrentWeapon != NULL) CurrentWeapon->update(Sprite.getPosition(), atan((sf::Mouse::getPosition(window).y + Sprite.getPosition().y - window.getSize().y/2 - CurrentWeapon->Sprite.getPosition().y) / (sf::Mouse::getPosition(window).x + Sprite.getPosition().x - window.getSize().x / 2 - CurrentWeapon->Sprite.getPosition().x)) * 180 / PI, window);
	if (OtherWeapon != NULL) OtherWeapon->update(Sprite.getPosition(), atan((sf::Mouse::getPosition(window).y + Sprite.getPosition().y - window.getSize().y / 2 - OtherWeapon->Sprite.getPosition().y) / (sf::Mouse::getPosition(window).x + Sprite.getPosition().x - window.getSize().x / 2 - OtherWeapon->Sprite.getPosition().x)) * 180 / PI, window);
	//positioning focus line for current weapon
	if (CurrentWeapon != NULL) {
		focusline.setPosition(CurrentWeapon->Sprite.getPosition());
		focusline.move(sf::Vector2f(Scale.x*TextureSize.x / 2, 0));
	}
	if (CurrentWeapon != NULL) {
		if (sf::Mouse::getPosition(window).x > window.getSize().x / 2) {
			focusline.setRotation(CurrentWeapon->Angle);
		}
		else if (sf::Mouse::getPosition(window).x < window.getSize().x / 2) {
			focusline.setRotation(CurrentWeapon->Angle + 180);
		}
		else {
			if (sf::Mouse::getPosition(window).y < window.getSize().y / 2) {
				focusline.setRotation(270);
			}
			else if (sf::Mouse::getPosition(window).y >= window.getSize().y / 2) {
				focusline.setRotation(90);
			}
		}
	}
}

void Player::releaseWeapon(std::vector<Weapon*> &unacquired)
{
	if (CurrentWeapon == NULL) return;
	else {
		CurrentWeapon->Movable = true;
		CurrentWeapon->Name = "";
		CurrentWeapon->Velocity.x = HSpeed;
		unacquired.push_back(CurrentWeapon);
		CurrentWeapon = NULL;
	}
}

void Player::acquireweapon(std::vector<Weapon*> &unacquired)	//thinking to allow acquire even when the weapon is moving
{
	for (int i = 0; i < unacquired.size(); i++) {
		if (unacquired[i]->Movable == false) {
			if (abs(Sprite.getPosition().x - unacquired[i]->Sprite.getPosition().x) < 20.0f && abs(Sprite.getPosition().y - unacquired[i]->Sprite.getPosition().y) < TextureSize.y / 2) {
				releaseWeapon(unacquired);
				CurrentWeapon = unacquired[i];
				unacquired.erase(unacquired.begin() + i);
				break;
			}
		}
	}
}

void Player::changeweapon()
{
	Weapon *temp = CurrentWeapon;
	CurrentWeapon = OtherWeapon;
	OtherWeapon = temp;
}

void Player::draw(sf::RenderWindow & window, int mainPlayer) {
	GameObject::draw(window);
	GameObject::drawText(window);

	if (CurrentWeapon != NULL) {
		CurrentWeapon->draw(window);
	}

	if (mainPlayer == Id) {
		if (CurrentWeapon != NULL) window.draw(focusline);
	}
	else {
		Text.setCharacterSize(25);
		window.draw(this->Text);
	}
}
