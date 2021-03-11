#ifndef _GENERATOR_LEVEL_H_DEFINED
#define _GENERATOR_LEVEL_H_DEFINED

#include <vector>
#include <memory>
#include "Tile.h"

/**
 * Represents a single level as a tilemap of tiles/
 * Tilemap = two dimensional square data structure
 */
namespace Generator
{
	typedef std::vector<std::shared_ptr<Tile>> TileVector;

	class Level
	{
	public:
		Level() : Level(0, 0) { }
		Level(int width, int height);
		virtual ~Level();

	public: // Methods
		int width() { return iWidth; }
		int height() { return iHeight; }
		std::shared_ptr<Tile> at(int x, int y);
	private: // Data
		int iWidth;
		int iHeight;
		std::vector<TileVector> iTileMap;
	};
}

#endif // _GENERATOR_LEVEL_H_DEFINED
