#pragma once
#ifndef ARRAYIMPL_H
#define ARRAYIMPL_H

#include <memory>
#include <stdio.h>
#include <cassert>

constexpr auto MAX_ARRAYSIZE = 100;
static char ARRAY_OPERATION_BUFFER[MAX_ARRAYSIZE];


template<class T>
class arr {
public:
	arr (int size);
	void print();
	T& operator[](int i);
private:
	size_t _ElemSize;
	size_t _ArraySize;
	void* _ArrayLocaton;
};

template<class T>
inline T& arr<T>::operator[](int i)
{
	assert(i < _ArraySize);
	T temp = *(T*)(malloc(sizeof(T)));
	memcpy((T*)&temp, ((T*)_ArrayLocaton + sizeof(T) * i), sizeof(T));
	return temp;
}

template<class T>
inline arr<T>::arr(int size)
{
	assert(size < MAX_ARRAYSIZE);
	_ElemSize = sizeof(T);
	_ArraySize = size;
	_ArrayLocaton = malloc(sizeof(T) * _ArraySize);
	
}

template<class T>
inline void arr<T>::print()
{
	printf("%i -> %i -> loc: %i", _ElemSize, sizeof(T) * _ArraySize, _ArrayLocaton);
}
// IMPL









#endif /* !ARRAYIMPL_H */


