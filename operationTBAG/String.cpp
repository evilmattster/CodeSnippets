#include "String.h"

//================================================================================================== CONSTRUCTORS

//------------------------------------------------------------------------------------------ Default Constructor
String::String()
{
	//Init size to 0, and allocated to 128
	size = 0;
	allocated = 128;

	//Create a new character array at pointer "characters"
	characters = new char[allocated];

	//Close the array with a null terminator
	characters[size] = 0;
};
//------------------------------------------------------------------------------------------ Char Constructor
String::String(const char& c)
{
	//Init size to 1, and allocated to 128
	size = 1;
	allocated = 128;
	
	//Create a new character array at pointer "characters"
	characters = new char[allocated];
	characters[0] = c;
	
	//Close the array with a null terminator
	characters[size] = 0;
};
//------------------------------------------------------------------------------------------ Char[] Constructor
String::String(const char input[])
{	
	//Init size to 0, and allocated to 128
	size = 0;
	allocated = 128;

	//Create a temporary variable to hold current characters, init to input[0]
	char temp = input[size];

	//Loop through the input array to find the size
	while(temp != 0 && temp != ';' && temp != -1){ temp = input[++size]; }
	
	//Create a new character array at pointer "characters"
	if(size < allocated)
		characters = new char[allocated];
	else
	{
		allocated = size + 128;
		characters = new char[allocated];
	}

	//Loop through the input array and initialize our characters
	for(int i=0; i<size; ++i){ characters[i] = input[i]; }
	
	//Close the array with a null terminator
	characters[size] = 0;
};

//------------------------------------------------------------------------------------------ Copy Constructor
String::String(const String& actual)
{
	//Init size to the actual size
	size = actual.size;
	allocated = actual.allocated;
	
	//Create a new character array at pointer "characters"
	characters = new char[allocated];

	//Loop through the the actual character array and initialize our characters
	for(int i=0; i<size; ++i){ characters[i] = actual.characters[i]; }
	
	//Close the array with a null terminator
	characters[size] = 0;
};

//================================================================================================== DESTRUCTOR
String::~String() { delete[] characters; };

//================================================================================================== PUBLIC METHODS

//------------------------------------------------------------------------------------------ Length
//Returns the length for people to use in a safe manner
int String::length()const
{ 
	return size;
}

//------------------------------------------------------------------------------------------ Find String
//Returns the index where the string starts, and -1 if the string was not found
int String::findstr(const String& toFind)const
{
	//Make sure this is long enough to contain the other string
	if(size < toFind.size)
		return -1;

	//Create a holder for the current index
	int index = 0;

	//Loop through this looking for the other string (end if there aren't enough characters remaining)
	while(index < (size + toFind.size))
	{
		//Create a switch to check if the strings are equal (assume found)
		bool foundIt = true;

		//Loop through this from the current index trying to find the string
		for(int i=0; i<toFind.size; ++i)
		{
			//Check if each character of this is not equal to the string
			if(substr(index + i) != toFind[i])
			{
				//Show that the string was not found here
				foundIt = false;

				//Essentially break from the loop by modifying i
				i = toFind.size;
			}
		}
		//If the switch wasn't turned off, the string has been found
		if(foundIt)
			return index;

		//Otherwise increment the index
		index++;
	}
	//If not found, return -1
	return -1;
}
//------------------------------------------------------------------------------------------ Sub String
//Returns a string from point a to b inclusive
String String::subString(const int a, const int b)const
{
	//Make a holder string
	String toReturn("");

	//Copy the sting over
	for(int i=a; i>=0 && i<=b && i<length(); ++i)
		toReturn += (*this)[i];

	//Return the string
	return toReturn;
}
//------------------------------------------------------------------------------------------ Find Character
//Returns the index of the first instance of the given character
int String::findchar(const char toFind)const
{
	//Make sure this is long enough to contain at least 1 character
	if(size < 1)
		return -1;

	//Create a holder for the current index
	int index = 0;

	//Loop through the string looking for the character
	while(index < size)
	{
		//If the character is found at the given index, return that index
		if(substr(index) == toFind)
			return index;

		//Otherwise increment the index
		index++;
	}
	//If not found, return -1
	return -1;
}

