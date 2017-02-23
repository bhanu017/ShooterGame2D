#pragma once
#include <SFML\Graphics.hpp>

class GameObject
{
public:
	sf::Sprite Sprite;
	bool Movable;
	sf::Vector2i TextureSize;
	GameObject();
	~GameObject();
	void draw(sf::RenderWindow &window);
private:
protected:
	sf::Font Font;
	float Scale = 1;
	sf::Text Text;
	sf::Texture Texture;
};

