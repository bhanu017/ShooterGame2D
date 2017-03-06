#pragma once
#include <vector>
//#include "Collision.h"

class World
{
public:
	World();
	~World();

	std::vector<std::vector<int>> tile_index; // stores whether a tile at a given index is a solid tile or empty tile.
	int x_tiles;
	int y_tiles; // stores number of tiles in horizontal and vertical direction.
	float TileSize;
};

/*int World::x_tiles = 1;
int World::y_tiles = 1;
int World::tile_index.resize(1);
int World::tile_index[0].resize(1);*/