#ifndef RIEDEL_INVENTORY_H
#define RIEDEL_INVENTORY_H

//Needed libraries
#include "Globals.h"

//Set the namespace TBA = Text-Based Adventure
namespace TBA
{
	class Inventory
	{
	public:
		//Constructors
		Inventory();					//Creates an empty inventory (needs a file name to run right)
		Inventory(const String&);		//Creates the inventory from a file name (no extention)

		//Public Methods
		void load(const String&);		//Loads the inventory file
		void add(const String&);		//Adds an item to the inventory
		void clear();						//Removes all items from the inventory

		//Public Functions
		bool check(const String&)const;	//Checks if an item is in the inventory, returns true if it is
		bool remove(const String&);		//Removes an item from the inventory

		//Operators
		friend std::ostream& operator<<(std::ostream&, const Inventory&);

	//private://commented for testing
		//Private Attributes
		std::vector<const String> itemList;		//A current list of what is in the inventory
		String filePath;						//The file this inventory object modifies

		//Private Methods
		void updateFile()const;		//Rewrites the inventory file from inventoryList
	};
};//end namespace

#endif
