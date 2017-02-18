#pragma once
#include <SFML\Graphics.hpp>

class GameObject
{
public:
	GameObject();
	~GameObject();
	void draw(sf::RenderWindow &window);
private:
protected:
	bool Movable;
	sf::Font Font;
	float Scale = 1;
	sf::Text Text;
	sf::Texture Texture;
	sf::Vector2i TextureSize;
	sf::Sprite Sprite;
};

