C++ Tilemap level generator

Author: Erno Pakarinen
Email: erpakari@gmail.com

GitHub link: https://github.com/codesmith-fi/LevelGenerator.git

Description

This is a OO approach to make a 2D Tilemap level generator. 

In it's current state it can create any size of 2D tilemap (dungeon level) with any number of any size rooms. See the LevelGenerator.cpp for usage. 

	std::shared_ptr<Level> level = std::make_shared<Level>(Level(KLevelWidth, KLevelWidth));
	level->createRooms(
		KNumberOfRooms, 
		KRoomMinWidth, KRoomMinHeight, 
		KRoomMaxWidth, KRoomMaxHeight, 
		KRetryCount );

Then just access tiles in the tilemap using

  level->at(x,y)

Tile class has properties describing the state of each tile.

