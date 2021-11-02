#pragma once
#ifndef ARRAYIMPL_H
#define ARRAYIMPL_H

#include <memory>
#include <stdio.h>
#include <cassert>

constexpr size_t MAX_ARRAYSIZE = 100;
static char ARRAY_OPERATION_BUFFER[MAX_ARRAYSIZE];


template<class _T>
class arr {
public:
	// constructors
	/*
	* defualt constructor, type specified in template argument list <here>()
	*/
	arr(size_t size);
	// operators

	/*
	* index access
	*/
	_T& operator[](size_t i);

private:
	size_t _ElemSize;
	size_t _ArraySize;
	void* _ArrayLocaton;
};



/*
* Constructor
*/
template<class _T>
inline arr<_T>::arr(size_t size)
{
	assert(size < MAX_ARRAYSIZE);
	_ElemSize = sizeof(_T);
	_ArraySize = size;
	_ArrayLocaton = malloc(sizeof(_T) * _ArraySize);
}

template<class _T>
inline _T& arr<_T>::operator[](size_t i)
{
	assert(i < _ArraySize);
	return (_T&)*((char*)_ArrayLocaton + (sizeof(_T) * i));
}


#endif /* !ARRAYIMPL_H */

