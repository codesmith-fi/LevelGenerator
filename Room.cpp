#include <stdlib.h>
#include <exception>
#include <stdexcept>
#include "Room.h"
#include "DebugLogger.h"

namespace Generator
{
	Room::Room(int x1, int y1, int x2, int y2, bool valid) : iTlX(x1), iTlY(y1), iBrX(x2), iBrY(y2), iValid(valid)
	{
	}

	void Room::addDoor(const Door& door)
	{
		// Door must be in the room borders but not in the corners
		// X******X
		// *XXXXXX*   -> * = valid door places
		// *XXXXXX*   -> X = invalid door places
		// *XXXXXX*
		// X******X
		if( (door.iY == iTlY && (door.iX > iTlX && door.iX < iBrX)) ||
			(door.iY == iBrY && (door.iX > iTlX && door.iX < iBrX)) ||
			(door.iX == iTlX && (door.iY > iTlY && door.iY < iBrY)) ||
			(door.iX == iBrX && (door.iY > iTlY && door.iY < iBrY))) 
		{
			std::shared_ptr<Door> door_ptr = std::shared_ptr<Door>(new Door(door));
			iDoors.push_back(door_ptr);
		}
	}

	std::shared_ptr<Door> Room::addTowardsRoom(Room& otherRoom)
	{
		
		int x = 0;
		int y = 0;

		// find out the wall where to put the door to

		Door::RoomDoorDirection a = get_direction(otherRoom);
		bool closed = (rand() % 2) ? true : false;
		std::shared_ptr<Door> new_door_ptr = std::shared_ptr<Door>(new Door(0, 0, closed));

		switch (a) {
			case Door::RoomDoorDirection::DOWN:
			{
				new_door_ptr->iY = iBrY;
				new_door_ptr->iX = iTlX + (rand() % ((iBrX - iTlX) - 2)) + 1;
				break;
			}
			case Door::RoomDoorDirection::UP:
			{
				new_door_ptr->iY = iTlY;
				new_door_ptr->iX = iTlX + (rand() % ((iBrX - iTlX) - 2)) + 1;
				break;
			}
			case Door::RoomDoorDirection::LEFT:
			{
				new_door_ptr->iX = iTlX;
				new_door_ptr->iY = iTlY + (rand() % ((iBrY - iTlY) - 2)) + 1;
				break;
			}
			case Door::RoomDoorDirection::RIGHT:
			{
				new_door_ptr->iX = iBrX;
				new_door_ptr->iY = iTlY + (rand() % ((iBrY - iTlY) - 2)) + 1;
				break;
			}
			case Door::RoomDoorDirection::UNKNOWN:
			default:
			{
				throw std::invalid_argument("Invalid coordinates for new room");
				break;
			}
		}
		new_door_ptr->iDirection = a;
		iDoors.push_back(new_door_ptr);
		return new_door_ptr;
	}

	Door::RoomDoorDirection Room::get_direction(Room& otherRoom)
	{
		Door::RoomDoorDirection a = Door::RoomDoorDirection::UNKNOWN;
		int r = rand() % 2;
		if (otherRoom.iTlX < iTlX) {
			// Old room on the left side below this room
			if (otherRoom.iTlY > iTlY) {
				a = (r == 0 ? Door::RoomDoorDirection::DOWN : Door::RoomDoorDirection::LEFT);
			}
			// Old room on the left side above this room
			else if (otherRoom.iTlY < iTlY) {
				a = (r == 0 ? Door::RoomDoorDirection::UP : Door::RoomDoorDirection::LEFT);
			}
			else {
				// Rooms are aligned horizontally but old is on the left side
				a = Door::RoomDoorDirection::LEFT;
			}
		}
		else if (otherRoom.iTlX > iTlX) {
			// Old room on the right side below this room
			if (otherRoom.iTlY > iTlY) {
				a = (r == 0 ? Door::RoomDoorDirection::DOWN: Door::RoomDoorDirection::RIGHT);
			}
			// Old room on the right side above this room
			else if (otherRoom.iTlY < iTlY) {
				a = (r == 0 ? Door::RoomDoorDirection::UP: Door::RoomDoorDirection::RIGHT);
			}
			// Rooms are aligned horizontally but old is on the right side
			else {
				a = Door::RoomDoorDirection::RIGHT;
			}
		}
		else {
			// Rooms are aligned vertically, a wall facing towards the old room
			a = otherRoom.iTlY < iTlY ? Door::RoomDoorDirection::UP : Door::RoomDoorDirection::DOWN;
		}
		return a;
	}

}
