#ifndef	STRINGIMPL_H
#define	STRINGIMPL_H

#include "include.h"

// string max length
#define		MAX(a, b)	((a) > (b) ? (a) : (b))
#define		MAX_SIZE	100
static char OPERATION_BUFFER[MAX_SIZE];

// DECL
class str {

public:
		// constructors
			str()							noexcept;
			str(str& x)						noexcept;
			str(char x)						noexcept;
			str(const char* x)					noexcept;
			str(const str& s)					noexcept;
			~str()							noexcept;

		// finders
	_NODISCARD	int		contains(str& x)			noexcept;
	_NODISCARD	int		contains(const char* x)			noexcept;

		// comparers
	_NODISCARD	int		compare(str& x)				noexcept;
	_NODISCARD	int		compare(const char* x)			noexcept;
	_NODISCARD	int		compareUntil(str& x, size_t n)		noexcept;
	_NODISCARD	int		compareUntil(const char* x, size_t n)	noexcept;
	_NODISCARD	str		substr(size_t start, size_t length)	noexcept;

		// removers
	_NODISCARD	str		remove(char x)				noexcept;
	_NODISCARD	str		removeAt(size_t x)			noexcept;
	_NODISCARD	str		removeRange(size_t x, size_t size)	noexcept;
	constexpr	void		clear()					noexcept;

		//misc
	_NODISCARD	str		Xor(uint8_t key)			noexcept;
	_NODISCARD	int		splitBy(str* stringArray, char x)	noexcept;

		// getters and setters
	_NODISCARD	const char*	c_str()					noexcept;
	_NODISCARD	size_t		length()				noexcept;


	template	<class _ElemType>
	_NODISCARD	str		operator+(_ElemType otherString);
			void		operator=(str& otherString);
			void		operator=(str otherString);
			void		operator=(const char* otherString);
	_NODISCARD	bool		operator==(str otherString);
			void		operator+=(str otherString);
			void		operator+=(const char* otherString);
			void		operator+=(char otherString);
	_NODISCARD	char&		operator[](size_t index);


private:
		// internal functions
			void		internalUpdlen();
			void		internalInsertString(char* dest, int start, char* src);
			void		cMemSet(void* mem, size_t sizeInChars, char chr);

private:
	char		_data[MAX_SIZE];
	size_t		_length;
};





inline				void		printf(str string);
inline				size_t		strlen(str string);
template<class _ElemType>	int		strcmp(str& string, _ElemType& string2);
template<class _ElemType>	int		strncmp(str& string, _ElemType& string2, size_t n);
template<class _ElemType>	int		strstr(str& string, _ElemType& searchString);
template<class _ElemType>	str		strcat(str& string1, _ElemType& string2);




// IMPL

/**
Default Constructor,
Creates an empty string.
 */
str::str() noexcept
{
#ifdef DEBUG
	printf("\n[empty] created \n");
#endif
	_length		=	1;
	_data[0]	=	'\0';
}

/**
Default Constructor,
initializes from a char
@param char
 */
str::str(char x) noexcept
{
#ifdef DEBUG
	printf("\n[%c] created \n", x);
#endif
	_length		=	1;
	_data[0]	=	x;
	_data[1]	=	'\0';					// Creates string consisting only of one char and null termination character
}


/**
Copy Constructor,
Copies a string from non-const value
@param str& baseString
 */
str::str(str& copyString) noexcept
{
	assert (&copyString != nullptr);				// copied string is nullptr
#ifdef DEBUG
	printf("\n[%s] copied \n", _data);
#endif
	rsize_t dataSize	=	sizeof(_data);
	_length			=	copyString._length;
	memcpy_s(							// Copies the string data into the new string object
		_data, 
		dataSize,
		(const void*) copyString._data, 
		dataSize
	);
}

/**
const Copy Constructor,
Copies a string from const value
@param const str& baseString
 */
