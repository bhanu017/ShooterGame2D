#include "World.h"
#include <fstream>
#include <iostream>
using namespace std;


World::World(int MAP_NUM)
{
	ifstream inFile;
	if (MAP_NUM == 1) {
		inFile.open("assets/maps/map1.txt");
		TileSize = 32.0f;
		Scaled = 0.25f;
		//Texture Initializations here
		tileSet.resize(7);
		tileSet[0].loadFromFile("assets/textures/brown.jpg");
		tileSet[1].loadFromFile("assets/textures/metal.jpg");
		tileSet[2].loadFromFile("assets/textures/orange.jpg");
		tileSet[3].loadFromFile("assets/textures/blue.jpg");
		tileSet[4].loadFromFile("assets/textures/green.jpg");
		tileSet[5].loadFromFile("assets/textures/yellow.jpg");
		tileSet[6].loadFromFile("assets/textures/red.jpg");
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
			if ((tile_index[i][j] > 3) && (tile_index[i][j] < 8)) tile_index[i][j] = 4;
			if (tile_index[i][j] >= 8) tile_index[i][j] -= 3;
			if (tile_index[i][j] != 0) {
				spriteMap[x].setTexture(tileSet[tile_index[i][j]-1]);
				spriteMap[x].setScale(Scaled, Scaled);
				spriteMap[x].setPosition(sf::Vector2f(i*TileSize, j*TileSize));
				x++;
			}
		}
	}
	inFile.close();
	/*ofstream testout;
	testout.open("assets/maps/test.txt");
	for (int j = 0; j < y_tiles; j++)
	{
		for (int i = 0; i < x_tiles; i++)
		{
			testout << i << "	" << j << "	" << tile_index[i][j] << endl;
		}
	}
	testout.close();*/
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


