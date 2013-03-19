#ifndef MRIEDEL_STRING_H
#define MRIEDEL_STRING_H
#include <iostream>
#include <vector>

class String
{
public:
	//Constructors
	String();				//Defaults to an empty string (size = 0)
	String(const char&);	//Creates a string one character long
	String(const char[]);	//Creates a string from a character array ending in '/0' or ';'
	String(const String&);	//Copys a string character by character into this one
	
	//Destructor
	~String();		//Deletes dynamically allocated memory

	//Public Methods
	int length()const;								//Returns the size of the character array
	String subString(const int, const int)const;	//Returns a string from point a to b inclusive
	int findstr(const String&)const;				//Returns the index where the string starts, and -1 if the string was not found
	int findchar(const char)const;					//Returns the index of the first instance of the given character
	void reallocate(const int);						//Changes the size of the array to the size input
	char* toChars() const { return characters; };
	std::vector<String> split(const char) const;	//Splits a string up into a vector of strings designated by a delimiter

	//Equals Operator
	String operator=(String);	//Constant time copy from one string into another

	//Concatenation Operators
	String operator+=(const String&);		//Adds another string to the end of this one
	String operator+(const String&)const;	//Returns a new string that is this string with another tagged on the end

	//Relational Operators
	bool operator==(const String&)const;	//Checks is one string is exactly equal to another
	bool operator>(const String&)const;		//Checks if the string minus punctualtion and special characters comes after another alphabetically
	bool operator<(const String&)const;		//Checks if the string minus punctualtion and special characters comes before another alphabetically
	bool operator!=(const String&)const;	//Checks that the string is not exactly equal to another
	bool operator>=(const String&)const;	//Checks that the formatted string is greater than, or exact string is equal to another
	bool operator<=(const String&)const;	//Checks that the formatted string is less than, or exact string is equal to another
	
	//Substring Operators
	const char operator[](const int)const;	//Returns an unmodifyable copy of a character at a given index
	char& operator[](const int);			//Returns a modifyable reference to a character at a given index

private:
	//Atrributes
	int size;			//The space being used this string
	int allocated;		//The space allocated to this string
	char *characters;	//A list of all characters in this string

	//Private Methods
	char substr(const int)const;	//Returns a copy of a character from a given index
	void swap(String&);				//Switches this string's data with another's (allows const time copy)
};

//Input/Output Operators
std::ostream& operator<<(std::ostream&, const String&);	//Outputs the string character by character
std::istream& operator>>(std::istream&, String&);		//Reads characters into the string until ';' or .eof()

//Character Operators
String operator+ (const char, const String&);		//char + string
bool   operator> (const char, const String&);		//char > string
bool   operator< (const char, const String&);		//char < string
bool   operator==(const char, const String&);		//char == string
bool   operator>=(const char, const String&);		//char >= string
bool   operator<=(const char, const String&);		//char <= string

//Character Array Operators
String operator+ (const char[], const String&);		//char[] + string
bool   operator> (const char[], const String&);		//char[] > string
bool   operator< (const char[], const String&);		//char[] < string
bool   operator==(const char[], const String&);		//char[] == string
bool   operator>=(const char[], const String&);		//char[] >= string
bool   operator<=(const char[], const String&);		//char[] <= string

//Additional Methods and Functions
String format(const String&);		//Removes all punctuation and special characters, makes everything upercase

#endif
