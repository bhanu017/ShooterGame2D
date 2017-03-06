#include "World.h"
#include <fstream>
#include <iostream>
using namespace std;


World::World()
{
	ifstream inFile;
	inFile.open("map.txt");

	inFile >> x_tiles;
	inFile >> y_tiles;
	int a, b;
	TileSize = 20.0f;

	tile_index.resize(x_tiles);
	for (int i = 0; i < x_tiles; i++)
	{
		tile_index[i].resize(y_tiles);
	}

	for (int j = 0; j < x_tiles; j++)
	{
		for (int i = 0; i < y_tiles; i++)
		{

			inFile >> a >> b >> tile_index[i][j];
		}
	}
	inFile.close();
	/*ofstream testout;
	testout.open("test.txt");
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


