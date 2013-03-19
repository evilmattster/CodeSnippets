#include "inventory.h"
namespace TBA
{
	/*******************************************************************************************************/
	/*                                                                                        CONSTRUCTORS */
	/*******************************************************************************************************/
	Inventory::Inventory()
	{
		load(GAME_PATH + SAVE_FOLDER_PATH + "/Inventory" + INVENTORY_FILE_EXTENTION);
	}
	Inventory::Inventory(const String& file)
	{
		load(file);
	}

	/*******************************************************************************************************/
	/*                                                                                      PUBLIC METHODS */
	/*******************************************************************************************************/
	void Inventory::load(const String& file)
	{
		//Set file name
		filePath = file + INVENTORY_FILE_EXTENTION;

		//Decode file
		decodeFile(filePath);

		//Open file
		std::ifstream input;
		input.open(filePath.toChars());
		if(input.fail()) std::cout<<"File not found\n";

		//Wipe any current inventory list
		itemList.clear();

		//Create a placeholder for input
		char temp[MAX_LINE_LENGTH];

		//read into vector
		while(!input.eof()&&!input.fail())
		{
			//get the next line of the file
			input.getline(temp, MAX_LINE_LENGTH);
			
			//Read in only if the line isn't empty
			if(temp[0] != 0)
			{
				formatString(temp);
				itemList.push_back(String(temp));
			}
		}
		//Sort vector
		sortVector(itemList);

		//Cleanup loose ends
		input.close();
		encryptFile(filePath);
	}
	void Inventory::add(const String& item)
	{
		//Stick a formatted version on the end of the inventory
		itemList.push_back(item);

		//Make sure everything is in order
		sortVector(itemList);
	}
	void Inventory::clear()
	{
		//Delete every item in the inventory vector
		itemList.clear();
	}

	/*******************************************************************************************************/
	/*                                                                                    PUBLIC FUNCTIONS */
	/*******************************************************************************************************/
	bool Inventory::check(const String& item)const
	{
		//Make a formatted copy of the item string
		String test = formatString(item);

		//Run through the inventory vector checking for the item return true if found
		for(unsigned i=0; i<itemList.size(); ++i)
			if(test == formatString(itemList[i]))
				return true;

		//If the item wasn't found, return false
		return false;
	}
	bool Inventory::remove(const String& item)
	{
		/*NOTE:	This function only deletes one copy of an item if there are multiple
				To delete all instances of an item make a loop that runs until this 
				function returns false*/
		
		//Set the boolean to return to false (no item deleted yet)
		bool toReturn = false;

		//Make a formatted copy of the item string
		String toDelete = formatString(item);

		//Create a holder for the new itemList
		std::vector<const String> temp;

		//run through the inventory vector copying everything but the item
		for(unsigned i=0; i<unsigned(itemList.size()); ++i)
			if((toDelete != formatString(itemList[i]))||(toReturn))
			{
				temp.push_back(itemList[i]);
				toReturn = true;
			}

		//tuen temp into the new list of items
		itemList = temp;

		//Let people know if anything was deleted
		return toReturn;
	}
	
	/*******************************************************************************************************/
	/*                                                                                           OPERATORS */
	/*******************************************************************************************************/
	//Output operator
	std::ostream& operator<<(std::ostream& out, const Inventory& inv)
	{
		//Create a variable to hold the output string
		String tempItem = "";
		String tempCommand = "";

		//Make a counter to allow skipped numbers for hidden items
		short hiddenCount = 0;

		//Loop through the inventory
		for(unsigned i=0; i<inv.itemList.size(); ++i)
		{
			//Check for a command type
			if((inv.itemList[i].length() > 2)&&(inv.itemList[i][0] == '#' && inv.itemList[i][1] == '['))
			{
				//Separate the command from the string
				bool nextSwitch = false;
				for(unsigned j=2; j < unsigned(inv.itemList[i].length()); ++j)
				{
					//Copy the item name
					if(nextSwitch)
						tempItem += inv.itemList[i][j];
					//Copy the command
					if(inv.itemList[i][j] != ']' && !nextSwitch)
						tempCommand += inv.itemList[i][j];
					//The command ended, copy the rest
					else
						nextSwitch = true;
				}
				//Reset
				nextSwitch = false;

				//Chech to make sure the item is supposed to be displayed
				if(tempCommand == "HIDDEN")
				{
					tempItem = "";
					++hiddenCount;
				}

				//Check for additional data is it is to be displayed
				else if((tempItem.length() > 3)&&(tempItem[0] == '-' && tempItem[1] == '>' && tempItem[2] == '['))
				{
					//Make another temp to hold the cleaned up item
					String tempHolder = "";

					//Copy the item over without command data
					for(unsigned j=3; j<unsigned(tempItem.length()); ++j)
					{
						if(nextSwitch)
							tempHolder += tempItem[j];
						else if(tempItem[j] == ']')
							nextSwitch = true;
					}
					//Put the commandlacking data into the output string
					tempItem = tempHolder;
				}
			}
			else
			{
				tempItem = inv.itemList[i];
			}

			//output the item
			if(tempItem != "")
				out<<(i + 1 - hiddenCount)<<". "<<tempItem<<"\n";
			//Reset
			tempItem = "";
			tempCommand = "";
		}
		//Send the stream out for the next guy
		return out;
	}

	/*******************************************************************************************************/
	/*                                                                                     PRIVATE METHODS */
	/*******************************************************************************************************/
	void Inventory::updateFile()const
	{
		//Check that "filePath" exists
		std::ofstream out;
		out.open(filePath.toChars());		

		//Clear the file
		out.clear();

		//Print inventory in file, one line per item (until the last one that can't have a line return on it)
		for(unsigned i=0; i<itemList.size()-1; ++i)
			out<<itemList[i]<<"\n";
		out<<itemList[itemList.size()-1];

		//Close file
		out.close();

		//Encrypt file
		encryptFile(filePath);
	}
};//End namespace