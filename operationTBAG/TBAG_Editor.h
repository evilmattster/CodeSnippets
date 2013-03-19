#ifndef RIEDEL_TBAG_EDITOR_H
#define RIEDEL_TBAG_EDITOR_H

#include "Globals.h"

class TBAG_Editor
{
public:
	//Constructor
	TBAG_Editor(){};
	bool load(const String&);		//Also plays the game from the start
	bool load(const String&, const String&); //Plays the game from room
	bool create(const String&);		//Makes a new game
	void runEdits(const String&);	//Loops the menu
	void runEditMenu();				//Runs the editor's action menu
	void makeRoom(bool);			//Bool switches the file override (true = dangerous)
	void debugRoom();				//Tests for obvious room errors
	void playFrom();				//Starts the game from a certain room
	void run();						//Plays from beginning

private:
	Room currentRoom;
	String gameName;
};

#endif
