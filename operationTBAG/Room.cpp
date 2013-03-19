#include "Room.h"

void Room::runRoom()
{
	if(GameName == "") GameName = roomName;
	while(true)
	{
		//Wipe the screen
		system("cls");

		//Open the Room textFile
		std::ifstream roomFile;
		roomFile.open((GAME_PATH + "/" + GameName + ROOM_FOLDER_PATH + "/" + roomName + ROOM_FILE_EXTENTION).toChars());
		if(roomFile.fail()) { std::cout<<"Could not load room "<<(GAME_PATH + "/" + GameName + ROOM_FOLDER_PATH + "/" + roomName + ROOM_FILE_EXTENTION).toChars()<<"\n"; return; }

		//Put the intro on the screen
		runIntro(roomFile);

		//If there are commands, load them for use
		int ResolutionIndex;
		commands.clear();
		loadCommands(roomFile);

		//If there is a menu, load it to the screen, beine weary of thrown Strings
		menu = loadMenu(roomFile);
		if(menu.Size() > 0)
		{
			try { ResolutionIndex = menu.getRestrainedInput(); }
			catch(String command)
			{
				ResolutionIndex = parseStr(commands, command);
			}
		}
		else
		{
			String tempIn;
			std::cout<<"What would you like to do? ";
			std::cin>>tempIn;
			ResolutionIndex = parseStr(commands, tempIn);
		}

		//Check for invalid stuff
		if(ResolutionIndex == -1)
		{
			std::cout<<"Unrecognized input\n";
			_sleep(800);
		}
		else
		{
			//Prep the resulution vector to resolve the selection
			resolves.clear();
			loadResolution(roomFile);

			//Prep the next room vector to resolve the selection
			nextRooms.clear();
			loadNextRooms(roomFile);

			//Resolve the menu (returns true on room change)
			int nextRoom;
			nextRoom = parseResolve(resolves, ResolutionIndex);

			//Change rooms
			std::cout<<roomName;
			if(nextRoom > -1 && nextRoom < nextRooms.size())
				roomName = nextRooms[nextRoom];
		}
		//Close the file when complete
		roomFile.close();
	}
}

