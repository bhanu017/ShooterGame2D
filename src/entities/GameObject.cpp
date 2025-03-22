#include "GameObject.h"



GameObject::GameObject()
{

}


GameObject::~GameObject()
{

}

void GameObject::draw(sf::RenderWindow & window) {
	window.draw(this->Sprite);
	//window.draw(this->Text);
}

float GameObject::getScale()
{
	return Scale;
}
