/*

MIT License

Copyright (c) 2021 Ben Birch

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef BETTERSTRING_H
#define BETTERSTRING_H
#include <memory>
#include <stdio.h>
#include <cassert>

// string max length
constexpr auto MAX_SIZE = 100;

static char OPERATION_BUFFER[MAX_SIZE];

// forward declarations

class str;
inline void printf(str string);
inline size_t strlen(str string);
template<class T> inline int strcmp(str& string, T& string2);
template<class T> inline int strncmp(str& string, T& string2, size_t n);
template<class T> inline int strstr(str& string, T& searchString);
template<class T> inline str strcat(str& string1, T& string2);

// DECL
class str {
private:
	char _data[MAX_SIZE];
	size_t _length;

public:
	// constructors
	str();
	str(str& x);
	str(char x);
	str(const char* x);
	str(const str& s);
	str(std::shared_ptr<str> x);

	// destructor
	~str();

	// operators
	void operator=(str& otherString);
	void operator=(str otherString);
	void operator=(const char* otherString);

	template<class T>
	str operator+(T otherString);
	//template<class T>
	//str operator+(T& otherString);

	void operator+=(str otherString);
	void operator+=(const char* otherString);
	void operator+=(char otherString);

	// finders
	int containsAt(str& x);
	int containsAt(const char* x);

	bool contains(str& x);
	bool contains(const char* x);

	// comparers
	int compare(str& x);
	int compare(const char* x);

	int compareUntil(str& x, size_t n);
	int compareUntil(const char* x, size_t n);

	str substr(size_t start, size_t length);
	
	int splitBy(str* stringArray, char x);

	// removers
	str remove(char x);
	str removeAt(size_t x);
	str removeRange(size_t x, size_t size);
	void clear();

	// getters and setters
	const char* c_str();
	size_t length();

private:
	// internal functions
	void internalUpdlen();
	void internalInsertString(char* dest, int start, char* src);
	void cMemSet(void* mem, size_t sizeInChars, char chr);
	
};

// IMPL

/**
Default Constructor,
Creates an empty string.
 */
inline str::str() {
#ifdef DEBUG
	printf("\n[empty] created \n");
#endif
	this->_length = 0;
	this->_data[0] = '\0';
}

/**
Default Constructor,
initializes from a char
@param char
 */
inline str::str(char x) {
#ifdef DEBUG
	printf("\n[%c] created \n", x);
#endif
	this->_length = 1;
	this->_data[0] = x;
	this->_data[1] = '\0';
}


/**
Copy Constructor,
Copies a string from non-const value
@param str& baseString
 */
inline str::str(str& copyString)
{
#ifdef DEBUG
	printf("\n[%s] copied \n", _data);
#endif
	memcpy_s(this->_data, sizeof(copyString._data), (const void*)copyString._data, sizeof(this->_data));
	this->_length = copyString._length;
}

/**
Copy Constructor,
Copies a string from const value
@param const str& baseString
 */
inline str::str(const str& x)
{
#ifdef DEBUG
	printf("\ncopied \n");
#endif
	memcpy_s(this->_data, sizeof(x._data), (const void*)x._data, sizeof(this->_data));
	this->_length = x._length;
}

/**
Copy Constructor,
Copies a string from a shared_ptr value,
useful for preventing strings going out of scope
@param std::shared_ptr<str> baseString
 */
inline str::str(std::shared_ptr<str> x)
{
#ifdef DEBUG
	printf("\n[%s] copied \n", _data);
#endif
	memcpy_s(this->_data, sizeof(x.get()->_data), (const void*)x.get()->_data, sizeof(this->_data));
	this->_length = x.get()->_length;
}

/**
Debug only,
shows when strings go out of scope
 */
inline str::~str()
{
#ifdef DEBUG
	printf("\n[%s] out of scope \n", _data);
#endif
}

/**
Constructor from const char*
@param const char* baseString
 */
inline str::str(const char* x)
{
	strcpy_s(this->_data, x);
	internalUpdlen();
	this->_data[this->_length] = '\0';
}

// operator impl
/**
copies string into string
@param str& copiedString
 */
void str::operator=(str& otherString)
{
	memcpy_s(this, sizeof(str), &otherString, sizeof(str));
}
/**
copies string into string
@param str& copiedString
 */
void str::operator=(str otherString)
{
	memcpy_s(this, sizeof(str), &otherString, sizeof(str));
}
/**
copies const char* value into string
@param const char* copiedString
 */
void str::operator=(const char* otherString)
{
	memcpy_s(this->_data, sizeof(char) * MAX_SIZE, otherString, sizeof(otherString));
}

/**
concatenates string with other string
@param str& concatString
 */
/*
template<class T>
str str::operator+(T& otherString)
{
	assert(strlen(*this) + strlen(otherString) < MAX_SIZE);
	str x = this->_data;
	x._length = strlen(*this);
	x += otherString;
	return x;
}
*/


/**
concatenates string with other string
@param str& concatString
 */
