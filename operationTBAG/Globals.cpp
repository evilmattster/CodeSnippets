#include "Globals.h"

//-----------------------------------------------------------------------------PARSER FUNCTIONS
//Returns the index of the resolution vector
int parseStr(const std::vector<std::vector<String>>& cmdVector, const String& inCmd)
{
	//Loop the outer vector
	bool notFound = true;
	unsigned i = 0;
	while(i < cmdVector.size() && notFound)
	{
		//Loop the inner vectors serching for the command
		unsigned j = 0;
		while(j < cmdVector[i].size() && notFound)
		{
			//Compare commands
			if(formatString(inCmd) == formatString(cmdVector[i][j]))
				notFound = false;
			++j;	//Increment inner loop
		}
		++i;	//Increment outer loop
	}

	//Let it be knon that the command cannot be found
	if(notFound) return -1;

	//Return the index of the resolution vector
	return i-1;
}

//Runs the code needed to resolve the command
int parseResolve(const std::vector<std::vector<String>>& resVector, const int& index)
{	
	//Cause Visual Studio is being a jerk
	int nextRoom = -1;

	//Loop through the commands in the proper index executing them all
	for(unsigned i=0; i<resVector[index].size(); ++i)
	{
		//Run through single word parsing options
		if(formatString(resVector[index][i]) == "HELP") runHelp();
		else if(formatString(resVector[index][i]) == "EXIT") exit(0);
		else if(formatString(resVector[index][i]) == "GOTO") nextRoom = index;
		else if(formatString(resVector[index][i]) == "EDIT") nextRoom = -1;
	}

	//Pass back the room index, -1 means don't change
	return nextRoom;
}

//-----------------------------------------------------------------------------STANDARD FORMAT
String formatString(const String& unformatted)
{
	//Make a copy of the string to format with no spaces
	String temp = "";
	for(unsigned i=0; i<unsigned(unformatted.length()); ++i)
		if(unformatted[i] != ' ')
			temp += unformatted[i];

	//convert to all caps
	for(unsigned i=0; i<unsigned(temp.length()); ++i)
		if(temp[i] >= 'a' && temp[i] <= 'z')
			temp[i] = char(int(temp[i]) - int('a') + int('A'));

	//return the formatted version
	return temp;
}	
void formatFile(const String& file)
{
}
String removeCommand(const String& codeIn)
{
	//Make a temporary string to put stuff in
	String temp = "";

	//Test fer and remove the first command
	if((codeIn.length() > 2)&&(codeIn[0] == '#' && codeIn[1] == '['))
	{
		//Separate the command from the string
		bool nextSwitch = false;
		for(unsigned j=2; j<unsigned(codeIn.length()); ++j)
		{
			//Copy the item name
			if(nextSwitch)
				temp += codeIn[j];
			//Copy the command
			else if(codeIn[j] != ']' && !nextSwitch)
				nextSwitch = true;
		}
		//Reset
		nextSwitch = false;

		//Check for additional data
		if((temp.length() > 3)&&(temp[0] == '-' && temp[1] == '>' && temp[2] == '['))
		{
			//Make another temp to hold the cleaned up item
			String tempHolder = "";

			//Copy the item over without command data
			for(unsigned j=3; j<unsigned(temp.length()); ++j)
			{
				if(nextSwitch)
					tempHolder += temp[j];
				else if(temp[j] == ']')
					nextSwitch = true;
			}
			//Put the commandlacking data into the output string
			return tempHolder;
		}
		return temp;
	}
	//No formatting needed
	return codeIn;
}
//-----------------------------------------------------------------------------FILE ENCRYPTION
void encryptFile(const String& file)
{
	//open file as input
	std::ifstream input;
	input.open(file.toChars());
	if(input.fail()) std::cout<<"File not found\n";

	//Create holder string
	String text;

	//read text into a long string
	while(!input.eof()&&!input.fail())
	{
		text += input.get();
	}
	//close file
	input.close();

	//Make sure it isn't already encrypted
	if(text[0] == char(1000)) return;

	//Make a character array to output
	char *result = new char[text.length() + 1];

	//Mark as Encrypted
	result[0] = char(1000);

	//Encode text
	for(int i=1; i<int(text.length() + 1); ++i)
	{
		result[i] = char(int(text[i-1]) + (i%15));
	}
	//open file as output
	std::ofstream output;
	output.open(file.toChars());

	//Write the encoded stuff in
	output.clear();
	output.write(result, int(text.length()));

	//delete dynamic memory
	delete[] result;
		
	//close file
	output.close();
}
//-----------------------------------------------------------------------------FILE DECODING
void decodeFile(const String& file)
{
	//open file as input
	std::ifstream input;
	input.open(file.toChars());
	if(input.fail()) std::cout<<"File not found\n";

	//Create holder string
	String text;

	//read text into a long string
	while(!input.eof()&&!input.fail())
	{
		text += input.get();
	}
	//close file
	input.close();

	//Make sure it isn't already decoded
	if((text[0] != char(1000))||(text.length() < 1)) return;

	//Make a character array to output
	char *result = new char[text.length() - 1];

	//Decode text
	for(int i=1; i<int(text.length()); ++i)
	{
		result[i-1] = char(int(text[i]) - (i%15));
	}
	//open file as output
	std::ofstream output;
	output.open(file.toChars());

	//Write the decoded stuff in
	output.clear();
	output.write(result, int(text.length()) - 2);

	//delete dynamic memory
	delete[] result;
		
	//close file
	output.close();
}
//-----------------------------------------------------------------------------SORTING STRING VECTORS
void sortVector(std::vector<const String>& toSort)//Simple "Bubble Sort" algorithm
{
	//Create a flag, a miniFlag, a counter and holder
	bool flag;		
	String temp;

	do
	{
		//Reset the flag to false at the start of each iteration
		flag = false;

		//Loop through the entire vector
		for(unsigned i=1; i<toSort.size(); ++i)
		{
			//Test if a swap needs to occur
			if(removeCommand(format(toSort[i-1])) > removeCommand(format(toSort[i])))
			{
				flag = true;
				temp = toSort[i-1];
				toSort[i-1] = toSort[i];
				toSort[i] = temp;
			}
		}
	//If a flag was raised, loop again
	}while(flag);
}

void runHelp()
{
	system("cls");
	std::cout<<"Try typing phrases such as \"go north\"\n";
	std::cout<<"\nIf it is creating games you are having difficulty with,\n"
		"Take a look at the example game (named Game).  The files are\n"
		"plain text and can be opened in any text editor.\n\n"
		"There is also a readme.txt located next to the executable.\n\n";
	system("pause");
};
