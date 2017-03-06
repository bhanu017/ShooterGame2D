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

	int x_tile = (player->Sprite.getPosition().x) / world.TileSize;
	int y_tile = (player->Sprite.getPosition().y) / world.TileSize;

	/*if (x_tile < 0 || x_tile > 31)
	{
		//std::cout << "Out!! \n" ;
		return true;
	}
	if (y_tile < 0 || y_tile > 31)
	{
		//std::cout << "Out!! \n";
		return true;
	}
	*/

	if (world.tile_index[x_tile][y_tile] == 1)
	{
		return true;
	}
	if (x_tile - 1 >= 0) {
		if (y_tile - 1 >= 0) {
			if (world.tile_index[x_tile - 1][y_tile - 1] == 1) {
				if (player->Sprite.getGlobalBounds().intersects(sf::Rect<float>::Rect((x_tile - 1)*world.TileSize, (y_tile - 1)*world.TileSize, world.TileSize, world.TileSize))) return true;
			}
		}
		if (y_tile + 1 <= 31) {
			if (world.tile_index[x_tile - 1][y_tile + 1] == 1) {
				if (player->Sprite.getGlobalBounds().intersects(sf::Rect<float>::Rect((x_tile - 1)*world.TileSize, (y_tile + 1)*world.TileSize, world.TileSize, world.TileSize))) return true;
			}
		}
		if (world.tile_index[x_tile - 1][y_tile] == 1) {
			if (player->Sprite.getGlobalBounds().intersects(sf::Rect<float>::Rect((x_tile - 1)*world.TileSize, y_tile*world.TileSize, world.TileSize, world.TileSize))) return true;
		}
	}
	if (x_tile + 1 <= 31) {
		if (y_tile - 1 >= 0) {
			if (world.tile_index[x_tile + 1][y_tile - 1] == 1) {
				if (player->Sprite.getGlobalBounds().intersects(sf::Rect<float>::Rect((x_tile+ 1)*world.TileSize, (y_tile - 1)*world.TileSize, world.TileSize, world.TileSize))) return true;
			}
		}
		if (y_tile + 1 <= 31) {
			if (world.tile_index[x_tile + 1][y_tile + 1] == 1) {
				if (player->Sprite.getGlobalBounds().intersects(sf::Rect<float>::Rect((x_tile + 1)*world.TileSize, (y_tile + 1)*world.TileSize, world.TileSize, world.TileSize))) return true;
			}
		}
		if (world.tile_index[x_tile + 1][y_tile] == 1) {
			if (player->Sprite.getGlobalBounds().intersects(sf::Rect<float>::Rect((x_tile + 1)*world.TileSize, y_tile*world.TileSize, world.TileSize, world.TileSize))) return true;
		}
	}
	if (y_tile - 1 >= 0) {
		if (world.tile_index[x_tile][y_tile - 1] == 1) {
			if (player->Sprite.getGlobalBounds().intersects(sf::Rect<float>::Rect(x_tile*world.TileSize, (y_tile - 1)*world.TileSize, world.TileSize, world.TileSize))) return true;
		}
	}
	if (y_tile + 1 <= 31) {
		if (world.tile_index[x_tile][y_tile + 1] == 1) {
			if (player->Sprite.getGlobalBounds().intersects(sf::Rect<float>::Rect(x_tile*world.TileSize, (y_tile + 1)*world.TileSize, world.TileSize, world.TileSize))) return true;
		}
	}
	return false;
}

void Collision::resolveBounds(sf::RenderWindow & window, Player * player, World & world)
{
	if (player->Sprite.getPosition().x < 0.0f)
	{
		player->Sprite.setPosition(sf::Vector2f(0.0f, player->Sprite.getPosition().y));
		//player->VSpeed = 0;
	}
	else if (player->Sprite.getPosition().x >= 640.0f)
	{
		player->Sprite.setPosition(sf::Vector2f(639.0f, player->Sprite.getPosition().y));
		//player->VSpeed = 0;
	}
	if (player->Sprite.getPosition().y >= 640.0f)
	{
		player->Sprite.setPosition(sf::Vector2f(player->Sprite.getPosition().x, 639.0f));
		player->VSpeed = 0;
	}
	else if (player->Sprite.getPosition().y < 0.0f)
	{
		player->Sprite.setPosition(sf::Vector2f(player->Sprite.getPosition().x, 0.0f));
		player->VSpeed = 0;
	}
}

bool Collision::BulletWall()
{
	return false;
}
