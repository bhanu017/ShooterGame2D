#include "Collision.h"
#include "Player.h"
#include "GameObject.h"
#include "World.h"
#include <iostream>

Collision::Collision()
{

}


Collision::~Collision()
{

}



bool Collision::PlayerWall(sf::RenderWindow &window, Player *player, World &world)
{
	//std::cout << player->Sprite.getPosition().x << " " << player->Sprite.getPosition().y;
	/*int up_x_tile = (player->Sprite.getPosition().x - 10) / 20;
	int down_x_tile = (player->Sprite.getPosition().x + 10) / 20;
	int up_y_tile = (player->Sprite.getPosition().y - 10) / 20;
	int down_y_tile = (player->Sprite.getPosition().y + 10) / 20;*/
	//std::cout << x_tile << " " << y_tile << std::endl;

	/*if (up_x_tile < 0 || up_x_tile > 31)
		return true;
	if (down_x_tile < 0 || down_x_tile > 31)
		return true;
	if (up_y_tile < 0 || up_y_tile > 31)
		return true;
	if (down_y_tile < 0 || down_y_tile > 31)
		return true;*/
	/*if (world.tile_index[up_x_tile][up_y_tile] == 1)
	{
		//std::cout << "collided " << x_tile << " " << y_tile << std::endl;
		return true;
	}
	if (world.tile_index[down_x_tile][up_y_tile] == 1)
	{
		//std::cout << "collided " << x_tile << " " << y_tile << std::endl;
		return true;
	}
	if (world.tile_index[up_x_tile][down_y_tile] == 1)
	{
		//std::cout << "collided " << x_tile << " " << y_tile << std::endl;
		return true;
	}
	if (world.tile_index[down_x_tile][down_y_tile] == 1)
	{
		//std::cout << "collided " << x_tile << " " << y_tile << std::endl;
		return true;
	}*/

	int x_tile = (player->Sprite.getPosition().x) / 20;
	int y_tile = (player->Sprite.getPosition().y) / 20;

	if (x_tile < 0 || x_tile > 31)
	{
		//std::cout << "Out!! \n" ;
		return true;
	}
	if (y_tile < 0 || y_tile > 31)
	{
		//std::cout << "Out!! \n";
		return true;
	}

	if (world.tile_index[x_tile][y_tile] == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Collision::BulletWall()
{
	return false;
}