str::str(const str& x) noexcept
{
	assert (&x != nullptr);						// x is nullptr
#ifdef DEBUG
	printf("\ncopied \n");
#endif

	rsize_t dataSize	=	sizeof(x._data);	
	_length			=	x._length;
	memcpy_s(							// Copies the string data into the new string object
		_data,
		dataSize,
		(const void*)x._data, 
		dataSize
	);
}

/**
Constructor from const char*
@param const char* baseString
 */
str::str(const char* x) noexcept
{
	assert (x != nullptr);						// x is nullptr
	strncpy_s(							// copy the const char* up to the null terminating character, or max string size,
		_data,							// whichever comes first.
		x,
		MAX_SIZE
	);

	_length			=	strlen(x);			// ensure that the last char is a null termination character
	_data[_length]		=	'\0';
}


/**
Debug only,
shows when strings go out of scope
 */
inline str::~str() noexcept
{
#ifdef DEBUG
	printf("\n[%s] out of scope \n", _data);			// debug only, no need to free memory as is declared on stack.
#endif
}



// operator impl



_NODISCARD char& str::operator[](size_t index) {
	assert (index < _length);					// Index is larger than length of array
	char*   test		=	(char*) _data + index;		// Retrieves the pointer of the char at the index
	return *test;
}

/**
copies string into string
@param str& copiedString
 */
void str::operator=(str& otherString)
{
	assert (&otherString != nullptr);				// other string is nullptr
	memcpy_s(this,							// copies string into other string memory location
		sizeof(str),
		&otherString,
		sizeof(str)
	);
}
/**
copies string into string
@param str& copiedString
 */
void str::operator=(str otherString)
{
	assert (&otherString != nullptr);				// other string is nullptr
	memcpy_s(this,							// copies string into other string memory location
		sizeof(str),
		&otherString,
		sizeof(str)
	);
}
/**
copies const char* value into string
@param const char* copiedString
 */
void str::operator=(const char* otherString)
{
	assert (otherString != nullptr);				// other string is nullptr
	memcpy_s(_data,							// copies string into other string memory location
		sizeof(char) * MAX_SIZE,
		otherString,
		sizeof(otherString)
	);
	_length		=	strlen(otherString);			// sets length
	_data[_length]	=	'\0';					// ensures null termination
}

/*
concatenates string with other string
@param str& concatString
 */
template<class _ElemType>
_NODISCARD str str::operator+(_ElemType otherString)
{
	 assert (strlen(*this) + strlen(otherString) < MAX_SIZE);	// concatenated string lengths sum to larger than max size
	 str x		=	_data;
	 x._length	=	strlen(*this);
	 x		+=	otherString;
	 return x;
 }
 
/**
concatenates string with += functionality,
modifies original string
@param char concatChar
 */
void str::operator+=(str otherString)
{
	assert (otherString._length >= 1);				// concatenating an empty string
	otherString._data[MAX_SIZE - 1]	=	'\0';			// ensure null termination
	internalUpdlen();
	internalInsertString(						// add the string
		_data,
		_length,
		otherString._data
	);
	_data[MAX_SIZE - 1]		=	'\0';			// ensure null termination
}

/**
concatenates with += functionality,
modifies original string
@param const char* concatString
 */
void str::operator+=(const char* otherString)
{
	assert (otherString != nullptr);				// const char* is nullptr
	assert (strlen(otherString) >= 1);				// const char* is empty

	internalUpdlen();
	internalInsertString(
		_data, 
		_length,
		(char*)otherString
	);
	_data[MAX_SIZE - 1]		=	'\0';

}

/**
concatenates 1 character with += functionality,
modifies original string
@param char concatChar
 */
inline void str::operator+=(char otherString)
{
	if (_length > MAX_SIZE - 2)
		return; 

	_data[_length]		=	otherString;
	_data[_length + 1]	=	'\0';
	_length++;
	
}

_NODISCARD bool str::operator==(str otherString)
{
	return (compare(otherString) == 0);
}


/**
returns a substring of given position and size
@param int start
@param int length
 */
