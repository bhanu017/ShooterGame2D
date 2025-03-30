#include "GameObject.h"



GameObject::GameObject()
{

}


GameObject::~GameObject()
{

}

void GameObject::draw(sf::RenderWindow & window) {
	window.draw(this->Sprite);
}

sf::Vector2f GameObject::getScale()
{
	return Scale;
}

void GameObject::drawText(sf::RenderWindow & window) {
	window.draw(this->Text);
}
