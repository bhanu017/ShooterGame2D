#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Player.h"
#include <string>



Player::Player(std::string &name, sf::Font textfont)
{
	Movable = true;
	TextureSize = sf::Vector2i(164, 265);
	TextureFlySize = sf::Vector2i(174, 382);
	Font = textfont;
	Scale = 0.5f;
	Name = name;
	Text.setString(name);
	Text.setFont(Font);
	Text.setCharacterSize((int) 36*Scale);
	Text.setFillColor(sf::Color::Green);
	//Text.setColor(sf::Color::White);
	//Text.setPosition();
	if (!Texture.loadFromFile("textures/walk_4.png")) {
		
	}
	if (!TextureFly.loadFromFile("textures/fly_4.png")) {

	}
	Sprite.setTexture(Texture);
	Sprite.setTextureRect(sf::IntRect(0,0, TextureSize.x, TextureSize.y));
	Sprite.setScale(sf::Vector2f(Scale, Scale));
	Health = 100;
	Nitro = 250;
	Speed = 3.0f;
	VSpeed = 0.0f;
	JetForce = -2000.0f;
	SpeedLimit = 300.0f;
	GForce = 500.0f;
	TextureCounter = 0;
	Text.setPosition(Sprite.getPosition());
	Text.move(sf::Vector2f(Scale*TextureSize.x / 4, Scale*TextureSize.y/2));
}


Player::~Player()
{
}

void Player::update()
{
	float temp = JetForce;
	float temp3;
	bool pIsFlying = IsFlying;
	IsFlying = false;
	IsWalking = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		IsFlying = true;
		if (Nitro < 3) JetForce = 0;
		else Nitro -= 3;
		this->Sprite.move(0, VSpeed / 30 + 0.5f*(JetForce + GForce)*(1 / 900));
		if (VSpeed > -SpeedLimit*0.7) VSpeed = VSpeed + (JetForce + GForce) / 30;
		if (!pIsFlying) Sprite.setTexture(TextureFly);
		TextureCounter = (TextureCounter + 15) % 16;
		this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureFlySize.x, 0, TextureFlySize.x, TextureFlySize.y));
		Sprite.setScale(sf::Vector2f(Scale, Scale));
		JetForce = temp;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		IsFlying = true;
		if (Nitro < 3) JetForce = 0;
		else Nitro -= 3;
		this->Sprite.move(0, VSpeed / 30 + 0.5f*(-JetForce + GForce)*(1 / 900));
		if (VSpeed < SpeedLimit) VSpeed = VSpeed + (-JetForce + GForce) / 30;
		if (!pIsFlying) Sprite.setTexture(TextureFly);
		TextureCounter = (TextureCounter + 15) % 16;
		this->Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureFlySize.x, 0, TextureFlySize.x, TextureFlySize.y));
		Sprite.setScale(sf::Vector2f(Scale, Scale));
		JetForce = temp;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (IsFlying) {
			temp = GForce;
			temp3 = VSpeed;
			GForce = 0;
			VSpeed = 0;
		}
		else IsWalking = true;
		this->Sprite.move(-Speed, VSpeed / 30 + 0.5f*(GForce)*(1 / 900));
		if (VSpeed < SpeedLimit) VSpeed = VSpeed + (GForce) / 30;
		if (!IsFlying) Sprite.setTexture(Texture);
		if (!IsFlying) TextureCounter = (TextureCounter + 15) % 16;
		if (!IsFlying) this->Sprite.setTextureRect(sf::IntRect((TextureCounter /4)*TextureSize.x, 0, TextureSize.x, TextureSize.y));
		if (!IsFlying) Sprite.setScale(sf::Vector2f(Scale, Scale));
		if (IsFlying) {
			GForce = temp;
			VSpeed = temp3;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (IsFlying) {
			temp = GForce;
			temp3 = VSpeed;
			GForce = 0;
			VSpeed = 0;
		}
		else IsWalking = true;
		this->Sprite.move(Speed, VSpeed / 30 + 0.5f*(GForce)*(1 / 900));
		if (VSpeed < SpeedLimit) VSpeed = VSpeed + (GForce) / 30;
		if (!IsFlying) Sprite.setTexture(Texture);
		if (!IsFlying) TextureCounter = (TextureCounter + 1) % 16;
		if (!IsFlying) this->Sprite.setTextureRect(sf::IntRect((TextureCounter /4)*TextureSize.x, 0, TextureSize.x, TextureSize.y));
		if (!IsFlying) Sprite.setScale(sf::Vector2f(Scale, Scale));
		if (IsFlying) {
			GForce = temp;
			VSpeed = temp3;
		}
	}
	if (!IsFlying && !IsWalking) {
		this->Sprite.move(0, VSpeed / 30 + 0.5f*(GForce)*(1 / 900));
		if (VSpeed < SpeedLimit) VSpeed = VSpeed + (GForce) / 30;
		if (pIsFlying) Sprite.setTexture(Texture);
		if (pIsFlying) Sprite.setTextureRect(sf::IntRect((TextureCounter / 4)*TextureSize.x, 0, TextureSize.x, TextureSize.y));
		if (pIsFlying) Sprite.setScale(sf::Vector2f(Scale, Scale));
	}
	Text.setString(Name + " " + std::to_string(VSpeed) + " " + std::to_string(Nitro));
	Text.setPosition(Sprite.getPosition());
	Text.move(sf::Vector2f(Scale*TextureSize.x / 4, Scale*TextureSize.y / 2));
	if (Nitro < 250) Nitro += 1;
	else Nitro = 250;
}