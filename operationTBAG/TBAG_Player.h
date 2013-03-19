#ifndef RIEDEL_TBAG_PLAYER_H
#define RIEDEL_TBAG_PLAYER_H

#include "Globals.h"
#include "Room.h"

class TBAG_Player
{
public:
	//Constructor
	TBAG_Player() {};

	//Public functions
	bool load(const String&);
	void gotoRoom(const String&);
	void run();

private:
	Room currentRoom;
};

#endif
