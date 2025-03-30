#include "World.h"
#include <exception>
#include <fstream>

World::World(int MAP_NUM, sf::Vector2f scale)
{
	std::ifstream inFile;
	if (MAP_NUM == 1) {
		inFile.open("assets/maps/TiledMap_1.txt");
		if (!inFile.is_open()) {
			throw std::runtime_error("Failed to open map file");
		}
		Scale = scale;
		//Texture Initializations here
		tileSet.resize(6);
		tileSet[0].loadFromFile("assets/textures/brown.jpg");
		tileSet[1].loadFromFile("assets/textures/metal.jpg");
		tileSet[2].loadFromFile("assets/textures/blue.jpg");
		tileSet[3].loadFromFile("assets/textures/metal.jpg");
		tileSet[4].loadFromFile("assets/textures/yellow.jpg");
		tileSet[5].loadFromFile("assets/textures/green.jpg");

		TileSize = sf::Vector2f(tileSet[0].getSize().x * scale.x, tileSet[0].getSize().y * scale.y);
	}

	inFile >> x_tiles;
	inFile >> y_tiles;
	inFile >> NumTiles;
	spriteMap.resize(NumTiles);
	tile_index.resize(x_tiles);
	for (int i = 0; i < x_tiles; i++)
	{
		tile_index[i].resize(y_tiles);
	}
	int x = 0;
	for (int j = 0; j < y_tiles; j++)
	{
		for (int i = 0; i < x_tiles; i++)
		{
			inFile >> tile_index[i][j];
			if (tile_index[i][j] != 0) {
				spriteMap[x].setTexture(tileSet[(tile_index[i][j]-1)%6]);
				spriteMap[x].setScale(Scale);
				spriteMap[x].setPosition(TileSize.x * i, TileSize.y * j);
				x++;
			}
		}
	}
	inFile.close();
}

World::~World()
{
}

void World::draw(sf::RenderWindow & window)
{
	for (int i = 0; i < NumTiles; i++) {
		window.draw(spriteMap[i]);
	}
}
