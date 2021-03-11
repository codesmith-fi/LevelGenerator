#ifndef _GENERATOR_TILE_H_DEFINED
#define _GENERATOR_TILE_H_DEFINED

namespace Generator
{
	/**
	 * Represents one tile in the tilemap
	 * Reasoning for separate class for Tile is that we can add special 
	 * properties in this structure. For example if the tile contains
	 * a trap.
	 * Properties and methods for handling tile
	 */
	class Tile
	{
	public:
		Tile() : Tile(false, 0, 0, 0) { }
		Tile(bool isOpen) : Tile(isOpen, 0, 0, 0) { }
		Tile(bool isOpen, int traps, int x, int y) : iIsOpen(isOpen), iTrapCount(traps), iX(x), iY(y) { }
		virtual ~Tile() { }
		Tile& operator=(const Tile& other);

	public: // Methods
		bool Open() { return iIsOpen; }

	public: // Properties
		bool iIsOpen;
		int iTrapCount;
		int iX;
		int iY;
	};
}

#endif // _GENERATOR_TILE_H_DEFINED