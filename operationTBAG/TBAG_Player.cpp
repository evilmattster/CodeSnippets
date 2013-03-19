#include "Globals.h"
#include "TBAG_Player.h"

bool TBAG_Player::load(const String &path)
{
	//load game file here===========================================
	Room temp(path);
	currentRoom = temp;
	currentRoom.runRoom();	//remove later==========================
	return true;			//later return whether it opened
}

void TBAG_Player::gotoRoom(const String &path)
{	
	Room temp(path);
	currentRoom = temp;
	currentRoom.runRoom();
}

void TBAG_Player::run()
{
	currentRoom.runRoom();
}