#pragma once
#include <string>
#include <vector>
#include <map>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Object {
public:
	int GetPropertyInt(std::string name);
	float GetPropertyFloat(std::string name);
	std::string GetPropertyString(std::string name);
	std::string name;
	std::string type;
	sf::Rect <int> rect;
	std::map <std::string, std::string> properties;//All properties of the object. Values are stored as strings and mapped by strings(names provided in editor).
};

struct Layer {
	int opacity;
	std::vector <sf::Sprite> tiles;
};

class Level
{
public:
	Level();
	virtual ~Level();
	//Loads the map. Returns false if it fails.
	bool LoadFromFile(std::string filename);
	//Returns the first object found with the given name. This is why we need unique names :)
	Object GetObject(std::string name);
	//Returns true if the given pixel is solid.
	bool IsSolidPixel(int x, int y);
	//Returns true if the given tile is solid. DO WE NEED THIS?
	bool IsSolidTile(int x, int y);
	//Moves the map. Although I would recommend using a view instead in most cases.
	void Move(int xStep, int yStep);
	//Set the area to draw. This rect is usually provided directly from the view you are using.
	void SetDrawingBounds(sf::Rect<float> bounds);
	//Draws the map to the provided window.
	void Draw(sf::RenderWindow &window);

private:
	//Width(tiles), height(tiles), tile width(pixels), tile height(pixels) of the map.
	int width, height, tileWidth, tileHeight;
	//Used to offset the tile number.
	int firstTileID;
	//Used to clip anything off screen.
	sf::Rect <float> drawingBounds;
	//The tileset image.
	sf::Image tilesetImage;
	//This stores all the solid areas (objects with type 'solid'). This gets checked by the IsSolid function.
	std::vector <sf::Rect <int> > solidObjects;
	//This stores all objects (including 'solid' types)
	std::vector <Object> objects;
	//This stores each layer of sprites/tiles so they can be drawn in order.
	std::vector <Layer> layers;
};

