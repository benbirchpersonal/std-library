#pragma once
#ifndef ARRAYIMPL_H
#define ARRAYIMPL_H
#include <memory>
#include <cassert>
#include "string-impl.h"
#include <initializer_list>

constexpr size_t MAX_ARRAYSIZE = 100;
static char ARRAY_OPERATION_BUFFER[MAX_ARRAYSIZE];


template <class _T>
class arr {
public:
	// constructors
	/*
	* defualt constructor, type specified in template argument list <here>()
	*/
	arr(size_t size) noexcept;
	arr(std::initializer_list<_T> _List) noexcept;
	~arr();
	// operators

	/*
	* index access
	*/
	_T& operator[](size_t i);
	// getters

	size_t count();

	_T& first();
	_T& last();



	int findFirstOf(_T search);
	int findLastOf(_T search);
	arr<size_t> find(_T search);

	void swap(size_t index1, size_t index2);
	void print() noexcept;
	void print(size_t index1, size_t index2) noexcept;

	typedef _T* iterator;
	typedef const _T* const_iterator;
	iterator begin() { return (_T*)this->_ArrayLocaton; }
	iterator end() { return (_T*)(this->_ArrayLocaton)+this->_ArraySize; }


private:
	size_t _ElemSize;
	size_t _ArraySize;
	void* _ArrayLocaton;
};



/*
* Constructor
*/
template<class _T>
inline arr<_T>::arr(size_t size) noexcept
{
	assert(size < MAX_ARRAYSIZE);
	_ElemSize = sizeof(_T);
	_ArraySize = size;
	_ArrayLocaton = malloc(_ElemSize * _ArraySize);
}

template<class _T>
inline arr<_T>::arr(std::initializer_list<_T> test) noexcept
{
	assert(test.size() < MAX_ARRAYSIZE);
	_ElemSize = sizeof(_T);
	_ArraySize = test.size();
	_ArrayLocaton = malloc(_ElemSize * _ArraySize);
	for (size_t i = 0; i < _ArraySize; i++)
	{
		_T temp = _T(*(test.begin() + i));
		memcpy_s((_T*)_ArrayLocaton + i,_ElemSize, &temp, _ElemSize);
	}
}


template<class _T>
inline arr<_T>::~arr()
{
	//free(_ArrayLocaton);
}





template<class _T>
inline _T& arr<_T>::operator[](size_t i)
{
	assert(i < _ArraySize);
	return (_T&)*((char*)_ArrayLocaton + (sizeof(_T) * i));
}


template<class _T>
inline size_t arr<_T>::count()
{
	return _ArraySize;
}

template<class _T>
inline _T& arr<_T>::first()
{
	return (_T)*(_T*)(_ArrayLocaton);
}


template<class _T>
inline _T& arr<_T>::last()
{
	return *(reinterpret_cast<_T*>(_ArrayLocaton) + (_ArraySize - 1));
}



/*
* Returns the index of the first occurance of a value in the array
* returns -1 if no occurances of item
* @param searchTerm
*/
template<class _T>
inline int arr<_T>::findFirstOf(_T search)
{
	for (size_t i = 0; i < _ArraySize; i++)
	{
		_T curr = *((char*)_ArrayLocaton + (_ElemSize * (i)));
		if (search == curr)
			return i;
	}

	return -1;
}


/*
* Returns the index of the last occurance of a value in the array
* returns -1 if no occurances of item
* @param searchTerm
*/
template<class _T>
inline int arr<_T>::findLastOf(_T search)
{
	for (size_t i = _ArraySize - 1; i >= 0; i--)
	{
		_T curr = *((char*)_ArrayLocaton + (_ElemSize * (i)));
		if (search == curr)
			return i;
	}
	return -1;
}


template<class _T>
inline arr<size_t> arr<_T>::find(_T search)
{
	int finds = 0;
	for (size_t i = 0; i < _ArraySize; i++)
	{
		_T* curr = ((_T*)_ArrayLocaton) + i;
		if (search == *curr)
			finds++;
	}
	arr<size_t> foundArray(finds);
	finds = 0;
	for (size_t i = 0; i < _ArraySize; i++)
	{
		_T curr = *((char*)_ArrayLocaton + (_ElemSize * (i)));
		if (search == curr) {
			foundArray[finds] = i;
			finds++;
		}
			
	}
	return foundArray;
}


template<class _T>
inline void arr<_T>::swap(size_t index1, size_t index2)
{
	_T* loc1 = (_T*)((char*)_ArrayLocaton + (_ElemSize * index1));
	_T* loc2 = (_T*)((char*)_ArrayLocaton + (_ElemSize * index2));
	_T* temp = reinterpret_cast<_T*>(malloc(_ElemSize));
	memcpy(temp, loc1, _ElemSize);
	memcpy(loc1, loc2, _ElemSize);
	memcpy(loc2, temp, _ElemSize);
	free(temp);

}

template<class _T>
inline void arr<_T>::print() noexcept
{
	for (size_t i = 0; i < _ArraySize; i++)
	{
		_T* current = ((_T*)(_ArrayLocaton)) + i;
		printf(*current);
		printf(" ");
	}
}



template<class _T>
inline void arr<_T>::print(size_t index1, size_t index2) noexcept
{
	assert(index1 < _ArraySize);
	assert(index2 < _ArraySize);
	for (size_t i = index1; i < _ArraySize; i++)
	{
		_T* current = (_T*)(_ArrayLocaton)+i;
		printf(*current);
		printf(" ");
	}
}

#endif /* !ARRAYIMPL_H */
