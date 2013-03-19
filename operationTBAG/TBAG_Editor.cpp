#include "Globals.h"
#include "TBAG_Editor.h"

bool TBAG_Editor::load(const String &path)
{
	//Set up room
	Room tempRoom(path);
	currentRoom = tempRoom;

	//Set the game path
	GAME_PATH = "./Game_Files/" + path;

	//Test Root Path
	std::ifstream rootFile;
	rootFile.open((GAME_PATH + "/" + path + GAME_FILE_EXTENTION).toChars());
	if(rootFile.fail()) return false;

	//***************************//
	//*******LOAD FROM ROOT******//
	//***************************//

	rootFile.close();
	
	//Test First Room
	std::ifstream rmFile;
	rmFile.open((GAME_PATH + ROOM_FOLDER_PATH + "/" + path + ROOM_FILE_EXTENTION).toChars());
	if(rmFile.fail()) return false;
	rmFile.close();
	
	run();

	return true;
}

bool TBAG_Editor::load(const String &path, const String &room)
{
	//Set up room
	Room tempRoom(room);
	tempRoom.setGameName(path);
	currentRoom = tempRoom;

	//Set the game path
	GAME_PATH = "./Game_Files/" + path;

	//Test Root Path
	std::ifstream rootFile;
	rootFile.open((GAME_PATH + "/" + path + GAME_FILE_EXTENTION).toChars());
	if(rootFile.fail()) return false;

	//***************************//
	//*******LOAD FROM ROOT******//
	//***************************//

	rootFile.close();
	
	//Test First Room
	std::ifstream rmFile;
	rmFile.open((GAME_PATH + ROOM_FOLDER_PATH + "/" + room + ROOM_FILE_EXTENTION).toChars());
	if(rmFile.fail()) return false;
	rmFile.close();

	run();

	return true;
}

void TBAG_Editor::runEdits(const String& name)
{
	//Set the game you are modifying
	GAME_PATH = "./Game_Files/" + name;
	gameName = name;

	//Loop through an edit cycle
	while(true)
	{
		//Run the edit menu
		runEditMenu();
	}
}

void TBAG_Editor::runEditMenu()
{
	//Wipe the screen
	system("cls");

	//Ask what they want to do
	char choice;
	std::cout<<"\n Please Select one of the following:\n\n"
		"   1. Create new room\n"
		"   2. Remake existing room (completely overwrites the file)\n"
		"   3. Test room for null connections\n"
		"   4. Play-test from room\n"
		"   5. Exit\n"
		"\n What would you like to do? ";
	std::cin>>choice;

	//Check the validity of the input
	if(choice - '0' < 1 || choice - '0' > 5)
	{
		std::cout<<"Invalid input\n";
		_sleep(800);
		return;
	}

	//Switch through the operations
	switch (choice)
	{
	case '1': //New Room
		makeRoom(false);
		break;
	case '2': //Existing Room
		makeRoom(true);
		break;
	case '3': //Check links
		debugRoom();
		break;
	case '4': //Play test
		playFrom();
		break;
	case '5': //Exit
		exit(0);
		break;
	default:
		break;
	}
}

bool TBAG_Editor::create(const String &path)
{
	//Set the game path
	GAME_PATH = "./Game_Files/" + path;

	//Set the base file system
	_mkdir("./Game_Files");
	String tempPath(GAME_PATH);
	_mkdir(tempPath.toChars());
	tempPath = GAME_PATH + ROOM_FOLDER_PATH; 
	_mkdir(tempPath.toChars());
	tempPath = GAME_PATH + SAVE_FOLDER_PATH; 
	_mkdir(tempPath.toChars());

	//Create the root file
	std::ofstream rootFile;
	rootFile.open((GAME_PATH + "/" + path + GAME_FILE_EXTENTION).toChars());
	if(rootFile.fail()) return false;

	//Write the file's text
	/*
	********************************************************************************************************************
	********************************************************************************************************************
	*/
	rootFile.close();

	//Create the first Room
	std::ofstream rmFile;
	rmFile.open((GAME_PATH + ROOM_FOLDER_PATH + "/" + path + ROOM_FILE_EXTENTION).toChars());
	if(rmFile.fail()) return false;

	//Write the room file
	rmFile<<"[INTRO]\n"
		"Welcome to your Title Page.\n"
		"You can edit this page by opening \""<<(GAME_PATH + ROOM_FOLDER_PATH + "/" + path + ROOM_FILE_EXTENTION).toChars()<<"\"\n"
		"Be sure you don't change the name of this room in particular\n"
		"\nType \"help\" if you get stuck.\n"
		"\nWhat would you like to do?\n"
		"[END_INTRO]\n\n"
		"[MENU]\n"
		"<OPTION>\n"
		"Exit\n"
		"<END_OPT>\n"
		"[END_MENU]\n\n"
		"[COMMAND]\n"
		"<>\n"
		"<HELP, WHATDOIDO>\n"
		"<EXIT, CLOSE, QUIT>\n"
		"[END_CMD]\n\n"
		"[RESOLVE]\n"
		"<EXIT>\n"
		"<HELP>\n"
		"<EXIT>\n"
		"[END_RES]\n";
	rmFile.close();
	
	//Try to load the newly created framework
	runEdits(path);
	 return true;
}

