#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <math.h>
#include "Player.h"
#include <string>
#include "Collision.h"
#include "Resolver.h"

#define PI 3.14159265



Player::Player(std::string &name, sf::Font textfont)
{
	sf::Vector2i sizeOfTile = sf::Vector2i(20, 20);
	Movable = true;
	TextureSize = sf::Vector2i(95, 154);	//164, 265 for hdr
	TextureFlySize = sf::Vector2i(101, 222);	//174, 382 for hdr
	Font = textfont;
	Scale = 0.25f;	//change for hdr (approx. 0.5f) test for this
	Name = name;
	Text.setString(name);
	Text.setFont(Font);
	Text.setCharacterSize((int) 24*Scale);	//36 for hdr
	Text.setFillColor(sf::Color::Green);
	//Text.setColor(sf::Color::White);
	//Text.setPosition();
	if (!Texture.loadFromFile("textures/lwalk_4.png")) {
		
	}
	if (!TextureFly.loadFromFile("textures/lfly_4.png")) {

	}
	Sprite.setTexture(Texture);
	Sprite.setTextureRect(sf::IntRect(0,0, TextureSize.x, TextureSize.y));
	Sprite.setScale(sf::Vector2f(Scale, Scale));
	Health = 100;
	Nitro = 2000;
	Speed = 90.0f;
	VSpeed = 0.0f;
	HSpeed = 180.0f;
	JetForce = -1000.0f;
	SpeedLimit = 250.0f;
	LastDamager = "";
	GForce = 400.0f;
	TextureCounter = 0;
	Text.setPosition(Sprite.getPosition());
	Text.move(sf::Vector2f(Scale*TextureSize.x / 4, Scale*TextureSize.y/2));
	CurrentWeapon = new Weapon("weapon1", Font, Sprite.getPosition());
	OtherWeapon = new Weapon("weapon2", Font, Sprite.getPosition());
	focusline.setSize(sf::Vector2f(1000.0f, 2.0f));
	focusline.setOrigin(sf::Vector2f(0.0f, 1.0f));
	focusline.setFillColor(sf::Color::White);
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
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W))) {
		IsFlying = true;
		if (Nitro < 50) {
			JetForce = 0;
			Nitro = 20;
		}
		else Nitro -= 8;
		this->Sprite.move(0, VSpeed / 30 + 0.5f*(JetForce + GForce)*(1 / 900));// check for collision after this.
		//
		if (Collision::PlayerWall(window, this, world))
		{
			Resolver::CollisionResolver(window, this, world);
		}

		VSpeed = VSpeed + (JetForce + GForce) / 30;
		if (VSpeed < -SpeedLimit*0.9f) VSpeed = pVSpeed;
		if (!pIsFlying) Sprite.setTexture(TextureFly);
		TextureCounter = (TextureCounter + 15) % 16;
		if (sf::Mouse::getPosition(window).x > Sprite.getPosition().x) this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureFlySize.x + 5, 0, TextureFlySize.x, TextureFlySize.y));	// +9 or 10 for hdr
		else this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4 + 1)*TextureFlySize.x + 5, 0, -TextureFlySize.x, TextureFlySize.y));	// +9 or 10 for hdr
		Sprite.setOrigin(TextureFlySize.x / 2, TextureSize.y / 2);
		Sprite.setScale(sf::Vector2f(Scale, Scale));
		Sprite.setRotation(0);
		JetForce = temp;
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S))) {
		IsFlying = true;
		if (Nitro < 50) {
			Nitro = 20;
			JetForce = 0;
		}
		else Nitro -= 8;
		this->Sprite.move(0, VSpeed / 30 + 0.5f*(-JetForce + GForce)*(1 / 900)); // Check for collision after this
			if (Collision::PlayerWall(window, this, world))
			{
				Resolver::CollisionResolver(window, this, world);
			}

		VSpeed = VSpeed + (-JetForce + GForce) / 30;
		if (VSpeed > SpeedLimit) VSpeed = pVSpeed;
		if (!pIsFlying) Sprite.setTexture(TextureFly);
		TextureCounter = (TextureCounter + 15) % 16;
		if (sf::Mouse::getPosition(window).x > Sprite.getPosition().x) this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4 + 1)*TextureFlySize.x + 5, 0, -TextureFlySize.x, TextureFlySize.y));	// +9 or 10 for hdr
		else this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureFlySize.x + 5, 0, TextureFlySize.x, TextureFlySize.y));	// +9 or 10 for hdr
		Sprite.setOrigin(TextureFlySize.x / 2, TextureSize.y / 2);
		Sprite.setScale(sf::Vector2f(Scale, Scale));
		Sprite.setRotation(180);
		JetForce = temp;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		hflying = true;
		if (Nitro < 50) {
			Nitro = 20;
			JetForce = 0;
		}
		else Nitro -= 8;
		if (IsFlying) {
			temp = GForce;
			temp3 = VSpeed;
			GForce = 0;
			VSpeed = 0;
			Nitro += 4;
		}
		this->Sprite.move(-HSpeed / 30, VSpeed / 30 + 0.5f*(GForce)*(1 / 900)); // Check for collision

		if (Collision::PlayerWall(window, this, world))
		{
			Resolver::CollisionResolver(window, this, world);
		}

		VSpeed = VSpeed + (GForce) / 30;
		if (VSpeed > SpeedLimit) VSpeed = pVSpeed;
		if (!IsFlying) Sprite.setTexture(TextureFly);
		if (!IsFlying) TextureCounter = (TextureCounter + 15) % 16;
		if (!IsFlying) {
			if (sf::Mouse::getPosition(window).x > Sprite.getPosition().x) this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureFlySize.x + 5, 0, TextureFlySize.x, TextureFlySize.y)); // +9 or 10 for hdr
			else this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureFlySize.x + 5, 0, TextureFlySize.x, TextureFlySize.y)); // +9 or 10 for hdr
		}
		Sprite.setOrigin(TextureFlySize.x / 2, TextureSize.y / 2);
		if (!IsFlying) Sprite.setScale(sf::Vector2f(Scale, Scale));
		int temp2 = Sprite.getRotation();
		if (temp2 == 0) temp2 = 360;
		if (IsFlying) Sprite.setRotation((temp2 + 270) / 2);
		else Sprite.setRotation(-90);
		if (IsFlying) {
			GForce = temp;
			VSpeed = temp3;
		}
		IsFlying = true;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		hflying = true;
		if (Nitro < 50) {
			Nitro = 20;
			JetForce = 0;
		}
		else Nitro -= 8;
		if (IsFlying) {
			temp = GForce;
			temp3 = VSpeed;
			GForce = 0;
			VSpeed = 0;
			Nitro += 4;
		}
		this->Sprite.move(HSpeed / 30, VSpeed / 30 + 0.5f*(GForce)*(1 / 900)); // Check for collision
		
		if (Collision::PlayerWall(window, this, world))
		{
			Resolver::CollisionResolver(window, this, world);
		}

		VSpeed = VSpeed + (GForce) / 30;
		if (VSpeed > SpeedLimit) VSpeed = pVSpeed;
		if (!IsFlying) Sprite.setTexture(TextureFly);
		if (!IsFlying) TextureCounter = (TextureCounter + 1) % 16;
		if (!IsFlying) {
			if (sf::Mouse::getPosition(window).x > Sprite.getPosition().x) this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureFlySize.x + 5, 0, TextureFlySize.x, TextureFlySize.y)); // +9 or 10 for hdr
			else this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureFlySize.x + 5, 0, TextureFlySize.x, TextureFlySize.y)); // +9 or 10 for hdr
		}
		Sprite.setOrigin(TextureFlySize.x / 2, TextureSize.y / 2);
		if (!IsFlying) Sprite.setScale(sf::Vector2f(Scale, Scale));
		if (IsFlying) Sprite.setRotation((Sprite.getRotation() + 90) / 2);
		else Sprite.setRotation(90);
		if (IsFlying) {
			GForce = temp;
			VSpeed = temp3;
		}
		IsFlying = true;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (!hflying)) {
		if (IsFlying) {
			temp = GForce;
			temp3 = VSpeed;
			GForce = 0;
			VSpeed = 0;
		}
		else IsWalking = true;
		this->Sprite.move(-Speed / 30, VSpeed / 30 + 0.5f*(GForce)*(1 / 900)); // Check for collision

		if (Collision::PlayerWall(window, this, world))
		{
			Resolver::CollisionResolver(window, this, world);
		}

		VSpeed = VSpeed + (GForce) / 30;
		if (VSpeed > SpeedLimit) VSpeed = pVSpeed;
		if (!IsFlying) Sprite.setTexture(Texture);
		if (!IsFlying) TextureCounter = (TextureCounter + 15) % 16;
		if (!IsFlying) {
			if (sf::Mouse::getPosition(window).x > Sprite.getPosition().x) this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureSize.x, 0, TextureSize.x, TextureSize.y));
			else this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4 + 1)*TextureSize.x, 0, -TextureSize.x, TextureSize.y));
		}
			if (!IsFlying) Sprite.setOrigin(TextureSize.x / 2, TextureSize.y / 2);
		if (!IsFlying) Sprite.setScale(sf::Vector2f(Scale, Scale));
		if (!IsFlying) Sprite.setRotation(0);

		if (IsFlying) {
			GForce = temp;
			VSpeed = temp3;
		}
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && (!hflying)) {
		if (IsFlying) {
			temp = GForce;
			temp3 = VSpeed;
			GForce = 0;
			VSpeed = 0;
		}
		else IsWalking = true;
		this->Sprite.move(Speed / 30, VSpeed / 30 + 0.5f*(GForce)*(1 / 900)); // Check for collision

		if (Collision::PlayerWall(window, this, world))
		{
			Resolver::CollisionResolver(window, this, world);
		}

		VSpeed = VSpeed + (GForce) / 30;
		if (VSpeed > SpeedLimit) VSpeed = pVSpeed;
		if (!IsFlying) Sprite.setTexture(Texture);
		if (!IsFlying) TextureCounter = (TextureCounter + 1) % 16;
		if (!IsFlying) {
			if (sf::Mouse::getPosition(window).x > Sprite.getPosition().x) this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureSize.x, 0, TextureSize.x, TextureSize.y));
			else this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4 + 1)*TextureSize.x, 0, -TextureSize.x, TextureSize.y));
		}
		if (!IsFlying) Sprite.setOrigin(TextureSize.x / 2, TextureSize.y / 2);
		if (!IsFlying) Sprite.setScale(sf::Vector2f(Scale, Scale));
		if (!IsFlying) Sprite.setRotation(0);
		if (IsFlying) {
			GForce = temp;
			VSpeed = temp3;
		}
	}

	if (!IsFlying && !IsWalking) {
		this->Sprite.move(0, VSpeed / 30 + 0.5f*(GForce)*(1 / 900)); // Check for collision

		if (Collision::PlayerWall(window, this, world))
		{
			Resolver::CollisionResolver(window, this, world);
		}

		VSpeed = VSpeed + (GForce) / 30;
		if (VSpeed > SpeedLimit) VSpeed = pVSpeed;
		if (pIsFlying) Sprite.setTexture(Texture);
		if (pIsFlying) {
			if (sf::Mouse::getPosition(window).x > Sprite.getPosition().x) this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureSize.x, 0, TextureSize.x, TextureSize.y));
			else this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4 + 1)*TextureSize.x, 0, -TextureSize.x, TextureSize.y));
		}
		if (!IsFlying) Sprite.setOrigin(TextureSize.x / 2, TextureSize.y / 2);
		if (!IsFlying) Sprite.setScale(sf::Vector2f(Scale, Scale));
		if (!IsFlying) Sprite.setRotation(0);
	}
	Text.setPosition(Sprite.getPosition());
	Text.move(sf::Vector2f(Scale*TextureSize.x / 4, Scale*TextureSize.y / 2));
	if (Nitro < 1999) Nitro += 2;
	else Nitro = 2000;

	//positioning weapons
	if (CurrentWeapon != NULL) CurrentWeapon->update(Sprite.getPosition(), atan((sf::Mouse::getPosition(window).y - CurrentWeapon->Sprite.getPosition().y) / (sf::Mouse::getPosition(window).x - CurrentWeapon->Sprite.getPosition().x)) * 180 / PI, window);
	if (OtherWeapon != NULL) OtherWeapon->update(Sprite.getPosition(), atan((sf::Mouse::getPosition(window).y - OtherWeapon->Sprite.getPosition().y) / (sf::Mouse::getPosition(window).x - OtherWeapon->Sprite.getPosition().x)) * 180 / PI, window);
	//positioning focus line for current weapon
	if (CurrentWeapon != NULL) focusline.setPosition(CurrentWeapon->Sprite.getPosition());
	if (CurrentWeapon != NULL) {
		if (sf::Mouse::getPosition(window).x >= CurrentWeapon->Sprite.getPosition().x) {
			focusline.setRotation(CurrentWeapon->Angle);
		}
		else {
			focusline.setRotation(CurrentWeapon->Angle + 180);
		}
	}
}

void Player::releaseWeapon(std::vector<Weapon*> &unacquired)
{
	if (CurrentWeapon == NULL) return;
	else {
		CurrentWeapon->Movable = true;
		CurrentWeapon->Name = "";
		if (IsWalking) CurrentWeapon->Velocity.x = Speed;
		else if (IsFlying) CurrentWeapon->Velocity.x = HSpeed;
		unacquired.push_back(CurrentWeapon);
		CurrentWeapon = NULL;
	}
}

void Player::acquireweapon(std::vector<Weapon*> &unacquired)	//thinking to allow acquire even when the weapon is moving
{
	for (int i = 0; i < unacquired.size(); i++) {
		if (unacquired[i]->Movable == false) {
			if (abs(Sprite.getPosition().x - unacquired[i]->Sprite.getPosition().x) < 5.0f && abs(Sprite.getPosition().y - unacquired[i]->Sprite.getPosition().y) < TextureSize.y / 2) {
				releaseWeapon(unacquired);
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

void Player::draw(sf::RenderWindow & window) {
	window.draw(focusline);
	window.draw(this->Sprite);
	window.draw(this->Text);
}