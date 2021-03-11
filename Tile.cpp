#include "Tile.h"
#include "DebugLogger.h"

namespace Generator
{
	Tile& Tile::operator=(const Tile& other)
	{
		this->iIsOpen = other.iIsOpen;
		this->iTrapCount = other.iTrapCount;
		return *this;
	}

	void Tile::setParentRoom(std::shared_ptr<Room> room_ptr)
	{
		iRoomPtr = room_ptr;
	}

	std::shared_ptr<Room> Tile::parentRoom()
	{
		return iRoomPtr;
	}

	bool Tile::isOpen()
	{
		return iIsOpen;
	}

	bool Tile::isWall()
	{
		bool wall = false;

		if (iRoomPtr.get() != NULL) {
			if (iX == iRoomPtr->iTlX || iX == iRoomPtr->iBrX ||
				iY == iRoomPtr->iTlY || iY == iRoomPtr->iBrY) {
				wall = true;
			}
		}
/*		if (iRoomPtr != NULL) {
			LOG_INFO() << " BR: (" << iRoomPtr->iBrX << ", " << iRoomPtr->iBrY << ") Check wall at " << iX << "," << iY << ", res = " << wall;
			
		}
		*/
		return wall;
	}

	bool Tile::isDoor()
	{
		bool is_door = false;
		if (iRoomPtr.get() != NULL) {
			for (auto r : iRoomPtr->iDoors) {
				if (r->iX == iX && r->iY == iY) {
					is_door = true;
					break;
				}
			}
		}
		return is_door;
	}

}
