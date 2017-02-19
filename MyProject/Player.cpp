#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Player.h"
#include <string>



Player::Player(std::string &name, sf::Font textfont)
{
	Movable = true;
	TextureSize = sf::Vector2i(95, 154);	//164, 265 for hdr
	TextureFlySize = sf::Vector2i(101, 222);	//174, 382 for hdr
	Font = textfont;
	Scale = 1.0f;	//change for hdr (approx. 0.5f) test for this
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
	GForce = 400.0f;
	TextureCounter = 0;
	Text.setPosition(Sprite.getPosition());
	Text.move(sf::Vector2f(Scale*TextureSize.x / 4, Scale*TextureSize.y/2));
}


Player::~Player()
{
}

void Player::update()
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
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up))||(sf::Keyboard::isKeyPressed(sf::Keyboard::W))) {
		IsFlying = true;
		if (Nitro < 50) {
			JetForce = 0;
			Nitro = 20;
		}
		else Nitro -= 8;
		this->Sprite.move(0, VSpeed / 30 + 0.5f*(JetForce + GForce)*(1 / 900));
		VSpeed = VSpeed + (JetForce + GForce) / 30;
		if (VSpeed < -SpeedLimit*0.9f) VSpeed = pVSpeed;
		if (!pIsFlying) Sprite.setTexture(TextureFly);
		TextureCounter = (TextureCounter + 15) % 16;
		this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureFlySize.x+5, 0, TextureFlySize.x, TextureFlySize.y));	// +9 or 10 for hdr
		Sprite.setOrigin(TextureFlySize.x / 2, TextureSize.y / 2);
		Sprite.setScale(sf::Vector2f(Scale, Scale));
		Sprite.setRotation(0);
		JetForce = temp;
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down))||(sf::Keyboard::isKeyPressed(sf::Keyboard::S))) {
		IsFlying = true;
		if (Nitro < 50) {
			Nitro = 20;
			JetForce = 0;
		}
		else Nitro -= 8;
		this->Sprite.move(0, VSpeed / 30 + 0.5f*(-JetForce + GForce)*(1 / 900));
		VSpeed = VSpeed + (-JetForce + GForce) / 30;
		if (VSpeed > SpeedLimit) VSpeed = pVSpeed;
		if (!pIsFlying) Sprite.setTexture(TextureFly);
		TextureCounter = (TextureCounter + 15) % 16;
		this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureFlySize.x+5, 0, TextureFlySize.x, TextureFlySize.y)); // +9 or 10 for hdr
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
			Nitro += 5;
		}
		this->Sprite.move(-HSpeed / 30, VSpeed / 30 + 0.5f*(GForce)*(1 / 900));
		VSpeed = VSpeed + (GForce) / 30;
		if (VSpeed > SpeedLimit) VSpeed = pVSpeed;
		if (!IsFlying) Sprite.setTexture(TextureFly);
		if (!IsFlying) TextureCounter = (TextureCounter + 15) % 16;
		if (!IsFlying) this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureFlySize.x+5, 0, TextureFlySize.x, TextureFlySize.y)); // +9 or 10 for hdr
		Sprite.setOrigin(TextureFlySize.x / 2, TextureSize.y / 2);
		if (!IsFlying) Sprite.setScale(sf::Vector2f(Scale, Scale));
		int temp2 = Sprite.getRotation();
		if (temp2 == 0) temp2 = 360;
		if (IsFlying) Sprite.setRotation((temp2+270)/2);
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
			Nitro += 5;
		}
		this->Sprite.move(HSpeed / 30, VSpeed / 30 + 0.5f*(GForce)*(1 / 900));
		VSpeed = VSpeed + (GForce) / 30;
		if (VSpeed > SpeedLimit) VSpeed = pVSpeed;
		if (!IsFlying) Sprite.setTexture(TextureFly);
		if (!IsFlying) TextureCounter = (TextureCounter + 1) % 16;
		if (!IsFlying) this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureFlySize.x+5, 0, TextureFlySize.x, TextureFlySize.y)); // +9 or 10 for hdr
		Sprite.setOrigin(TextureFlySize.x / 2, TextureSize.y / 2);
		if (!IsFlying) Sprite.setScale(sf::Vector2f(Scale, Scale));
		if (IsFlying) Sprite.setRotation((Sprite.getRotation() + 90)/2);
		else Sprite.setRotation(90);
		if (IsFlying) {
			GForce = temp;
			VSpeed = temp3;
		}
		IsFlying = true;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left))&&(!hflying)) {
		if (IsFlying) {
			temp = GForce;
			temp3 = VSpeed;
			GForce = 0;
			VSpeed = 0;
		}
		else IsWalking = true;
		this->Sprite.move(-Speed/30, VSpeed / 30 + 0.5f*(GForce)*(1 / 900));
		VSpeed = VSpeed + (GForce) / 30;
		if (VSpeed > SpeedLimit) VSpeed = pVSpeed;
		if (!IsFlying) Sprite.setTexture(Texture);
		if (!IsFlying) TextureCounter = (TextureCounter + 15) % 16;
		if (!IsFlying) this->Sprite.setTextureRect(sf::IntRect((TextureCounter /4)*TextureSize.x, 0, TextureSize.x, TextureSize.y));
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
		this->Sprite.move(Speed/30, VSpeed / 30 + 0.5f*(GForce)*(1 / 900));
		VSpeed = VSpeed + (GForce) / 30;
		if (VSpeed > SpeedLimit) VSpeed = pVSpeed;
		if (!IsFlying) Sprite.setTexture(Texture);
		if (!IsFlying) TextureCounter = (TextureCounter + 1) % 16;
		if (!IsFlying) this->Sprite.setTextureRect(sf::IntRect((TextureCounter /4)*TextureSize.x, 0, TextureSize.x, TextureSize.y));
		if (!IsFlying) Sprite.setOrigin(TextureSize.x / 2, TextureSize.y / 2);
		if (!IsFlying) Sprite.setScale(sf::Vector2f(Scale, Scale));
		if (!IsFlying) Sprite.setRotation(0);
		if (IsFlying) {
			GForce = temp;
			VSpeed = temp3;
		}
	}
	
	if (!IsFlying && !IsWalking) {
		this->Sprite.move(0, VSpeed / 30 + 0.5f*(GForce)*(1 / 900));
		VSpeed = VSpeed + (GForce) / 30;
		if (VSpeed > SpeedLimit) VSpeed = pVSpeed;
		if (pIsFlying) Sprite.setTexture(Texture);
		if (pIsFlying) Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureSize.x, 0, TextureSize.x, TextureSize.y));
		if (!IsFlying) Sprite.setOrigin(TextureSize.x / 2, TextureSize.y / 2);
		if (!IsFlying) Sprite.setScale(sf::Vector2f(Scale, Scale));
		if (!IsFlying) Sprite.setRotation(0);
	}
	
	Text.setString(Name + " " + std::to_string(Nitro));
	Text.setPosition(Sprite.getPosition());
	Text.move(sf::Vector2f(Scale*TextureSize.x / 4, Scale*TextureSize.y / 2));
	if (Nitro < 1998) Nitro += 3;
	else Nitro = 2000;
}