//Bool switches the file override (true = dangerous)
void TBAG_Editor::makeRoom(bool fileOverride)
{
	//Wipe the screen
	system("cls");

	//Ask for a name
	String roomName;
	std::cout<<"\n What would you like to name your room? ";
	std::cin>>roomName;

	//Make the filepath
	String filePath = (GAME_PATH + ROOM_FOLDER_PATH + "/" + roomName + ROOM_FILE_EXTENTION);

	//If the override is off, make sure the file doesn't exist
	if(!fileOverride)
	{
		std::ifstream testExistence;
		testExistence.open(filePath.toChars());
		if(!testExistence.fail())
		{
			std::cout<<"ERROR: This room already exists\n";
			testExistence.close();
			_sleep(800);
			return;
		}
	}

	//Attempt to create the file
	std::ofstream newRoom;
	newRoom.open(filePath.toChars());
	if(newRoom.fail()) { std::cout<<"Could not create file\n"; _sleep(800); return; }
	

	//Make a vector to hold every line of the file
	std::vector<String> newFile;
	std::vector<String> toResolve;
	std::vector<String> toGoTo;
	String tempPush;

	//Make the [INTRO] -> [END_INTRO]
	system("cls");
	newFile.push_back("[INTRO]");
	std::cout<<"Please enter the intro text, terminated by [END_INTRO] on its own line.\n"
		"Keep in mind that [PAUSE] is a valid function\n";
	std::cin>>tempPush;
	while(formatString(tempPush) != "[END_INTRO]")
	{
		newFile.push_back(tempPush);
		std::cin>>tempPush;
	}
	newFile.push_back("[END_INTRO]");

	//Make the [MENU] -> [END_MENU]
	system("cls");
	newFile.push_back("[MENU]");
	std::cout<<"Please enter the menu text, terminated by [END_MENU] on its own line.\n"
		"Please enter one menu option per line\n";
	std::cin>>tempPush;
	while(formatString(tempPush) != "[END_MENU]")
	{
		newFile.push_back("<OPTION>");
		newFile.push_back(tempPush);
		toResolve.push_back(tempPush);
		newFile.push_back("<END_OPT>");
		std::cin>>tempPush;
	}
	newFile.push_back("[END_MENU]");

	//Make the [COMMAND] -> [END_CMD]
	system("cls");
	newFile.push_back("[COMMAND]");
	std::cout<<"Please enter the command text, terminated by [END_CMD] on its own line.\n"
		"Please enter commands in <> with equivilent commands separated by commas:\n"
		"EG  \"<GoNorth,WalkNorth,moveNorth,HeadNorth>\" spaces and caps don't matter\n";
	std::cin>>tempPush;
	while(formatString(tempPush) != "[END_CMD]")
	{
		newFile.push_back(tempPush);
		toResolve.push_back(tempPush);
		std::cin>>tempPush;
	}
	newFile.push_back("[END_CMD]");

	//Make the [RESOLVE] -> [END_RES]
	newFile.push_back("[RESOLVE]");
	for(unsigned i=0; i<toResolve.size(); ++i)
	{
		system("cls");
		std::cout<<"Please write the resolution task for:\n"<<toResolve[i]<<"\n"
			"If it goes to a room type [GOTO]. Other options are [EXIT] or [HELP]\n";
		std::cin>>tempPush;
		newFile.push_back(tempPush);
		if(formatString(tempPush) == "[GOTO]")
			toGoTo.push_back(toResolve[i]);
		else
			toGoTo.push_back(" ");
	}
	newFile.push_back("[END_RES]");

	//Make the [ROOM] -> [END_ROOM]
	newFile.push_back("[ROOMS]");
	for(unsigned i=0; i<toResolve.size(); ++i)
	{
		system("cls");
		if(toGoTo[i] != " ")
		{
			std::cout<<"\n Please write the name of the room that this:\n\""<<toGoTo[i]<<"\" goes to.\n";
			std::cin>>tempPush;
		}
		else tempPush = " ";
		newFile.push_back(tempPush);
	}
	newFile.push_back("[END_ROOMS]");

	//Loop through the vector writing the new file
	for(unsigned i=0; i < newFile.size(); ++i)
		newRoom<<newFile[i]<<"\n";
	newRoom.close();
}