//------------------------------------------------------------------------------------------ Reallocate Array
//Changes the size of the array to the size input
void String::reallocate(const int newCapacity)
{
	//Make a temporary array 
	char *temp = new char[newCapacity];

	//Do size checking
	if(newCapacity < size)
		size = newCapacity - 1;

	//Put the current string into the newly allocated one
	for(int i=0; i<size; i++)
		temp[i] = substr(i);

	//Put a null terminator on it
	temp[size] = 0;

	//Swap the strings
	*this = String(temp);

	//Remove the dynamic memory
	delete[] temp;
}

//------------------------------------------------------------------------------------------ Vector Split
//Splits a string up into a vector of strings designated by a delimiter
std::vector<String> String::split(const char delim) const
{
	//Create a string vector to hold each string
	std::vector<String> result;

	//Create a temporary string to hold each "word"
	String tempWord;

	//Loop through the string dividing it into words
	for(int i=0; i<size; ++i)
	{
		//Check for the delimiter
		if(substr(i) == delim)
		{
			//Push the temp into the vector if it exists, then reset the temp
			if(tempWord != "")
			{
				result.push_back(tempWord);
				tempWord = "";
			}
		}
		//If the delimiter wasn't hit, a letter must need to be pushed into the word
		else 
			tempWord += substr(i);
	}
	//Clean up by pushing the last word into the vector
	if(tempWord != "")
		result.push_back(tempWord);

	//Return the vector
	return result;
}

//================================================================================================== EQUALS OPERATOR
//Sets this equal to some other string
String String::operator=(String right)
{
	//Switch the data contained in this, with that of the temporary variable "right"
	swap(right);

	//Return "this" incase someone does a funky equality
	return *this;
}

//================================================================================================== CONCATENATION OPERATORS

//------------------------------------------------------------------------------------------ Plus Equals +=
//Adds the following string to this, and sets this equal to the result
String String::operator+=(const String& right)
{
	//Create a temporary array to hold both strings combined
	char *temp;

	//Set the size of temp so that it can hold everything
	if(allocated < (size + right.size))
		temp = new char[allocated + right.allocated];
	else
		temp = new char[allocated];

	//Loop through the first String putting all the characters into the temporary array
	for(int i=0; i<size; ++i)
		temp[i] = substr(i);

	//Loop through the second String putting all of the characters after the first set
	for(int i=0; i<right.size; ++i)
		temp[size + i] = right[i];

	//Put a null terminator on the array
	temp[size + right.size] = 0;

	//Set this equal to the newly created array
	String toSwap(temp);
	swap(toSwap); 

	//Clean up dynamic memory
	delete[] temp;

	//Return the finished concatenation
	return *this;
}
//------------------------------------------------------------------------------------------ Plus +
//Returns this with the other string following it without modifying this
String String::operator+(const String& right)const
{	
	//Create a temporary array to hold both strings combined
	char *temp;

	//Set the size of temp so that it can hold everything
	if(allocated < (size + right.size))
		temp = new char[allocated + right.allocated];
	else
		temp = new char[allocated];

	//Loop through the first String putting all the characters into the temporary array
	for(int i=0; i<size; ++i)
		temp[i] = substr(i);

	//Loop through the second String putting all of the characters after the first set
	for(int i=0; i<right.size; ++i)
		temp[size + i] = right[i];

	//Put a null terminator on the array
	temp[size + right.size] = 0;

	//Create a String from the temporary array
	String combined(temp);

	//Clean up dynamic memory
	delete[] temp;

	//Return the finished concatenation
	return combined;
}

//================================================================================================== RELATIONAL OPERATORS

