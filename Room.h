#ifndef _GENERATOR_ROOM_DEFINED
#define _GENERATOR_ROOM_DEFINED

#include <vector>
#include <memory>
#include "Door.h"

namespace Generator
{
	class Room
	{
	public:
	public:
		Room() : Room(0,0,0,0) { }
		Room(int x1, int y1, int x2, int y2);
		virtual ~Room() { }

	public:
		/**
		 * Add a new door to the room
		 *
		 */
		void addDoor(const Door& door);

		/**
		 * Add a room leading towards the other room given as parameter
		 */
		std::shared_ptr<Door> addTowardsRoom(Room& otherRoom);

	private:
		/**
		 * Get a random x,y position on the wall facing towards the otherRoom 
		 * from this room.
		 */
		Door::RoomDoorDirection get_direction(Room& otherRoom);
	public: // data
		int iTlX;
		int iTlY;
		int iBrX;
		int iBrY;
		std::vector<std::shared_ptr<Door>> iDoors;
	};
}

#endif // _GENERATOR_ROOM_DEFINED

