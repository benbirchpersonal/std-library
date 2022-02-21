#ifndef	ARRAYIMPL_H
#define	ARRAYIMPL_H
#include "helpers.h"
#ifndef MAX_ARRAYSIZE
#define	MAX_ARRAYSIZE 1000
#endif


_STDLIB_BEGIN

template <class _ElemType>
class arr {
public:
	constexpr					arr(size_t size)								noexcept;
	constexpr					arr()										noexcept;



	arr(const arr<_ElemType>& _copiedArr)					noexcept;
	~arr()													noexcept;

	_ElemType& operator[](size_t i);

	_NODISCARD	size_t			count()											noexcept;

	_NODISCARD	_ElemType& first()											noexcept;
	_NODISCARD	_ElemType& last()											noexcept;

	_NODISCARD	int				findFirstOf(_ElemType search);
	_NODISCARD	int				findLastOf(_ElemType search);

	_NODISCARD	stack<size_t> 	find(_ElemType search);

	void			swap(size_t index1, size_t index2);
	void			sort(bool(*greaterThan)(const _ElemType& obj1, const _ElemType obj2));
	void			print();
	void			print(size_t index1, size_t index2);


	using		iterator = _ElemType*;
	_NODISCARD	iterator		begin()										const noexcept;
	_NODISCARD	iterator		end()										const noexcept;

protected:
	_ElemType* _ArrayLocation;
	size_t		_ElemSize;
	size_t		_ArraySize;
	size_t		_InitListcurrentIndex;

public:			// INITIALIZER LIST CONSTRUCTORS

	template <typename... UList, REQUIRES(nonarrow_convertible<_ElemType, UList...>::value)>
	arr(UList &&... vs)
	{
		this->_ElemSize = sizeof(_ElemType);
		this->_ArraySize = 0;
		this->_ArrayLocation = nullptr;
		process(forward<UList>(vs)...);
		processSecondPass(forward<UList>(vs)...);
	}


private:
	// epic compile time polymorphic variadic template recursive initializer list unpacking algorithm
	template <typename U, typename... UList>
	void process(U&& v, UList &&... vs)
	{
		_ArraySize++;
		process(forward<UList>(vs)...);
	}
	template <class _ElemType>
	void process()
	{
		_InitListcurrentIndex = 0;
		_ArrayLocation = (_ElemType*)malloc(sizeof(_ElemType) * _ArraySize);
	}

	template <typename U, typename... UList>
	void processSecondPass(U&& v, UList &&... vs)
	{
		auto x = forward<U>(v);
		memcpy_s(
			_ArrayLocation + _InitListcurrentIndex,
			sizeof(_ElemType),
			&x,
			sizeof(_ElemType)
		);
		_InitListcurrentIndex++;
		processSecondPass(forward<UList>(vs)...);
	}
	void processSecondPass() {}
};



template<class _ElemType>
constexpr arr<_ElemType>::arr(size_t size) noexcept
{
	assert(size < MAX_ARRAYSIZE);

#ifdef DEBUG
	printf("\ncreated \n");
#endif

	_ElemSize = sizeof(_ElemType);
	_ArraySize = size;
	_ArrayLocation = (_ElemType*)malloc(_ElemSize * _ArraySize);
}

/*
* Constructor
*/
template<class _ElemType>
constexpr arr<_ElemType>::arr() noexcept
{


#ifdef DEBUG
	printf("\ncreated \n");
#endif

	_ElemSize = sizeof(_ElemType);
	_ArraySize = 0;
	_ArrayLocation = nullptr;
}


template<class _ElemType>
arr<_ElemType>::arr(const arr<_ElemType>& copiedArr) noexcept
{
	memcpy_s(
		&copiedArr,
		sizeof(copiedArr),
		this,
		sizeof(this)
	);
}

/*
* destrcutor
*/
template<class _ElemType>
inline arr<_ElemType>::~arr() noexcept
{
#ifdef DEBUG
	printf("\n out of scope \n");
#endif
	//free(_ArrayLocation);
}




