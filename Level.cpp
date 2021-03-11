#include <exception>
#include <stdexcept>
#include "Level.h"

namespace Generator
{
	Level::Level(int width, int height) : iWidth(width), iHeight(height)
	{
		// construct an empty tilemap, vector of vectors of Tile
		for (int y = 0; y < height; ++y) {
			TileVector line;
			for (int x = 0; x < width; ++x) {
				line.push_back(std::make_shared<Tile>(Tile(false, 0, x, y)));
			}
			iTileMap.push_back(line);
		}
	}

	Level::~Level()
	{
	}

	std::shared_ptr<Tile> Level::at(int x, int y)
	{
		// Sanity check
		if (x >= iWidth && y >= iHeight) {
			throw std::length_error("Invalid level coordinates, out of range");
		}
		return iTileMap.at(y).at(x);
	}
}