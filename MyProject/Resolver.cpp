#include "Resolver.h"



Resolver::Resolver()
{
}


Resolver::~Resolver()
{
}

void Resolver::CollisionResolver(sf::RenderWindow & window, Player * player, World & world)
{
	if (player->Sprite.getPosition().x < 0)
	{
		player->Sprite.setPosition(sf::Vector2f(1.0f, player->Sprite.getPosition().y));
		player->VSpeed = 0;
	}
	else if (player->Sprite.getPosition().y < 0 )
	{
		player->Sprite.setPosition(sf::Vector2f(player->Sprite.getPosition().x, 1.0f));
		player->VSpeed = 0;
	}
	else if (player->Sprite.getPosition().y > 640)
	{
		player->Sprite.setPosition(sf::Vector2f(player->Sprite.getPosition().x, 639.0f));
		player->VSpeed = 0;
	}
	else if (player->Sprite.getPosition().x < 640)
	{
		player->Sprite.setPosition(sf::Vector2f(639.0f, player->Sprite.getPosition().y));
		player->VSpeed = 0;
	}
	else if (player->VSpeed > 0)
	{
		player->Sprite.setPosition(sf::Vector2f(player->Sprite.getPosition().x, player->Sprite.getPosition().y - 10));
		player->VSpeed = 0;
	}
	else if (player->VSpeed < 0)
	{
		player->Sprite.setPosition(sf::Vector2f(player->Sprite.getPosition().x, player->Sprite.getPosition().y + 10));
		player->VSpeed = 0;
	}
	else if (player->HSpeed > 0)
	{
		player->Sprite.setPosition(sf::Vector2f(player->Sprite.getPosition().x - 10, player->Sprite.getPosition().y));
		//player->VSpeed = 0;
	}
	else if (player->VSpeed > 0)
	{
		player->Sprite.setPosition(sf::Vector2f(player->Sprite.getPosition().x + 10, player->Sprite.getPosition().y));
		//player->VSpeed = 0;
	}

}
