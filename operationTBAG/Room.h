#ifndef RIEDEL_ROOM_H
#define RIEDEL_ROOM_H

#include "Globals.h"
#include "Menu.h"

class Room
{
public:
	Room(){};
	Room(const String name){ roomName = name; };
	void runRoom();

	//Changes to the room stored in the room array
	void roomByIndex(const int);
	void setGameName(const String& x) { GameName = x; };

private:
	/*THESE ALL NEED PARSING UPON INPUT*/
	String roomName;
	String GameName;
	Menu menu;									//Can be in place of commands
	std::vector<String> nextRooms;				//Stores the names of possible next rooms
	std::vector<std::vector<String>> commands;	//Each vector is a command, each element is an equivilent command
	std::vector<std::vector<String>> resolves;	//Elements corrispond to command elements, the inner vector needs to be run in sequence
	/*END PARSED ATTRIBUTES*/

	//Private functions
	void runIntro(std::ifstream&);
	Menu loadMenu(std::ifstream&);
	void loadCommands(std::ifstream&);
	void loadResolution(std::ifstream&);
	void loadNextRooms(std::ifstream&);
};

#endif
