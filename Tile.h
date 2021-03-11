#ifndef _GENERATOR_TILE_H_DEFINED
#define _GENERATOR_TILE_H_DEFINED

#include <memory>
#include "Room.h"

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
		Tile(bool isOpen, int traps, int x, int y) 
			: iIsOpen(isOpen), iTrapCount(traps), iX(x), iY(y), iIsCorridor(0), iRoomPtr(NULL), iDoorPtr(NULL) { }
		virtual ~Tile() { }
		Tile& operator=(const Tile& other);

	public: // Methods
		void setParentRoom(std::shared_ptr<Room> room_ptr);
		std::shared_ptr<Room> parentRoom();
		bool isOpen();
		bool isWall();
		bool isDoor();

	public: // Properties
		std::shared_ptr<Room> iRoomPtr;
		std::shared_ptr<Door> iDoorPtr;
		bool iIsOpen;
		bool iIsCorridor;
		int iTrapCount;
		int iX;
		int iY;
	};
}

#endif // _GENERATOR_TILE_H_DEFINED
