#ifndef _GENERATOR_LEVEL_H_DEFINED
#define _GENERATOR_LEVEL_H_DEFINED

#include <vector>
#include <memory>
#include "Tile.h"
#include "Room.h"

/**
 * Represents a single level as a tilemap of tiles/
 * Tilemap = two dimensional square data structure
 */
namespace Generator
{
	typedef std::vector<std::shared_ptr<Tile>> TTileVector;
	typedef std::vector<std::shared_ptr<Room>> TRoomVector;

	class Level
	{
	public:
		Level() : Level(0, 0) { }
		Level(unsigned int width, unsigned int height);
		virtual ~Level();

	public: // Methods
		int width() { return iWidth; }
		int height() { return iHeight; }
		std::shared_ptr<Tile> at(unsigned int x, unsigned int y);
		std::shared_ptr<Room> addRoom(unsigned int minWidth, unsigned int minHeight, 
			unsigned int maxWidth, unsigned int maxHeight);
		std::shared_ptr<Room> addRoomAt(int x, int y, 
			unsigned int minWidth, unsigned int minHeight, 
			unsigned int maxWidth, unsigned int maxHeigh);
		void createRooms(int count, unsigned int minWidth, unsigned int minHeight,
			unsigned int maxWidth, unsigned int maxHeight, int retryCount = 10);
		TRoomVector rooms();

	private:
		bool checkArea(int unsigned x, unsigned int y, unsigned int w, unsigned int h);
		void carveArea(std::shared_ptr<Room> parent, unsigned int x, unsigned int y, 
			unsigned int w, unsigned int h);
		void carve_corridor(const Door& origin, const Room& target);

	private: // Data
		unsigned int iWidth;
		unsigned int iHeight;
		std::vector<TTileVector> iTileMap;
		TRoomVector iRooms;
	};
}

#endif // _GENERATOR_LEVEL_H_DEFINED
