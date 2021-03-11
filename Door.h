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
#ifndef _GENERATOR_DOOR_DEFINED
#define _GENERATOR_DOOR_DEFINED

namespace Generator
{
	class Door
	{
	public:
		enum class RoomDoorDirection {
			UNKNOWN,
			DOWN,
			UP,
			LEFT,
			RIGHT,
		};

	public:
		Door() : Door(0, 0, true) { }
		Door(int x, int y, bool closedDoor)
			: iX(x), iY(y), iClosed(closedDoor), iDirection(RoomDoorDirection::UNKNOWN) { }
		virtual ~Door() { }
		Door& operator=(const Door& other);
	public:
		int iX;
		int iY;
		bool iClosed;
		RoomDoorDirection iDirection;
	};
}

#endif // _GENERATOR_DOOR_DEFINED

