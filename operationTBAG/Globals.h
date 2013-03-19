#ifndef RIEDEL_GLOBALS_H
#define RIEDEL_GLOBALS_H

#include <iostream>
#include <fstream>
#include<iostream>
#include <vector>
#include <chrono>
#include <direct.h>
#include "String.h"
#include "inventory.h"
#include "Room.h"

//File extentions
#define GAME_FILE_EXTENTION ".gam"
#define INVENTORY_FILE_EXTENTION ".inv"
#define ROOM_FILE_EXTENTION ".rm"
#define SAVE_FILE_EXTENTION ".sav"

//Folder file paths
#define ROOM_FOLDER_PATH "/Rooms"
#define SAVE_FOLDER_PATH "/SaveFiles"

static const int MAX_LINE_LENGTH = 200;
static String GAME_PATH = "./Game_Files";
static bool IS_EDITOR = false;

//-----------------------------------------------------------------------------PARSER FUNCTIONS
int parseStr(const std::vector<std::vector<String>>&, const String&);		//Returns the index of the resolution vector
int parseResolve(const std::vector<std::vector<String>>&, const int&);		//Runs the code needed to resolve the command

//-----------------------------------------------------------------------------ACTUAL PARSED FUNCTIONS
void runHelp();

//-----------------------------------------------------------------------------STANDARD FORMAT
String formatString(const String& unformatted);	//Formatting a string
void formatFile(const String& file);			//Formatting a whole file
String removeCommand(const String& codeIn);		//Formatting
void encryptFile(const String& file);			//File encryption
void decodeFile(const String&);					//File decoding
void sortVector(std::vector<const String>&);	//Bubble sort

#endif
