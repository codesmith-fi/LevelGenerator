#include <iostream>
#include <memory>
#include <time.h>
#include "Level.h"

using namespace Generator;

int main(int argc, char** argv)
{
	srand(((unsigned int)time(NULL)));

	std::shared_ptr<Level> level = std::make_shared<Level>(Level(100,40));

	std::cout << "Level width=" << level->width() << " height=" << level->height() << std::endl;

	level->createRooms(14, 6, 6, 15, 15, 10);

	for (int y = 0; y < level->height(); ++y) {
		for (int x = 0; x < level->width(); ++x) {
			unsigned char out = level->at(x,y)->isOpen() ? ' ' : '*';
			out = level->at(x, y)->isWall() ? '#' : out;
			if (level->at(x, y)->isDoor()) {				
				out = level->at(x, y)->iDoorPtr->iClosed ?  '+' : '//';
			}
			std::cout << out;
		}
		std::cout << std::endl;
	}
	return 0;
}
