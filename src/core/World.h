#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
//#include "Collision.h"

class World
{
public:
	World(int MAP_NUM, sf::Vector2f scale);
	~World();

	std::vector<std::vector<int>> tile_index; // stores whether a tile at a given index is a solid tile or empty tile.
	int x_tiles;
	int y_tiles; // stores number of tiles in horizontal and vertical direction.
	sf::Vector2f TileSize;
	std::vector<sf::Sprite> spriteMap;
	std::vector<sf::Texture> tileSet;
	int NumTiles;
	void draw(sf::RenderWindow &window);
	sf::Vector2f Scale = sf::Vector2f(1.0f, 1.0f);
};
