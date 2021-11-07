#ifndef		ARRAYIMPL_H
#define		ARRAYIMPL_H

#include	<memory>
#include	<cassert>
#include	<initializer_list>
#include	"dynamic-array.h"

#define		MAX_ARRAYSIZE		100


static char ARRAY_OPERATION_BUFFER[MAX_ARRAYSIZE];

template <class _T>
class arr {
public:
	constexpr					arr(size_t size)						noexcept;
	constexpr					arr()									noexcept;
	constexpr					arr(std::initializer_list<_T> _List)	noexcept;
								~arr()									noexcept;

				_T&				operator[](size_t i);

	_NODISCARD	size_t			count()									noexcept;

	_NODISCARD	_T&				first()									noexcept;
	_NODISCARD	_T&				last()									noexcept;

	_NODISCARD  int				findFirstOf(_T search);
	_NODISCARD  int				findLastOf(_T search);
	_NODISCARD  dynArr<size_t>  find(_T search);

				void			swap(size_t index1, size_t index2);
				void			print();
				void			print(size_t index1, size_t index2);


	using		iterator   =	_T*;
	_NODISCARD	iterator		begin()									const;
	_NODISCARD	iterator		end()									const;

private:

	size_t		_ElemSize;
	size_t		_ArraySize;
	_T*			_ArrayLocation;
};



/*
* Constructor
*/
template<class _T>
constexpr arr<_T>::arr(size_t size) noexcept
{
	assert(size < MAX_ARRAYSIZE);
#ifdef DEBUG
	printf("\ncreated \n");
#endif
	_ElemSize		=		sizeof(_T);
	_ArraySize		=		size;
	_ArrayLocation	=		(_T*)malloc(_ElemSize * _ArraySize);
}

/*
* Constructor
*/
template<class _T>
constexpr arr<_T>::arr() noexcept
{
	assert(size < MAX_ARRAYSIZE);

#ifdef DEBUG
	printf("\ncreated \n");
#endif

	_ElemSize		=		sizeof(_T);
	_ArraySize		=		0;
	_ArrayLocation	=		nullptr;
}

/*
* Constructor
*/
template<class _T>
constexpr arr<_T>::arr(std::initializer_list<_T> _List) noexcept
{
	assert(_List.size() < MAX_ARRAYSIZE);

#ifdef DEBUG
	printf("\ncreated \n");
#endif

	_ElemSize		=		sizeof(_T);
	_ArraySize		=		_List.size();
	_ArrayLocation	=		(_T*) malloc(_ElemSize * _ArraySize);

	for (size_t i = 0; i < _ArraySize; i++)
	{
		_T temp		=		_T(*(_List.begin() + i));
		memcpy_s(
			_ArrayLocation + i,
			_ElemSize,
			&temp,
			_ElemSize
		);
	}
}

/*
* destrcutor
*/
template<class _T>
inline arr<_T>::~arr() noexcept
{
#ifdef DEBUG
	printf("\n out of scope \n");
#endif
	free (_ArrayLocation);
}




/*
* accesses an index of the array
*/
template<class _T>
inline _T& arr<_T>::operator[](size_t i)
{
	assert  (i < _ArraySize);
	return *((_T*)(_ArrayLocation) + i);
}

/*
* returns size of array
*/
template<class _T>
_NODISCARD size_t arr<_T>::count() noexcept
{
	return _ArraySize;
}
/*
* returns first item in array
*/
template<class _T>
_NODISCARD _T& arr<_T>::first() noexcept
{
	return *_ArrayLocation;
}

/*
* returns last item in array
*/
template<class _T>
_NODISCARD _T& arr<_T>::last() noexcept
{
	return *(_ArrayLocation + (_ArraySize - 1));
}



/*
* Returns the index of the first occurance of a value in the array
* returns -1 if no occurances of item
* @param searchTerm
*/
template<class _T>
_NODISCARD int arr<_T>::findFirstOf(_T search)
{
	for (size_t i = 0; i < _ArraySize; i++)
	{
		_T curr		=		*(_ArrayLocation + i);
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
_NODISCARD int arr<_T>::findLastOf(_T search)
{
	for (size_t i = _ArraySize - 1; i >= 0; i--)
	{
		_T curr		=		* ( _ArrayLocation + i );
		if (search == curr)
			return i;
	}
	return -1;
}

/*
* Returns a dynamic array of the indexes of the occurances of a value in the array
* @param searchTerm
*/
template<class _T>
_NODISCARD dynArr<size_t> arr<_T>::find(_T search)
{
	dynArr<size_t> foundArray;

	for (size_t i = 0; i < _ArraySize; i++)
	{
		_T curr		=		*(_ArrayLocation + i);
		if (search == curr)
			foundArray.push(i);
	}
	return foundArray;
}


template<class _T>
inline void arr<_T>::swap(size_t index1, size_t index2)
{
	_T* loc1		=		(_ArrayLocation + index1);
	_T* loc2		=		(_ArrayLocation + index2);
	_T* temp		=		(_T*) (malloc(_ElemSize));
	memcpy_s(
		temp,
		_ElemSize,
		loc1, 
		_ElemSize
	);

	memcpy_s(
		loc1,
		_ElemSize,
		loc2,
		_ElemSize
	);

	memcpy_s(
		loc2,
		_ElemSize,
		temp,
		_ElemSize
	);

	free(temp);

}


template<class _T>
inline void arr<_T>::print()
{
	for (size_t i = 0; i < _ArraySize; i++)
	{
		_T* current		=		( _ArrayLocation + i );
		printf(*current);
		printf(" ");
	}
}



template<class _T>
inline void arr<_T>::print(size_t index1, size_t index2)
{
	assert(index1 < _ArraySize);
	assert(index2 < _ArraySize);

	for (size_t i = index1; i < _ArraySize; i++)
	{
		_T* current		=		 _ArrayLocation + i;
		printf(*current);
		printf(" ");
	}
}


/* ITERATORS */

template<class _T> _NODISCARD _T* arr<_T>::begin() const {
	return  _ArrayLocation;
}

template<class _T> _NODISCARD _T* arr<_T>::end() const {
	return  (_ArrayLocation + _ArraySize);
}





#endif /* !ARRAYIMPL_H */
