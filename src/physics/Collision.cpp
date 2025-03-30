#include "Collision.h"
//#include "Player.h"
//#include "GameObject.h"
//#include "World.h"
//#include "Weapon.h"
#include <iostream>

using namespace std;

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

	int x_tile = (player->Sprite.getPosition().x) / world.TileSize.x;
	int y_tile = (player->Sprite.getPosition().y) / world.TileSize.y;

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

	if (world.tile_index[x_tile][y_tile] != 0)
	{
		return true;
	}
	if (x_tile - 1 >= 0) {
		if (y_tile - 1 >= 0) {
			if (world.tile_index[x_tile - 1][y_tile - 1] != 0) {
				if (sf::Rect<float>(player->Sprite.getGlobalBounds().left + 10.0f*player->getScale().x,
								   player->Sprite.getGlobalBounds().top,
								   player->Sprite.getGlobalBounds().width - 20.0f*player->getScale().x,
								   player->Sprite.getGlobalBounds().height)
					.intersects(sf::Rect<float>((x_tile - 1)*world.TileSize.x,
											   (y_tile - 1)*world.TileSize.y,
											   world.TileSize.x,
											   world.TileSize.y))) return true;
			}
		}
		if (y_tile + 1 < world.y_tiles) {
			if (world.tile_index[x_tile - 1][y_tile + 1] != 0) {
				if (sf::Rect<float>(player->Sprite.getGlobalBounds().left + 10.0f*player->getScale().x,
								   player->Sprite.getGlobalBounds().top,
								   player->Sprite.getGlobalBounds().width - 20.0f*player->getScale().x,
								   player->Sprite.getGlobalBounds().height)
					.intersects(sf::Rect<float>((x_tile - 1)*world.TileSize.x,
											   (y_tile + 1)*world.TileSize.y,
											   world.TileSize.x,
											   world.TileSize.y))) return true;
			}
		}
		if (world.tile_index[x_tile - 1][y_tile] != 0) {
			if (sf::Rect<float>(player->Sprite.getGlobalBounds().left + 10.0f*player->getScale().x,
							   player->Sprite.getGlobalBounds().top,
							   player->Sprite.getGlobalBounds().width - 20.0f*player->getScale().x,
							   player->Sprite.getGlobalBounds().height)
				.intersects(sf::Rect<float>((x_tile - 1)*world.TileSize.x,
										   y_tile*world.TileSize.y,
										   world.TileSize.x,
										   world.TileSize.y))) return true;
		}
	}
	if (x_tile + 1 <= world.x_tiles) {
		if (y_tile - 1 >= 0) {
			if (world.tile_index[x_tile + 1][y_tile - 1] != 0) {
				if (sf::Rect<float>(player->Sprite.getGlobalBounds().left + 10.0f*player->getScale().x,
								   player->Sprite.getGlobalBounds().top,
								   player->Sprite.getGlobalBounds().width - 20.0f*player->getScale().x,
								   player->Sprite.getGlobalBounds().height)
					.intersects(sf::Rect<float>((x_tile+ 1)*world.TileSize.x,
											   (y_tile - 1)*world.TileSize.y,
											   world.TileSize.x,
											   world.TileSize.y))) return true;
			}
		}
		if (y_tile + 1 <= world.y_tiles) {
			if (world.tile_index[x_tile + 1][y_tile + 1] != 0) {
				if (sf::Rect<float>(player->Sprite.getGlobalBounds().left + 10.0f*player->getScale().x,
								   player->Sprite.getGlobalBounds().top,
								   player->Sprite.getGlobalBounds().width - 20.0f*player->getScale().x,
								   player->Sprite.getGlobalBounds().height)
					.intersects(sf::Rect<float>((x_tile + 1)*world.TileSize.x,
											   (y_tile + 1)*world.TileSize.y,
											   world.TileSize.x,
											   world.TileSize.y))) return true;
			}
		}
		if (world.tile_index[x_tile + 1][y_tile] != 0) {
			if (sf::Rect<float>(player->Sprite.getGlobalBounds().left + 10.0f*player->getScale().x,
							   player->Sprite.getGlobalBounds().top,
							   player->Sprite.getGlobalBounds().width - 20.0f*player->getScale().x,
							   player->Sprite.getGlobalBounds().height)
				.intersects(sf::Rect<float>((x_tile + 1)*world.TileSize.x,
										   y_tile*world.TileSize.y,
										   world.TileSize.x,
										   world.TileSize.y))) return true;
		}
	}
	if (y_tile - 1 >= 0) {
		if (world.tile_index[x_tile][y_tile - 1] != 0) {
			if (sf::Rect<float>(player->Sprite.getGlobalBounds().left + 10.0f*player->getScale().x,
							   player->Sprite.getGlobalBounds().top,
							   player->Sprite.getGlobalBounds().width - 20.0f*player->getScale().x,
							   player->Sprite.getGlobalBounds().height)
				.intersects(sf::Rect<float>(x_tile*world.TileSize.x,
										   (y_tile - 1)*world.TileSize.y,
										   world.TileSize.x,
										   world.TileSize.y))) return true;
		}
	}
	if (y_tile + 1 <= world.y_tiles) {
		if (world.tile_index[x_tile][y_tile + 1] != 0) {
			if (sf::Rect<float>(player->Sprite.getGlobalBounds().left + 10.0f*player->getScale().x,
							   player->Sprite.getGlobalBounds().top,
							   player->Sprite.getGlobalBounds().width - 20.0f*player->getScale().x,
							   player->Sprite.getGlobalBounds().height)
				.intersects(sf::Rect<float>(x_tile*world.TileSize.x,
										   (y_tile + 1)*world.TileSize.y,
										   world.TileSize.x,
										   world.TileSize.y))) return true;
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
	else if (player->Sprite.getPosition().x >= world.x_tiles*world.TileSize.x)
	{
		player->Sprite.setPosition(sf::Vector2f(world.x_tiles*world.TileSize.x-1, player->Sprite.getPosition().y));
		//player->VSpeed = 0;
	}
	if (player->Sprite.getPosition().y >= world.y_tiles*world.TileSize.y)
	{
		player->Sprite.setPosition(sf::Vector2f(player->Sprite.getPosition().x, world.y_tiles*world.TileSize.y-1));
		player->VSpeed = 0;
	}
	else if (player->Sprite.getPosition().y < 0.0f)
	{
		player->Sprite.setPosition(sf::Vector2f(player->Sprite.getPosition().x, 0.0f));
		player->VSpeed = 0;
	}
}

bool Collision::BulletWall(Bullet *bullet, World &world)
{
	if (bullet->Sprite.getPosition().x >= world.x_tiles*world.TileSize.x) {
		return true;
	}
	else if (bullet->Sprite.getPosition().y >= world.y_tiles*world.TileSize.y) {
		return true;
	}
	else if (bullet->Sprite.getPosition().y < 0.0f) {
		return true;
	}
	else if (bullet->Sprite.getPosition().x < 0.0f) {
		return true;
	}
	else {
		int x = bullet->Sprite.getPosition().x / world.TileSize.x;
		int y = bullet->Sprite.getPosition().y / world.TileSize.y;
		if (world.tile_index[x][y] != 0) {
			return true;
		}
	}
	return false;
}

bool Collision::WeaponWall(Weapon *weapon, World &world) {
	if (weapon->Sprite.getPosition().x >= world.x_tiles*world.TileSize.x) {
		return true;
	}
	else if (weapon->Sprite.getPosition().y >= world.y_tiles*world.TileSize.y) {
		return true;
	}
	else if (weapon->Sprite.getPosition().y < 0.0f) {
		return true;
	}
	else if (weapon->Sprite.getPosition().x < 0.0f) {
		return true;
	}
	else {
		int x = weapon->Sprite.getPosition().x / world.TileSize.x;
		int y = weapon->Sprite.getPosition().y / world.TileSize.y;
		if (world.tile_index[x][y] != 0) {
			return true;
		}
	}
	return false;
}