//Private functions
void Room::runIntro(std::ifstream& inFile)
{
	//Rewind the file and wipe the screen
	inFile.seekg(0);
	system("cls");

	//Get the first line of the file
	char tempLine[MAX_LINE_LENGTH + 1];
	inFile.getline(tempLine, MAX_LINE_LENGTH);

	//Look for the [INTRO]
	while(formatString(tempLine) != "[INTRO]" && !inFile.eof())
		inFile.getline(tempLine, MAX_LINE_LENGTH);
	
	//Skip past the intro key
	inFile.getline(tempLine, MAX_LINE_LENGTH);

	//Print every line until [END_INTRO]
	while(formatString(tempLine) != "[END_INTRO]" && !inFile.eof())
	{

		//If a [PAUSE] appears, run pause then cls and move on
		if(formatString(tempLine) == "[PAUSE]") 
		{ 
			system("pause"); 
			system("cls"); 
		}

		//Print out all of the lines on new lines
		else std::cout<<tempLine<<std::endl;

		//Increment looper
		inFile.getline(tempLine, MAX_LINE_LENGTH);
	}
}
void Room::loadCommands(std::ifstream& inFile)
{
	//Rewind the file
	inFile.seekg(0);

	//Get the first line of the file
	char tempLine[MAX_LINE_LENGTH + 1];
	inFile.getline(tempLine, MAX_LINE_LENGTH);

	//Look for [COMMAND], if one is not found simply return
	while(formatString(tempLine) != "[COMMAND]" && !inFile.eof())
		inFile.getline(tempLine, MAX_LINE_LENGTH);
	
	//Skip past the command key
	inFile.getline(tempLine, MAX_LINE_LENGTH);

	//Look for [END_CMD]
	while(formatString(tempLine) != "[END_CMD]" && !inFile.eof())
	{
		//Set up the temporaries
		std::vector<String> tempVector;
		String nextCommand("");

		//Loop through the line character by character getting commands
		int i = 0;
		while(i < String(tempLine) && tempLine[i] != '<') ++i;
		++i;
		while(i < String(tempLine) && tempLine[i] != '>')
		{
			if(tempLine[i] != ',') nextCommand += tempLine[i];
			else
			{
				//Push the command onto the vector
				tempVector.push_back(nextCommand);
				nextCommand = "";
			}
			++i;
		}
		//Push the command onto the vector
		tempVector.push_back(nextCommand);
		nextCommand = "";

		//Push the vector onto the vector
		commands.push_back(tempVector);
		tempVector.clear();

		//Get the next line
		inFile.getline(tempLine, MAX_LINE_LENGTH);
	}
}
Menu Room::loadMenu(std::ifstream& inFile)
{
	//Rewind the file
	inFile.seekg(0);

	//Get the first line of the file
	char tempLine[MAX_LINE_LENGTH + 1];
	inFile.getline(tempLine, MAX_LINE_LENGTH);

	//Look for [MENU], if one is not found simply return
	while(formatString(tempLine) != "[MENU]" && !inFile.eof())
		inFile.getline(tempLine, MAX_LINE_LENGTH);
	
	//Skip past the menu key
	inFile.getline(tempLine, MAX_LINE_LENGTH);

	int optCount = 0;
	
	while(!inFile.eof() && formatString(tempLine) != "[END_MENU]")
	{
		//Look for <OPTION>
		while(formatString(tempLine) != "<OPTION>" && !inFile.eof())
			inFile.getline(tempLine, MAX_LINE_LENGTH);	
		//Skip past the option key
		inFile.getline(tempLine, MAX_LINE_LENGTH);
		
		//Print some formatting
		++optCount;
		std::cout<<"   "<<optCount<<". "<<tempLine<<"\n";

		//Look for <END_OPT>
		while(formatString(tempLine) != "<END_OPT>" && !inFile.eof())
		{
			inFile.getline(tempLine, MAX_LINE_LENGTH);
			if(formatString(tempLine) != "<END_OPT>") std::cout<<"      "<<tempLine<<"\n";
		}
		//Skip past the option key
		inFile.getline(tempLine, MAX_LINE_LENGTH);
	}
	//Turn the count into a menu
	Menu result(optCount);
	return result;
}
void Room::loadResolution(std::ifstream& inFile)
{
	//Rewind the file
	inFile.seekg(0);

	//Get the first line of the file
	char tempLine[MAX_LINE_LENGTH + 1];
	inFile.getline(tempLine, MAX_LINE_LENGTH);

	//Look for [RESOLVE], if one is not found simply return
	while(formatString(tempLine) != "[RESOLVE]" && !inFile.eof())
		inFile.getline(tempLine, MAX_LINE_LENGTH);
	
	//Skip past the command key
	inFile.getline(tempLine, MAX_LINE_LENGTH);

	//Look for [END_RES]
	while(formatString(tempLine) != "[END_RES]" && !inFile.eof())
	{
		//Set up the temporaries
		std::vector<String> tempVector;
		String nextCommand("");

		//Loop through the line character by character getting commands
		int i = 0;
		while(i < String(tempLine) && tempLine[i] != '<') ++i;
		++i;
		while(i < String(tempLine) && tempLine[i] != '>')
		{
			if(tempLine[i] != ',') nextCommand += tempLine[i];
			else
			{
				//Push the command onto the vector
				tempVector.push_back(nextCommand);
				nextCommand = "";
			}
			++i;
		}
		//Push the command onto the vector
		tempVector.push_back(nextCommand);
		nextCommand = "";

		//Push the vector onto the vector
		resolves.push_back(tempVector);
		tempVector.clear();

		//Get the next line
		inFile.getline(tempLine, MAX_LINE_LENGTH);
	}
}

void Room::loadNextRooms(std::ifstream& inFile)
{
	//Rewind the file
	inFile.seekg(0);

	//Get the first line of the file
	char tempLine[MAX_LINE_LENGTH + 1];
	inFile.getline(tempLine, MAX_LINE_LENGTH);

	//Look for [RESOLVE], if one is not found simply return
	while(formatString(tempLine) != "[ROOMS]" && !inFile.eof())
		inFile.getline(tempLine, MAX_LINE_LENGTH);
	
	//Skip past the command key
	inFile.getline(tempLine, MAX_LINE_LENGTH);

	//Look for [END_RES]
	while(formatString(tempLine) != "[END_ROOMS]" && !inFile.eof())
	{
		nextRooms.push_back(tempLine);

		//Get the next line
		inFile.getline(tempLine, MAX_LINE_LENGTH);
	}
}