//Tests for obvious room errors
void TBAG_Editor::debugRoom()//================================================================
{
	//Wipe the screen
	system("cls");
	
	//Ask for a name
	String roomName;
	std::cout<<"\n What room would you like to debug? ";
	std::cin>>roomName;
	
	//Try to open the room
	std::ifstream testFile;
	testFile.open((GAME_PATH + ROOM_FOLDER_PATH + "/" + roomName + ROOM_FILE_EXTENTION).toChars());
	if(testFile.fail()) { std::cout<<"Unable to open file "<<(GAME_PATH + ROOM_FOLDER_PATH + "/" + roomName + ROOM_FILE_EXTENTION).toChars()<<"\n"; _sleep(800); return; }

	//Start the debugging (set up the names array)
	std::vector<String> fileNames;
	char temp[MAX_LINE_LENGTH+1];
	testFile.getline(temp, MAX_LINE_LENGTH);
	while(formatString(temp) != "[ROOMS]" && !testFile.eof())
		testFile.getline(temp, MAX_LINE_LENGTH);
	testFile.getline(temp, MAX_LINE_LENGTH);
	while(formatString(temp) != "[END_ROOMS]" && !testFile.eof())
	{
		fileNames.push_back(temp);
		testFile.getline(temp, MAX_LINE_LENGTH);
	}

	//Attempt to open each file
	system("cls");
	bool badData = false;
	for(unsigned i=0; i<fileNames.size(); ++i)
	{
		std::ifstream tempIn;
		tempIn.open((GAME_PATH + ROOM_FOLDER_PATH + "/" + fileNames[i] + ROOM_FILE_EXTENTION).toChars());
		if(tempIn.fail()) { std::cout<<"Accessing non-existent room \""<<fileNames[i]<<"\"\n"; badData = true; }
		else tempIn.close();
	}
	if(!badData) std::cout<<"All rooms accounted for\n";

	testFile.close();
	testFile.open((GAME_PATH + ROOM_FOLDER_PATH + "/" + roomName + ROOM_FILE_EXTENTION).toChars());

	testFile.getline(temp, MAX_LINE_LENGTH);
	while(formatString(temp) != "[MENU]" && !testFile.eof())
		testFile.getline(temp, MAX_LINE_LENGTH);
	while(formatString(temp) != "[END_MENU]" && !testFile.eof())
		testFile.getline(temp, MAX_LINE_LENGTH);
	
	if(formatString(temp) != "[END_MENU]")
		std::cout<<"Your room is lacking a menu. Even if a menu isn't used,\n"
		"a blank one should be inserted so the room can parse properly.\n\n";

	system("pause");
}

//Starts the game from a certain room
void TBAG_Editor::playFrom()
{
	//Wipe the screen
	system("cls");
	
	//Ask for a name
	String roomName;
	std::cout<<"\n What room would you like to start from? ";
	std::cin>>roomName;
	
	//Set the current room
	std::cout<<gameName<<", "<<roomName<<"\n";
	load(gameName, roomName);
	std::cout<<gameName<<", "<<roomName<<"\n";
	system("pause");
}

void TBAG_Editor::run()
{
	currentRoom.runRoom();
}