/*
* accesses an index of the array
*/
template<class _ElemType>
inline _ElemType& arr<_ElemType>::operator[](size_t i)
{
	assert(i < _ArraySize);
	return *((_ElemType*)(_ArrayLocation)+i);
}

/*
* returns size of array
*/
template<class _ElemType>
_NODISCARD size_t arr<_ElemType>::count() noexcept
{
	return _ArraySize;
}
/*
* returns first item in array
*/
template<class _ElemType>
_NODISCARD _ElemType& arr<_ElemType>::first() noexcept
{
	return *_ArrayLocation;
}

/*
* returns last item in array
*/
template<class _ElemType>
_NODISCARD _ElemType& arr<_ElemType>::last() noexcept
{
	return *(_ArrayLocation + (_ArraySize - 1));
}



/*
* Returns the index of the first occurance of a value in the array
* returns -1 if no occurances of item
* @param searchTerm
*/
template<class _ElemType>
_NODISCARD int arr<_ElemType>::findFirstOf(_ElemType search)
{
	for (size_t i = 0; i < _ArraySize; i++)
	{
		_ElemType curr = *(_ArrayLocation + i);
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
template<class _ElemType>
_NODISCARD int arr<_ElemType>::findLastOf(_ElemType search)
{
	for (size_t i = _ArraySize - 1; i >= 0; i--)
	{
		_ElemType curr = *(_ArrayLocation + i);
		if (search == curr)
			return i;
	}
	return -1;
}

/*
* Returns a dynamic array of the indexes of the occurances of a value in the array
* @param searchTerm
*/
template<class _ElemType>
_NODISCARD stack<size_t> arr<_ElemType>::find(_ElemType search)
{
	stack<size_t> foundArray;

	for (size_t i = 0; i < _ArraySize; i++)
	{
		_ElemType curr = *(_ArrayLocation + i);
		if (search == curr)
			foundArray.push(i);
	}
	return foundArray;
}

/**
* Swaps 2 elements in the array.
* physical memory copy 
*/
template<class _ElemType>
inline void arr<_ElemType>::swap(size_t index1, size_t index2)
{
	_ElemType* loc1 = (_ArrayLocation + index1);
	_ElemType* loc2 = (_ArrayLocation + index2);
	_ElemType* temp = (_ElemType*)(malloc(_ElemSize));

	assert(loc1 != nullptr);
	assert(loc2 != nullptr);
	assert(temp != nullptr);

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

/**
* Swaps 2 elements in the array.
* physical memory copy 
*/
template<class _ElemType>
inline void arr<_ElemType>::print()
{
	for (size_t i = 0; i < _ArraySize; i++)
	{
		_ElemType* current = (_ArrayLocation + i);
		printf(*current);
		printf(" ");
	}

	printf("\n");
}

/* ITERATORS */

template<class _ElemType>
_NODISCARD _ElemType* arr<_ElemType>::begin() const noexcept
{
	return  _ArrayLocation;
}

template<class _ElemType>
_NODISCARD _ElemType* arr<_ElemType>::end() const noexcept
{
	return  (_ArrayLocation + _ArraySize);
}
/**
* takes in a fucntion which decides if 1 element of type T is greater than another
* structure -> bool greaterThan(const T& n1, const T& n2); -> should return true if greater than and false if less than.
*/
template<class _ElemType>
void arr<_ElemType>::sort(bool(*greaterThan)(const _ElemType& obj1, const _ElemType obj2))
{
	bool done = false;
	while (!done)
	{
		for (int i = 0; i < this->_ArraySize - 1; i++)
		{
			if (greaterThan(_ArrayLocation + i, _ArrayLocation + i + 1))
			{
				done = false;
				this->swap(i, i + 1);
			}
		}
	}
}

_STDLIB_END



#endif /* !ARRAYIMPL_H */
