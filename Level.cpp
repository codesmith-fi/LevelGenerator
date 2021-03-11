/**
 * Level Gerator module
 *
 * Author: Erno Pakarinen
 * Email: erpakari@gmail.com
 * Date: March 11, 2021
 *
 * If you use this piece of code, honk me with an email. Free to use but the
 * origins should be mentioned in end product if you use this.
 *
 * MIT License
 */
#include <exception>
#include <stdexcept>
#include <stdlib.h>
#include "DebugLogger.h"
#include "Level.h"

namespace Generator
{
	Level::Level(unsigned int width, unsigned  int height) : iWidth(width), iHeight(height)
	{
		if (width <= 0 || height <= 0 ) {
			return;
		}

		// construct an empty tilemap, vector of vectors of Tile
		for (unsigned int y = 0; y < height; ++y) {
			
			TTileVector line;
			for (unsigned int x = 0; x < width; ++x) {
				line.push_back(std::make_shared<Tile>(Tile(false, 0, x, y)));
			}
			iTileMap.push_back(line);
		}
	}

	Level::~Level()
	{
	}

	std::shared_ptr<Tile> Level::at(unsigned int x, unsigned int y)
	{
		// Sanity check
		if (x >= iWidth && y >= iHeight) {
			throw std::length_error("Invalid level coordinates, out of range");
		}
		return iTileMap.at(y).at(x);
	}

	TRoomVector Level::rooms()
	{
		return iRooms;
	}

	std::shared_ptr<Room> Level::addRoom(unsigned int minWidth, unsigned int minHeight, 
		unsigned int maxWidth, unsigned int maxHeight)
	{
		return addRoomAt(-1, -1, minWidth, minHeight, maxWidth, maxHeight);
	}


	std::shared_ptr<Room> Level::addRoomAt(int x, int y, 
		unsigned int minWidth, unsigned int minHeight, 
		unsigned int maxWidth, unsigned int maxHeight)
	{
		// If no desired position given, get a random location
		if (x < 0 || y < 0) {
			x = rand() % iWidth;
			y = rand() % iHeight;
		}

		if (((unsigned int)x >= iWidth && (unsigned int)y >= iHeight) || !iWidth || !iHeight ) {
			throw std::length_error("Invalid level coordinates, out of range");
		}

		// Sanity check
		maxHeight = maxHeight < minHeight ? minHeight : maxHeight;
		maxWidth = maxWidth < minWidth ? minWidth : maxWidth;

		// Get random room dimensions in the range of given arguments
		int w = minWidth;
		int tX = maxWidth - minWidth;
		int h = minHeight;
		int tY = maxHeight - minHeight;
		if (tX > 0) {
			w = minWidth + (rand() % tX);
		}
		if (tY > 0) {
			h = minHeight + (rand() % tY);
		}

		std::shared_ptr<Room> room(new Room(x,y,x+w-1,y+h-1,false));
		if (checkArea(x, y, w, h)) {
			// carve area
			carveArea(room, x, y, w, h);
			room->iValid = true;
			if (iRooms.size()>0) {
				std::shared_ptr<Room> previousRoom = iRooms.at(iRooms.size()-1);
				std::shared_ptr<Door> door_ptr = room->addTowardsRoom(*previousRoom);
				iTileMap.at(door_ptr->iY).at(door_ptr->iX)->iDoorPtr = door_ptr;
				carve_corridor(*door_ptr, *previousRoom);
			}
			iRooms.push_back(room);
		}
		return room;
	}

	void Level::createRooms(int count,
		unsigned int minWidth, unsigned int minHeight,
		unsigned int maxWidth, unsigned int maxHeight, int retryCount)
	{
		for (int i = 0; i < count; ++i) {
			int retry = 0;
			while(retry < retryCount) {
				std::shared_ptr<Room> room(addRoom(minWidth, minHeight, maxWidth, maxHeight));
				if (room->iValid) {
					break;
				}
				retry++;
			}
		}
	}

