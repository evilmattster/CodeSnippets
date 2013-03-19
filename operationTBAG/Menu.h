#ifndef RIEDEL_MENU_H
#define RIEDEL_MENU_H

class Menu
{
public:
	Menu() {};
	Menu(unsigned short x) { opts = x; };
	int getRestrainedInput();	//Returns the user input of the menu
	int Size() { return opts; };

private:
	unsigned short opts;
};

#endif