//------------------------------------------------------------------------------------------ Double Equals ==
//Returns true if this is equal to another string
bool String::operator==(const String& right)const
{
	//Check the length first
	if(size != right.size) return false;

	//Now run through letter by letter
	for(int i=0; i<size; ++i)
		if(substr(i) != right[i]) return false;

	//Everything chaecks out, they must be equal
	return true;
}
//------------------------------------------------------------------------------------------ Greater Than >
//Returns true if this comes later alphabetically (eg 'Z' > 'A')
bool String::operator>(const String& right)const
{
	//Create temporary formatted versions of the current strings
	String lesser = format(right);
	String greater = format(*this);
	
	//Run through each character and check if the statement is true
	for(int i=0; i<greater.size; ++i)
	{
		//First check to see if the lesster character exists, If not this must be greater
		if(i >= lesser.size)
			return true;

		//Then check if we are dealing with a letter or number (numbers preceed the alphabet)
		if(greater[i] >= 'A' && greater[i] <= 'Z')
		{
			//Check if lesser is a number or letter, if its a number return true
			if(lesser[i] >= '1' && lesser[i] <= '9')
				return true;

			//Otherwise they are both letters and we just need to check if "greater"s is really greater
			if(greater[i] > lesser[i])
				return true;
		}
		//Greater[i] is a number
		else
		{
			//Check if lesser is a number or letter, if its a letter return false
			if(lesser[i] >= 'A' && lesser[i] <= 'Z')
				return false;

			//Otherwise they are both numbers and we just need to check if "greater"s is really greater
			if(greater[i] > lesser[i])
				return true;
		}
	}
	//The loop ended without returning, therefore the statement must be false
	return false;
}
//------------------------------------------------------------------------------------------ Less Than <
//Returns true if this comes earlier alphabetically (eg 'A' < 'Z')
bool String::operator<(const String& right)const
{
	//Create temporary formatted versions of the current strings
	String lesser = format(*this);
	String greater = format(right);
	
	//Run through each character and check if the statement is false
	//Using the property (x < y)==(y > x)
	for(int i=0; i<greater.size; ++i)
	{
		//First check to see if the lesster character exists, If not this must be greater
		if(i >= lesser.size)
			return true;

		//Then check if we are dealing with a letter or number (numbers preceed the alphabet)
		if(greater[i] >= 'A' && greater[i] <= 'Z')
		{
			//Check if lesser is a number or letter, if its a number return true
			if(lesser[i] >= '1' && lesser[i] <= '9')
				return true;

			//Otherwise they are both letters and we just need to check if "greater"s is really greater
			if(greater[i] > lesser[i])
				return true;
		}
		//Greater[i] is a number
		else
		{
			//Check if lesser is a number or letter, if its a letter return false
			if(lesser[i] >= 'A' && lesser[i] <= 'Z')
				return false;

			//Otherwise they are both numbers and we just need to check if "greater"s is really greater
			if(greater[i] > lesser[i])
				return true;
		}
	}
	//The loop ended without returning, therefore the statement must be false
	return false;
}
//------------------------------------------------------------------------------------------ Not Equal !=
//Returns true if this is not equal to another string
bool String::operator!=(const String& right)const
{
	//Return the oposite result as boolean equality operator
	return !(*this == right);
}
//------------------------------------------------------------------------------------------ Greater Than Or Equal >=
//Returns true if the strings are equal, or this comes later alphabetically
bool String::operator>=(const String& right)const
{
	//Return true if this is gearter than OR equal to right
	return (*this > right || *this == right);
}
//------------------------------------------------------------------------------------------ Less Than Or Equal <=
//Returns true if the strings are equal or this comes first alphabetically
bool String::operator<=(const String& right)const
{
	//Return true if this is less than OR equal to right
	return (*this < right || *this == right);
}

//================================================================================================== SUBSTRING OPERATORS

//------------------------------------------------------------------------------------------ Accessor []
//Allows you to look at a character of a given index, without changing it
const char String::operator[](const int index)const
{
	//If the character doesnt exist return 0
	if(index >= size || index < 0)
		return 0;

	//Otherwise return the character from the given index
	return substr(index);
}
//------------------------------------------------------------------------------------------ Modifier []
//Lets you look up and modify a particular character os the String
char& String::operator[](const int index)
{
	//If the character doesnt exist throw an exception and return a null char
	if(index >= size || index < 0)
	{
		throw(String("Index out of range"));
		return characters[size];
	}

	//Return a pointer to the character in the String at a given index
	return characters[index];
}

