#include "Menu.h"
#include "Globals.h"

//Returns the user input of the menu, can throw a parsing command
int Menu::getRestrainedInput()
{
	//Create the variable to test
	int in = -1;

	//Create a String to input to (trust me on this)
	char testIn[MAX_LINE_LENGTH];
	std::cout<<"\n Please enter a numeric choice: ";
	std::cin>>testIn;

	//Test if the data is numeric
	String temp(testIn);
	if(temp.length() > 1 || temp[0]-1 < '0' || temp[0] > char(opts + '0'))
		throw(temp);		//Throw the text to be caught by a higher function
	else
		in = temp[0]-1 - '0';	//Convert to an integer

	return in;
}