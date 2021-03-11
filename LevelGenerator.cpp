#include <iostream>
#include <memory>
#include "Level.h"

using namespace Generator;

int main(int argc, char** argv)
{
	std::shared_ptr<Level> level = std::make_shared<Level>(Level(100,40));

	std::cout << "Level width=" << level->width() << " height=" << level->height() << std::endl;

	for (int y = 0; y < level->height(); ++y) {
		for (int x = 0; x < level->width(); ++x) {
			unsigned char out = level->at(x,y)->isOpen() ? ' ' : '*';
			out = level->at(x, y)->isDoor() ? 'D' : out;
			out = level->at(x, y)->isWall() ? '#' : out;
			std::cout << out;
		}
		std::cout << std::endl;
	}
	return 0;
}