	void Level::carve_corridor(const Door& origin, const Room& target)
	{
		int sX = origin.iX;
		int sY = origin.iY;
		int tX = target.iTlX + (target.iBrX - target.iTlX) / 2;
		int tY = target.iTlY + (target.iBrY - target.iTlY) / 2;

		int deltaX = 0;
		if (tX > sX) {
			deltaX++;
		}
		else if(tX < sX) {
			deltaX--;
		}

		int deltaY = 0;
		if (tY > sY) {
			deltaY++;
		}
		else if (tY < sY) {
			deltaY--;
		}
		/**
		 * TODO: Make a door at the corridor end point
		 */
		std::shared_ptr<Tile> tile = at(sX, sY);
		if (origin.iDirection == Door::RoomDoorDirection::UP) {
			while (sY > tY) {
				std::shared_ptr<Tile> tile = at(sX, sY);
				tile->iIsOpen = true;
				tile->iIsCorridor = true;
				sY--;
			}
			while (sX != tX) {
				std::shared_ptr<Tile> tile = at(sX, sY);
				tile->iIsOpen = true;
				tile->iIsCorridor = true;
				sX+=deltaX;
			}
		} else if (origin.iDirection == Door::RoomDoorDirection::DOWN) {
			while (sY < tY) {
				std::shared_ptr<Tile> tile = at(sX, sY);
				tile->iIsOpen = true;
				tile->iIsCorridor = true;
				sY++;
			}
			while (sX != tX) {
				std::shared_ptr<Tile> tile = at(sX, sY);
				tile->iIsOpen = true;
				tile->iIsCorridor = true;
				sX += deltaX;
			}
		} else if (origin.iDirection == Door::RoomDoorDirection::LEFT) {
			while (sX > tX) {
				std::shared_ptr<Tile> tile = at(sX, sY);
				tile->iIsOpen = true;
				tile->iIsCorridor = true;
				sX--;
			}
			while (sY != tY) {
				std::shared_ptr<Tile> tile = at(sX, sY);
				tile->iIsOpen = true;
				tile->iIsCorridor = true;
				sY += deltaY;
			}
		}
		else if (origin.iDirection == Door::RoomDoorDirection::RIGHT) {
			while (sX < tX) {
				std::shared_ptr<Tile> tile = at(sX, sY);
				tile->iIsOpen = true;
				tile->iIsCorridor = true;
				sX++;
			}
			while (sY != tY) {
				std::shared_ptr<Tile> tile = at(sX, sY);
				tile->iIsOpen = true;
				tile->iIsCorridor = true;
				sY += deltaY;
			}
		}
/*
		if (!tile->isDoor()) {
			std::shared_ptr<Door> door_ptr = std::shared_ptr<Door>(new Door(sX, sY, true));
			if (tile->iRoomPtr != NULL) {
				tile->iRoomPtr->iDoors.push_back(door_ptr);
				tile->iDoorPtr = door_ptr;
			}
		}
*/
	}

	bool Level::checkArea(unsigned int x, unsigned int y, 
		unsigned int w, unsigned int h)
	{
		bool res = true;
		for (unsigned int iy = y; iy < y+h && res; ++iy) {
			for (unsigned int ix = x; ix < x+w && res; ++ix) {
				if (iy >= iTileMap.size() || ix >= iTileMap.at(iy).size()) {
					res = false;
					break;
				}
				if(iTileMap.at(iy).at(ix)->iIsOpen) {
					res = false;
					break;
				}
				else {
					res = true;
				}
			}
		}
		return res;
	}

	void Level::carveArea(std::shared_ptr<Room> parent, 
		unsigned int x, unsigned int y, unsigned int w, unsigned int h)
	{
		for(unsigned int iy = y; iy < y+h; ++iy) {
			for(unsigned int ix = x; ix < x+w; ++ix) {
				std::shared_ptr<Tile> tile = iTileMap.at(iy).at(ix);
				tile->iIsOpen = true;
				tile->iRoomPtr = parent;
			}
		}
	}

}

