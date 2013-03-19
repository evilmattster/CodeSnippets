#include "Globals.h"
#include "TBAG_Editor.h"
#include "TBAG_Player.h"

int main(int argc, char *argv[])
{
	//Set up player and editor objects
	TBAG_Player gamePlayer;
	TBAG_Editor gameEditor;
	
	/*================================================================================= FILE PASSED MAIN ===============================*/

	//Check if running a game, or editing
	if(argc > 1)
	{
		//If the editor tag was passed, run the editor
		if(argv[1] == "-editor") IS_EDITOR = true;

		//If the editor tag wasn't passed, try to open the game
		else if(gamePlayer.load(argv[1])) gamePlayer.run();

		//If the game couldn't open, send an error
		else std::cout<<"Could not open game files for "<<argv[1]<<"\n"; 
		
		//End the game as soon as the run loop stops
		return 0;
	}

	/*================================================================================= EDITOR MAIN ===============================*/

	//If it is in editor mode, set up the editor
	if(IS_EDITOR)
	{
		//The game name to edit
		char toEdit[100];

		//ask for input
		std::cout<<" What game would you like to edit?  ";
		std::cin>>toEdit;

		//Try to open that game
		if(gameEditor.load(toEdit)) gameEditor.run();
		else std::cout<<"Could not open game files for "<<argv[1]<<"\n"; 
		
		//End the game as soon as the run loop stops
		return 0;		 
	}

	/*================================================================================= STANDARD MAIN ===============================*/
	
	//Loop through the list until an option is hit
	while(true)
	{
		//Set up a choice variable
		char menuChoice;

		//Print out the options
		system("cls");
		std::cout<<"\n                    ***  Welcome to Operation TBAG!  ***\n\n"
			<<" What would you like to do?\n\n"
			<<"   1. Play an existing adventure\n"
			<<"   2. Edit an existing adventure\n"
			<<"   3. Create a new adventure\n"
			<<"   4. About Operation TBAG\n"
			<<"   5. Exit\n\n"
			<<" Please enter a numeric choice: ";
		std::cin>>menuChoice;

		//Resolve the input
		system("cls");
		char gameName[100];
		std::ifstream tester;
		switch(menuChoice)
		{
		case '1':		//Play a game
			//Ask what they want to play
			std::cout<<"\n What would you like to play? ";
			std::cin>>gameName;

			//Make sure the game can open
			if(gamePlayer.load(gameName)) { gamePlayer.run(); return 0; }

			//If it doesn't open, loop to the main menu
			else std::cout<<"The game files for "<<gameName<<" could not be found.\n\n";
			system("pause");
			break;

		case '2':		//Edit a game
			//Ask what they want to edit
			std::cout<<"\n What would you like to edit? ";
			std::cin>>gameName;

			//Make sure the game can open
			tester.open((GAME_PATH + "/" + gameName + "/" + gameName + GAME_FILE_EXTENTION).toChars());
			if(tester.fail())
			{
				std::cout<<"The game files for "<<gameName<<" could not be found.\n\n";
				system("pause");
			}
			else 
				gameEditor.runEdits(gameName);
			break;

		case '3':		//New game
			//Ask what they want to edit
			std::cout<<"\n What would you like to name your adventure? ";
			std::cin>>gameName;

			//Make sure the game can open
			if(gameEditor.create(gameName)) { gameEditor.run(); return 0; }

			//If it doesn't open, loop to the main menu
			else std::cout<<"The game structure for "<<gameName<<" could not be created.\n\n";
			system("pause");
			break;

		case '4':		//About Operation TBAG
			std::cout<<"\n\n\n\n\n\n                About Operation TBAG (Text Based Adventure Game)\n\n\n"
				<<"\n                         Created by: Matthew Riedel\n\n"
				"                  Made for \"Kent Hack Enough\" March 8-10, 2013\n\n"
				"                     Programmed in Visual Studio 2012 C++\n\n\n\n\n\n\n\n\n\n";
			system("pause");
			break;

		case '5':
			return 0;

		default:	//No proper choice
			std::cout<<"Please only enter a 1, 2, 3, 4, or 5\n\n";
			system("pause");
		}
	}

	//Terminate the progrm
	system("pause");
	return 0;
};