template<class T>
str str::operator+(T otherString)
{
	assert(strlen(*this) + strlen(otherString) < MAX_SIZE);
	str x = this->_data;
	x._length = strlen(*this);
	x += otherString;
	return x;
}


/**
concatenates 1 character with += functionality,
modifies original string
@param char concatChar
 */
void str::operator+=(str otherString)
{
	assert((otherString._length) >= 1);
	otherString._data[MAX_SIZE - 1] = '\0';
	internalUpdlen();
	internalInsertString(this->_data, strlen(*this), otherString._data);
	this->_data[MAX_SIZE - 1] = '\0';
}

/**
concatenates with += functionality,
modifies original string
@param const char* concatString
 */
void str::operator+=(const char* otherString)
{
	assert(otherString != nullptr);
	assert(strlen(otherString) >= 1);
	strncpy_s(OPERATION_BUFFER, otherString, MAX_SIZE);
	OPERATION_BUFFER[MAX_SIZE - 1] = '\0';
	internalUpdlen();
	internalInsertString(this->_data, this->_length, OPERATION_BUFFER);
	this->_data[MAX_SIZE - 1] = '\0';
	cMemSet(OPERATION_BUFFER, MAX_SIZE, '\0');
}

/**
concatenates 1 character with += functionality,
modifies original string
@param char concatChar
 */
inline void str::operator+=(char otherString)
{
	if (strlen(*this) < 100) {
		this->_data[_length] = otherString;
		this->_data[_length + 1] = '\0';
		this->_length++;
	}
}

/**
returns index at which the substring x occurs
@param str& substring
 */
inline int str::containsAt(str& x)
{
	assert(strlen(x) >= 1);
	assert(strlen(x) < strlen(*this));
	int xlen = strlen(x);
	int foundCount = 0;
	for (size_t i = 0; i < strlen(*this); i++)
	{
		if (this->_data[i] == x._data[foundCount]) {
			foundCount++;
		}
		else
			foundCount = 0;

		if (foundCount == xlen)
			return (i + 1) - xlen;
	}
	return -1;
}

/**
returns index at which the substring x occurs
@param const char* substring
 */
inline int str::containsAt(const char* x)
{
	assert(x != nullptr);
	assert(strlen(x) >= 1);
	assert(strlen(x) < strlen(*this));
	int xlen = strlen(x);
	int foundCount = 0;
	for (size_t i = 0; i < strlen(*this); i++)
	{
		if (this->_data[i] == x[foundCount]) {
			foundCount++;
		}
		else
			foundCount = 0;

		if (foundCount == xlen)
			return (i + 1) - xlen;
	}
	return -1;
}

/**
returns whether the substring x occurs in the string
@param const char* substring
 */
inline bool str::contains(const char* x)
{
	return containsAt(x) != 0;
}

/**
returns a substring of given position and size
@param int start
@param int length
 */
inline str str::substr(size_t start, size_t length)
{
	assert(start + length <= strlen(*this));
	assert(length >= 1);

	int x = 0;
	for (size_t i = start; i < length; i++, x++)
	{
		OPERATION_BUFFER[x] = this->_data[i];
	}
	OPERATION_BUFFER[x] = '\0';
	str tmp = OPERATION_BUFFER;
	cMemSet(OPERATION_BUFFER, MAX_SIZE, 0);
	return tmp;
}

/**
returns whether the substring x occurs in the string
@param str& substring
 */
inline bool str::contains(str& x)
{
	assert(this->_length >= strlen(x));
	assert(strlen(x) >= 1);
	int xlen = strlen(x);
	int foundCount = 0;
	for (size_t i = 0; i < strlen(*this); i++)
	{
		if (this->_data[i] == x._data[foundCount]) {
			foundCount++;
		}
		else
			foundCount = 0;

		if (foundCount == xlen)
			return true;
	}
	return false;
}
#define MAX(a, b) ((a) > (b) ? (a) : (b))
/**
returns 0 if strings are equal
@param str& stringCmp
 */
inline int str::compare(str& x)
{
	for (size_t i = 0; i < MAX(strlen(*this), strlen(x)); i++)
	{
		if (this->_data[i] != x._data[i])
			return (int)this->_data[i] - (int)x._data[i];
	}
	return 0;
}

/**
returns 0 if strings are equal
@param const char* stringCmp
 */
inline int str::compare(const char* x)
{
	assert(x != nullptr);
	for (size_t i = 0; i < MAX(strlen(*this), strlen(x)); i++)
	{
		if (this->_data[i] != x[i])
			return (int)this->_data[i] - (int)x[i];
	}
	return 0;
}

/**
returns 0 if strings are equal up to n length
@param str& stringCmp
@param size_t n
 */
inline int str::compareUntil(str& x, size_t n)
{
	assert(n < (strlen(x)));
	for (size_t i = 0; i < n; i++)
	{
		if (this->_data[i] != x._data[i])
			return (int)this->_data[i] - (int)x._data[i];
	}
	return 0;
}

/**
returns 0 if strings are equal up to n length
@param const char* stringCmp
@param size_t n
 */