inline str str::substr(size_t start, size_t length) noexcept
{
	assert (start + length <= _length);
	assert (length >= 1);

	int x			=	0;
	for (size_t i = start; i < length; i++, x++)
	{
		OPERATION_BUFFER[x] = _data[i];
	}

	OPERATION_BUFFER[x]	=	'\0';
	str tmp			=	OPERATION_BUFFER;
	cMemSet(
		OPERATION_BUFFER, 
		MAX_SIZE, 
		0
	);
	return tmp;
}

 /**
 returns index at which the substring x occurs
 @param str& substring
  */
inline int str::contains(str& x) noexcept
{
	int xlen	=	x._length;
	int foundCount	=	0;
	assert (xlen >= 1);
	assert (&x != nullptr);
	assert (xlen <= _length);
	

	for (size_t i = 0; i < _length; i++)
	{
		if (_data[i] == x._data[foundCount]) {
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
@param str& substring
 */
inline int str::contains(const char* x) noexcept
{
	int xlen		=	strlen(x);
	int foundCount		=	0;
	assert (xlen >= 1);
	assert (&x != nullptr);
	assert (xlen <= _length);
	
	for (size_t i = 0; i < _length; i++)
	{
		if (_data[i] == x[foundCount]) {
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
returns 0 if strings are equal
@param str& stringCmp
 */
inline int str::compare(str& x) noexcept
{
	for (size_t i = 0; i < MAX(_length, x._length); i++)
	{
		if (_data[i] != x._data[i])
			return (int)_data[i] - (int)x._data[i];
	}
	return 0;
}

/**
returns 0 if strings are equal
@param const char* stringCmp
 */
inline int str::compare(const char* x) noexcept
{
	assert (x != nullptr);
	for (size_t i = 0; i < MAX(_length, strlen(x)); i++)
	{
		if (_data[i] != x[i])
			return (int)_data[i] - (int)x[i];
	}
	return 0;
}

/**
returns 0 if strings are equal up to n length
@param str& stringCmp
@param size_t n
 */
inline int str::compareUntil(str& x, size_t n) noexcept
{
	assert (n < (x._length));
	for (size_t i = 0; i < n; i++)
	{
		if (_data[i] != x._data[i])
			return (int)_data[i] - (int)x._data[i];
	}
	return 0;
}

/**
returns 0 if strings are equal up to n length
@param const char* stringCmp
@param size_t n
 */
inline int str::compareUntil(const char* x, size_t n) noexcept
{
	assert (n < strlen(x));
	for (size_t i = 0; i < n; i++)
	{
		if (_data[i] != x[i])
			return (int)_data[i] - (int)x[i];
	}
	return 0;
}

/**
clears the string,
self explanatory
 */
constexpr void str::clear() noexcept
{
	_data[0]	=	'\0';
	_length		=	0;
}

/**
modifies an array of strings, by splitting the original string by the given character.
returns the numbers of segments the string has been split into
@param pointer to string array
@param char given character
 */
inline int str::splitBy(str* stringArray, char x) noexcept
{
	size_t splitIndex	=	0;
	size_t splitSize	=	0;
	for (size_t i = 0; i < _length; i++)
	{
		if (_data[i] != x) {
			stringArray[splitIndex]	+= _data[i];
			splitSize++;
			continue;
		}
		stringArray[splitIndex]._data[splitSize] = '\0';
		splitIndex++;
		splitSize	=	0;
	}

	stringArray[splitIndex]._data[splitSize] = '\0';
	return splitIndex + 1;
}

/**
returns a pointer to a new string without the given character
@param char given character
 */
inline str str::remove(char x) noexcept
{
	int bufIndex			=	0;
	for (size_t i = 0; i < _length; i++)
	{
		if (_data[i] != x) {
			OPERATION_BUFFER[bufIndex] = _data[i];
			bufIndex++;
		}
	}
	OPERATION_BUFFER[bufIndex + 1]	=	'\0';
	str ret				=	OPERATION_BUFFER;
	cMemSet(
		OPERATION_BUFFER, 
		bufIndex + 1, 
		0
	);
	return ret;
}

/**
returns a new string, removing the given index
@param char given character
 */
inline str str::removeAt(size_t x) noexcept
{
	assert (x <= _length);
	size_t bufIndex			=	0;
	for (size_t i = 0; i < _length; i++)
	{
		if (i != x) {
			OPERATION_BUFFER[bufIndex] = _data[i];
			bufIndex++;
		}
	}
	OPERATION_BUFFER[bufIndex + 1]	=	'\0';
	str ret				=	OPERATION_BUFFER;
	cMemSet(
		OPERATION_BUFFER, 
		bufIndex + 1, 
		0
	);
	return ret;
}

/**
returns a new string, removing the range between the given index and size
@param char given character
@param size_t given size
 */
inline str str::removeRange(size_t x, size_t size) noexcept
{
	assert (_length >= size);
	size_t bufIndex		=		0;
	for (size_t i = 0; i < _length; i++)
	{
		if (!(i > x && i <= x + size)) {
			OPERATION_BUFFER[bufIndex] = _data[i];
			bufIndex++;
		}
	}
	OPERATION_BUFFER[bufIndex + 1]	=	'\0';
	str ret				=	str(OPERATION_BUFFER);
	cMemSet(
		OPERATION_BUFFER, 
		bufIndex + 1, 
		0
	);
	return ret;
}

/**
returns a const char*
 */
inline const char* str::c_str() noexcept
{
	assert (_length < MAX_SIZE);
	_data[_length]		=	'\0';
	return _data;
}
/**
returns the length of the string
 */
inline size_t str::length() noexcept 
{
	assert (_length >= 0);
	return _length;
}

/*
* xor encryption with int key
*/
inline str str::Xor(uint8_t key) noexcept
{
	for (size_t i = 0; i < _length; i++)		 
	{
		*(_data + i) = (*(char*)(_data + i) ^ key);
	}
	return str(*this);
}


// INTERNAL IMPL

void str::internalUpdlen() 
{
	for (size_t i = 0; i < MAX_SIZE; i++) {
		if (_data[i] == '\0') {
			_length = i;
			return;
		}
	}
	_length		=	0;
	return;
}

void str::internalInsertString(char* dest, int start, char* src) {
	int x	=	0;
	assert (start > 0);
	assert (src != nullptr);

	for (size_t i = start; i < MAX_SIZE; i++, x++)
	{
		dest[i]		=	src[x];
		if (src[x] == '\0')
			return;
	}
}

void str::cMemSet(void* mem, size_t sizeInChars, char byte) {
	char* memchar		=	(char*)mem;
	for (size_t i = 0; i < sizeInChars; i++)
	{
		memchar[i]	=	 byte;
	}
}

// C STYLE FUNCTION IMPLEMENTATIONS

/**
returns 0 if strings are equal
@param str& string
@param str& / const char* / char[] string2
 */
template<class _ElemType>
inline int strcmp(str& string, _ElemType& string2)
{
	return string.compare(string2);
}

/**
returns 0 if strings are equal up to n length
@param str& string
@param str& / const char* / char[] string2
 */
template<class _ElemType>
inline int strncmp(str& string, _ElemType& string2, size_t n)
{
	return string.compareUntil(string2, n);
}


/**
returns index of first string difference
@param str& string
@param str& / const char* / char[] string2
 */
template<class _ElemType>
int strstr(str& string, _ElemType& searchString)
{
	return string.contains(searchString);
}

/**
returns length of string
@param str& string
 */
size_t strlen(str string)
{
	return string.length();
}

/**
concatenates the strings
@param str& string1
@param str& / const char* / char[] string2
 */
template<class _ElemType>
str strcat(str& string1, _ElemType& string2) {
	return string1 + str(string2);
}

/*
* outputs the string to the console window
*/
void printf(str string) {
	printf(string.c_str());
}


#endif /* !STRINGIMPL_H */
