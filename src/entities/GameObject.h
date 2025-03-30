#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	sf::Sprite Sprite;
	bool Movable;
	sf::Vector2f TextureSize;
	GameObject();
	~GameObject();
	void draw(sf::RenderWindow &window);
	void drawText(sf::RenderWindow &window);
	sf::Vector2f getScale();
private:
protected:
	sf::Font Font;
	sf::Text Text;
	sf::Texture Texture;
	sf::Vector2f Scale = sf::Vector2f(1.0f, 1.0f);
};
