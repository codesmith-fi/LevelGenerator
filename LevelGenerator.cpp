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
#include <iostream>
#include <memory>
#include <time.h>
#include "Level.h"

using namespace Generator;

int main(int argc, char** argv)
{
	const int KLevelWidth = 80;
	const int KLevelHeight = 30;
	const int KNumberOfRooms = 12;
	const int KRoomMinWidth = 6;
	const int KRoomMinHeight = 6;
	const int KRoomMaxWidth = 25;
	const int KRoomMaxHeight = 25;
	const int KRetryCount = 10;

	srand(((unsigned int)time(NULL)));
	Level* level = new Level(KLevelWidth, KLevelWidth);

	std::cout << "Level width=" << level->width() << " height=" << level->height() << std::endl;
	std::cout << "Generating up to " << KNumberOfRooms << " rooms with size between ("
		<< KRoomMinWidth << "-" << KRoomMaxWidth << ","
		<< KRoomMaxWidth << "-" << KRoomMaxHeight << ")" << std::endl << std::endl;

	level->createRooms(
		KNumberOfRooms, 
		KRoomMinWidth, KRoomMinHeight, 
		KRoomMaxWidth, KRoomMaxHeight, 
		KRetryCount );

	for (int y = 0; y < level->height(); ++y) {
		for (int x = 0; x < level->width(); ++x) {
			unsigned char out = level->at(x,y).isOpen() ? ' ' : '*';
			if(!level->at(x, y).iIsCorridor) {
				out = level->at(x, y).isWall() ? '#' : out;
			}
			if (level->at(x, y).isDoor()) {				
				out = level->at(x, y).iDoorPtr->iClosed ?  '+' : '//';
			}
			std::cout << out;
		}
		std::cout << std::endl;
	}
	delete level;
	return 0;
}
