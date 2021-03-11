#include "Door.h"

namespace Generator
{
	Door& Door::operator=(const Door& other)
	{
		iClosed = other.iClosed;
		iX = other.iX;
		iY = other.iY;
		return *this;
	}
}
