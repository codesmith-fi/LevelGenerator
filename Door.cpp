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