inline int str::compareUntil(const char* x, size_t n)
{
	assert(n < strlen(x));
	for (size_t i = 0; i < n; i++)
	{
		if (this->_data[i] != x[i])
			return (int)this->_data[i] - (int)x[i];
	}
	return 0;
}

/**
clears the string,
self explanatory
 */
inline void str::clear()
{
	this->_data[0] = '\0';
	this->_length = 0;
}

/**
modifies an array of strings, by splitting the original string by the given character.
returns the numbers of segments the string has been split into
@param pointer to string array
@param char given character
 */
inline int str::splitBy(str* stringArray, char x)
{
	size_t splitIndex = 0;
	size_t splitSize = 0;
	for (size_t i = 0; i < strlen(*this); i++)
	{
		if (this->_data[i] != x) {
			stringArray[splitIndex] += this->_data[i];
			splitSize++;
			continue;
		}
		stringArray[splitIndex]._data[splitSize] = '\0';
		splitIndex++;
		splitSize = 0;
	}

	stringArray[splitIndex]._data[splitSize] = '\0';
	return splitIndex + 1;
}

/**
returns a pointer to a new string without the given character
@param char given character
 */
inline str str::remove(char x)
{
	int bufIndex = 0;
	for (size_t i = 0; i < strlen(*this); i++)
	{
		if (this->_data[i] != x) {
			OPERATION_BUFFER[bufIndex] = this->_data[i];
			bufIndex++;
		}
	}
	OPERATION_BUFFER[bufIndex + 1] = '\0';
	str ret = OPERATION_BUFFER;
	cMemSet(OPERATION_BUFFER, bufIndex + 1, 0);
	return ret;
}

/**
returns a new string, removing the given index
@param char given character
 */
inline str str::removeAt(size_t x)
{
	assert(x <= strlen(*this));
	size_t bufIndex = 0;
	for (size_t i = 0; i < strlen(*this); i++)
	{
		if (i != x) {
			OPERATION_BUFFER[bufIndex] = this->_data[i];
			bufIndex++;
		}
	}
	OPERATION_BUFFER[bufIndex + 1] = '\0';
	str ret = OPERATION_BUFFER;
	cMemSet(OPERATION_BUFFER, bufIndex + 1, 0);
	return ret;
}

/**
returns a new string, removing the range between the given index and size
@param char given character
@param size_t given size
 */
inline str str::removeRange(size_t x, size_t size)
{
	assert(strlen(*this) >= size);
	size_t bufIndex = 0;
	for (size_t i = 0; i < strlen(*this); i++)
	{
		if (!(i > x && i <= x + size)) {
			OPERATION_BUFFER[bufIndex] = this->_data[i];
			bufIndex++;
		}
	}
	OPERATION_BUFFER[bufIndex + 1] = '\0';
	str ret = str(OPERATION_BUFFER);
	cMemSet(OPERATION_BUFFER, bufIndex + 1, 0);
	return ret;
}

/**
returns a const char*
 */
inline const char* str::c_str()
{
	_data[MAX_SIZE - 1] = '\0';
	return _data;
}
/**
returns the length of the string
 */
inline size_t str::length() {
	assert(_length >= 0);
	return _length;
}

// INTERNAL IMPL

void str::internalUpdlen() {
	for (unsigned short i = 0; i < MAX_SIZE; i++) {
		if (this->_data[i] == '\0') {
			this->_length = i;
			return;
		}
	}
	this->_length = 0;
	return;
}

void str::internalInsertString(char* dest, int start, char* src) {
	int x = 0;
	assert(start > 0);
	assert(src != nullptr);



	for (size_t i = start; i < MAX_SIZE; i++, x++)
	{
		dest[i] = src[x];
		if (src[x] == '\0')
			return;
	}
}

void str::cMemSet(void* mem, size_t sizeInChars, char byte) {
	char* memchar = (char*)mem;
	for (size_t i = 0; i < sizeInChars; i++)
	{
		memchar[i] = byte;
	}
}

// C STYLE FUNCTION IMPLEMENTATIONS

/**
returns 0 if strings are equal
@param str& string
@param str& / const char* / char[] string2
 */
template<class T>
inline int strcmp(str& string, T& string2)
{
	return string.compare(string2);
}

/**
returns 0 if strings are equal up to n length
@param str& string
@param str& / const char* / char[] string2
 */
template<class T>
inline int strncmp(str& string, T& string2, size_t n)
{
	return string.compareUntil(string2, n);
}


/**
returns index of first string difference
@param str& string
@param str& / const char* / char[] string2
 */
template<class T>
inline int strstr(str& string, T& searchString)
{
	return string.containsAt(searchString);
}

/**
returns length of string
@param str& string
 */
inline size_t strlen(str string)
{
	return string.length();
}

/**
concatenates the strings
@param str& string1
@param str& / const char* / char[] string2
 */
template<class T>
inline str strcat(str& string1, T& string2) {
	return string1 + str(string2);
}

inline void printf(str string) {
	printf(string.c_str());
}


#endif /* !BETTERSTRING_H */
