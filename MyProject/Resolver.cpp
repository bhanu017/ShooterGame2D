#include "Resolver.h"



Resolver::Resolver()
{
}


Resolver::~Resolver()
{
}

void Resolver::CollisionResolver(sf::RenderWindow & window, Player * player, World & world)
{
	bool done = false;
	if (player->Sprite.getPosition().x < 0.0f)
	{
		player->Sprite.setPosition(sf::Vector2f(0.0f, player->Sprite.getPosition().y));
		//player->VSpeed = 0;
		done = true;
	}
	else if (player->Sprite.getPosition().x >= 640.0f)
	{
		player->Sprite.setPosition(sf::Vector2f(639.0f, player->Sprite.getPosition().y));
		//player->VSpeed = 0;
		done = true;
	}
	if (player->Sprite.getPosition().y >= 640.0f)
	{
		player->Sprite.setPosition(sf::Vector2f(player->Sprite.getPosition().x, 639.0f));
		//player->VSpeed = 0;
		done = true;
	}
	else if (player->Sprite.getPosition().y < 0.0f)
	{
		player->Sprite.setPosition(sf::Vector2f(player->Sprite.getPosition().x, 0.0f));
		//player->VSpeed = 0;
		done = true;
	}
	/*
		if (player->VSpeed > 0) {
			player->Sprite.setPosition(sf::Vector2f(player->Sprite.getPosition().x, player->Sprite.getPosition().y - 10));
			//player->VSpeed = 0;
		}
		else if (player->VSpeed < 0)
		{
			player->Sprite.setPosition(sf::Vector2f(player->Sprite.getPosition().x, player->Sprite.getPosition().y + 10));
			//player->VSpeed = 0;
		}
		if (player->HSpeed > 0)
		{
			player->Sprite.setPosition(sf::Vector2f(player->Sprite.getPosition().x - 10, player->Sprite.getPosition().y));
			//player->VSpeed = 0;
		}
		else if (player->HSpeed < 0)
		{
			player->Sprite.setPosition(sf::Vector2f(player->Sprite.getPosition().x + 10, player->Sprite.getPosition().y));
			//player->VSpeed = 0;
		}
	*/
	if (!done) {
		if (player->Sprite.getPosition().x == player->PrevPos.x) {
			player->Sprite.setPosition(player->Sprite.getPosition().x, player->PrevPos.y);
			player->VSpeed = 0;
		}
		else {
			player->Sprite.setPosition(player->PrevPos.x, player->Sprite.getPosition().y);
		}
	}
}
