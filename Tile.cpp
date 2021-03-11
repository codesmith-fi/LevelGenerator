#include "Tile.h"

namespace Generator
{
	Tile& Tile::operator=(const Tile& other)
	{
		this->iIsOpen = other.iIsOpen;
		this->iTrapCount = other.iTrapCount;
		return *this;
	}
}