//================================================================================================== INPUT/OUTPUT OPERATORS

//------------------------------------------------------------------------------------------ Output <<
//Prints the String to any output with no formatting
std::ostream& operator<<(std::ostream& out, const String& toPrint)
{
	//Loop through printing each character of the String
	for(int i=0; i<toPrint.length(); ++i)
		out<<toPrint[i];

	//Pass on the output stream for the next guy
	return out;
}
//------------------------------------------------------------------------------------------ Input >>
//Reads in an array from any input terminated by a semi-colon
std::istream& operator>>(std::istream& in, String& toInit)
{
	//Clear out the old variable
	toInit = String();

	//make a temp to store incoming characters
	char temp;

	//Get the first char before looping
	in>>temp;	

	//Fill the String with input from somewhere character by character
	//Only loop if the input isnt a terminating character
	while(temp != '\n' && temp != ';' && temp != '0' && !in.eof())
	{
		//Push the next variable into the String
		toInit += temp;

		//Fetch the remaining characters one by one
		in.get(temp);
	}	
	//Return the input stream for the next guy
	return in;
}
	
//================================================================================================== PRIVATE METHODS

//------------------------------------------------------------------------------------------ Substring
//Returns the character from a given index
char String::substr(const int index)const
{
	//Return the caracter at a given index
	return characters[index];
}
//------------------------------------------------------------------------------------------ Swap
//Switches the contents of this string with another
void String::swap(String& other)
{
	//Swap the "size" variables
	int tempSize = size;
	size = other.size;
	other.size = tempSize;

	//Swap the "allocated" variables
	int tempAlloc = allocated;
	allocated = other.allocated;
	other.allocated = tempAlloc;

	//Swap the "characters" pointers
	char *tempPointer = characters;
	characters = other.characters;
	other.characters = tempPointer;
}

//****************************************************************************************************************************************
//************************************************************************************************** FREE STANDING FONCTIONS AND OPERATORS
//****************************************************************************************************************************************

//================================================================================================== CHARACTER OPERATORS
String operator+ (const char left, const String& right){ return (String(left) + right);  }
bool   operator==(const char left, const String& right){ return (String(left) == right); }
bool   operator!=(const char left, const String& right){ return (String(left) == right); }
bool   operator>=(const char left, const String& right){ return (String(left) >= right); }
bool   operator<=(const char left, const String& right){ return (String(left) <= right); }
bool   operator> (const char left, const String& right){ return (String(left) > right);  }
bool   operator< (const char left, const String& right){ return (String(left) < right);  }

//================================================================================================== CHARACTER ARRAY OPERATORS
String operator+ (const char left[], const String& right){ return (String(left) + right);  }
bool   operator==(const char left[], const String& right){ return (String(left) == right); }
bool   operator!=(const char left[], const String& right){ return (String(left) == right); }
bool   operator>=(const char left[], const String& right){ return (String(left) >= right); }
bool   operator<=(const char left[], const String& right){ return (String(left) <= right); }
bool   operator> (const char left[], const String& right){ return (String(left) > right);  }
bool   operator< (const char left[], const String& right){ return (String(left) < right);  }

//================================================================================================== ADDITIONAL METHODS AND FUNCTIONS

//------------------------------------------------------------------------------------------ Format
//Returns a string in all caps, no spaces or punctuation
String format(const String& toFix)
{
	//Create a holder for the formatted String
	String formatted;

	//Make a temporary character for holding purposes in the loop
	char temp;

	//Loop through the input formatting each character, discarding punctualtion
	for(int i=0; i<toFix.length(); ++i)
	{
		//Init temp to the current character
		temp = toFix[i];

		//Test if the character is a letter or number, otherwise move on
		if((temp >= 'a' && temp <= 'z')||(temp >= 'A' && temp <= 'Z')||(temp >= '0' && temp <= '9'))
		{
			//Check if temp is a lowercase letter, and if so capitalize it
			if(temp >= 'a' && temp <= 'z')
				temp = (temp - 'a' + 'A');

			//Push the formatted character into the formatted string
			formatted += temp;
		}
	}
	//Return the formatted String
	return formatted;
}
