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
		Room() : Room(0,0,0,0, false) { }
		Room(int x1, int y1, int x2, int y2, bool valid);
		virtual ~Room() { }

	public:
		bool isInside(int x, int y) const;
		bool isOnEdges(int x, int y) const;

		/**
		 * Add a new door to the room
		 *
		 */
		void addDoor(std::shared_ptr<Door> door);

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
		bool iValid;
		int iTlX;
		int iTlY;
		int iBrX;
		int iBrY;
		std::vector<std::shared_ptr<Door>> iDoors;
	};
}

#endif // _GENERATOR_ROOM_DEFINED

