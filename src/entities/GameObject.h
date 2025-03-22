#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	sf::Sprite Sprite;
	bool Movable;
	sf::Vector2i TextureSize;
	GameObject();
	~GameObject();
	void draw(sf::RenderWindow &window);
	float getScale();
private:
protected:
	sf::Font Font;
	sf::Text Text;
	sf::Texture Texture;
	float Scale = 1.0f;
};

