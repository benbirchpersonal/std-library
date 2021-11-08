#ifndef	DYNAMIC_ARRAY_IMPL
#define	DYNAMIC_ARRAY_IMPL

#include "include.h"

#define	DEFAULT_ARRAYSIZE 100

template	<class _ElemType>
class		dynArr : public arr<_ElemType> {
public:
    // constructors
    constexpr				dynArr<_ElemType>()					noexcept;
    constexpr				dynArr<_ElemType>(size_t reservedSpace)			noexcept;
    constexpr				dynArr(dynArr<_ElemType>& copiedArr)			noexcept;
    constexpr				dynArr(std::initializer_list<_ElemType> _List)		noexcept;

    // push/pop
			bool		push(_ElemType item)					noexcept;
			_ElemType&	pop()							noexcept;
private:
    _NODISCARD		bool		realloc();

private:
    size_t		_ArrayAvailableSize;
};


template<class _ElemType>
constexpr dynArr<_ElemType>::dynArr() noexcept
{
    this->_ArrayLocation		=	(_ElemType*) malloc(sizeof(_ElemType) * DEFAULT_ARRAYSIZE);
    this->_ArraySize			=	0;
    this->_ArrayAvailableSize		=	DEFAULT_ARRAYSIZE;
}


template<class _ElemType>
constexpr dynArr<_ElemType>::dynArr(size_t reservedSpace) noexcept
{
	this->_ArrayLocation		=	(_ElemType*) malloc(sizeof(_ElemType) * reservedSpace);
	this->_ArraySize		=	0;
	this->_ArrayAvailableSize	=	reservedSpace;
}

template<class _ElemType>
constexpr  dynArr<_ElemType>::dynArr(dynArr<_ElemType>& copiedArr) noexcept
{
	this->_ArrayLocation		=	(_ElemType*) malloc(sizeof(_ElemType) * copiedArr._ArraySize);
	this->_ArraySize		=	copiedArr._ArraySize;
	this->_ArrayAvailableSize	=	copiedArr._ArrayAvailableSize;
	rsize_t copySize		=	copiedArr._ArraySize;

	memcpy_s(
		this->_ArrayLocation,
		copySize,
		copiedArr._ArrayLocation,
		copySize
	);
}


template<class _ElemType>
constexpr  dynArr<_ElemType>::dynArr(std::initializer_list<_ElemType> _List) noexcept
{
	this->_ArrayLocation		=	(_ElemType*) malloc(sizeof(_ElemType)	* _List.size());
	this->_ArraySize		=	_List.size();
	this->_ArrayAvailableSize	=	DEFAULT_ARRAYSIZE > _List.size() ? DEFAULT_ARRAYSIZE : _List.size()	* 2;

	for (size_t i = 0; i < _List.size(); i++)
	{
		_ElemType temp		=	_ElemType(*(_List.begin() + i));
		rsize_t elemSize	=	sizeof(_ElemType);

		memcpy_s(
			(_ElemType*)this->_ArrayLocation + i,
			elemSize,
			&temp,
			elemSize
		);
	}
}

template<class _ElemType>
 inline bool dynArr<_ElemType>::push(_ElemType item) noexcept
 {
	assert (this->_ArrayLocation != nullptr);

	if (this->_ArraySize >= (this->_ArrayAvailableSize - 1))
	if (!realloc())
		return false;

	_ElemType* pushloc	=	(this->_ArrayLocation)+ this->_ArraySize;
	*pushloc		=	_ElemType(item);

	this->_ArraySize++;
	return true;
}

template<class _ElemType>
inline _ElemType& dynArr<_ElemType>::pop() noexcept
{
	this->_ArraySize--;
	return (_ElemType) * (this->_ArrayLocation + this->_ArraySize - 1);
}

/*
* Finds a new chunk of memory which the array can be placed in. 
*/
template<class _ElemType>
_NODISCARD inline bool dynArr<_ElemType>::realloc()
{
	_ElemType* newLocation		=	nullptr;
	newLocation			=	(_ElemType*)(malloc(sizeof(_ElemType) * this->_ArrayAvailableSize * 2));

	if (newLocation == nullptr) 
	newLocation			=	(_ElemType*)(malloc(sizeof(_ElemType) * this->_ArrayAvailableSize + 1));
    
	if (newLocation == nullptr)
	return false;

	memcpy_s(
	newLocation,
	sizeof(_ElemType) * this->_ArrayAvailableSize * 2,
		this->_ArrayLocation,
	sizeof(_ElemType) * this->_ArraySize
	);

	free(this->_ArrayLocation);
	this->_ArrayLocation		=	newLocation;
	this->_ArrayAvailableSize	*=	2;
	return true;
}


#endif /* !DYNAMIC_ARRAY_IMPL*/
