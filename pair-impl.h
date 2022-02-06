#ifndef PAIR_INCLUDED
#define PAIR_INCLUDED

#include "helpers.h"

/*

PAIR IMPLEMENTATION
___________________
The pair is a static data structure which can contain 2 different data types and packs them together.

declaration: 

pair<T1, T2> x;

or:

pair<int, const char*> x {1,"test"};

or:

pair<int, const char*> x = {1,"test"};

*/

_STDLIB_BEGIN
template <class _ElemType1, class _ElemType2>
class pair {
public:
	pair();		
	pair(const _ElemType1&, const _ElemType2&);
	~pair();

	const void	 operator=(const pair<_ElemType1, _ElemType2>& copy);
	const _ElemType1& first();
	const _ElemType2& second();

	pair<_ElemType1, _ElemType2> swap() noexcept;



private:
	_ElemType1* _first;
	_ElemType2* _second;
};



/*
Defualt constructor for pair. allocates space for 2 objects but leaves uninitialzied.

*/
template <class _ElemType1, class _ElemType2>
pair<_ElemType1, _ElemType2>::pair() {
	assert(sizeof(_ElemType1) > 0 && sizeof(_ElemType2) > 0);
	this->_first = (_ElemType1*)malloc(sizeof(_ElemType1) + sizeof(_ElemType2));
	this->_second = (_ElemType2)(this->_first + 1);

#ifdef DEBUG
	printf("created empty pair at %p", this->_first);
#endif

}


/*
Pair constructor with "initializer list" of 2 objects, can be initialized with {x,y} or (x,y).
Allocates and copies objects into the pair
*/
template <class _ElemType1, class _ElemType2>
pair<_ElemType1, _ElemType2>::pair(const _ElemType1& obj1, const _ElemType2& obj2) {
	assert(sizeof(_ElemType1) > 0 && sizeof(_ElemType2) > 0);
	this->_first = (_ElemType1*)malloc(sizeof(_ElemType1) + sizeof(_ElemType2));
	this->_second = (_ElemType2*)(this->_first + 1);
	memcpy_s(
		(void*)this->_first,
		sizeof(_ElemType1),
		(const void*)&obj1,
		sizeof(_ElemType1)
	);

	memcpy_s(
		(void*)this->_second,
		sizeof(_ElemType2),
		(const void*)&obj2,
		sizeof(_ElemType2)
	);

#ifdef DEBUG
	printf("copied elements to %p", this->_first);
#endif
}

/*
Destructor for pair class. prints debug message when destructor is called.
*/
template <class _ElemType1, class _ElemType2>
pair<_ElemType1, _ElemType2>::~pair() {
#ifdef DEBUG
	printf("out of scope at %p", this->_first);
#endif

}


/*
returns a const reference to the first object in the pair
*/
template <class _ElemType1, class _ElemType2>
const _ElemType1& pair<_ElemType1, _ElemType2>::first() {
	return *this->_first;
}

/*
returns a const reference to the second object in the pair
*/
template <class _ElemType1, class _ElemType2>
const _ElemType2& pair<_ElemType1, _ElemType2>::second() {
	return *this->_second;
}

/*
assignment operator with const pair<>& containing the same types.
*/
template <class _ElemType1, class _ElemType2>
const void pair<_ElemType1, _ElemType2>::operator=(const pair<_ElemType1, _ElemType2>& copy) {
	memcpy_s(
		this,
		sizeof(this),
		copy,
		sizeof(this)
	);
}



/*
swap function for pairs. Can only be swapped if of the same type - not because of laziness, but because it encourages
very bad coding practices and unreadable and difficult to understand code.

Implementation pretty simple, create temp and swap items and then free temp.
*/
template <class _ElemType1, class _ElemType2>
pair<_ElemType1, _ElemType2> pair<_ElemType1, _ElemType2>::swap() noexcept {
	_ElemType1* temp = (_ElemType1*)malloc(sizeof(_ElemType1));
	assert(is_same<_ElemType1, _ElemType2>::value);				// objects of different types may not be swapped.
	memcpy_s(
		temp,
		sizeof(_ElemType1),
		this->_first,
		sizeof(_ElemType1)
	);

	memcpy_s(
		this->_first,
		sizeof(_ElemType1),
		this->_second,
		sizeof(_ElemType1)
	);

	memcpy_s(
		this->_second,
		sizeof(_ElemType1),
		temp,
		sizeof(_ElemType1)
	);
	free(temp);
	return *this;

}

_STDLIB_END

#endif // PAIR_INCLUDED
