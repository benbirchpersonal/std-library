#ifndef	DYNAMIC_ARRAY_IMPL
#define	DYNAMIC_ARRAY_IMPL

#include "include.h"

#define	DEFAULT_ARRAYSIZE 100

template	<class _T>
class		dynArr : public arr<_T> {
public:
    // constructors
    constexpr				dynArr<_T>()					noexcept;
    constexpr				dynArr<_T>(size_t reservedSpace)		noexcept;
    constexpr				dynArr(dynArr<_T>& copiedArr)			noexcept;
    constexpr				dynArr(std::initializer_list<_T> _List)		noexcept;

    // push/pop
			bool		push(_T item)					noexcept;
			_T&		pop()						noexcept;
private:
    _NODISCARD		bool		realloc();

private:
    size_t		_ArrayAvailableSize;
};


template<class _T>
constexpr dynArr<_T>::dynArr() noexcept
{
    this->_ArrayLocation		=	(_T*) malloc(sizeof(_T) * DEFAULT_ARRAYSIZE);
    this->_ArraySize			=	0;
    this->_ArrayAvailableSize		=	DEFAULT_ARRAYSIZE;
}


template<class _T>
constexpr dynArr<_T>::dynArr(size_t reservedSpace) noexcept
{
	this->_ArrayLocation		=	(_T*) malloc(sizeof(_T) * reservedSpace);
	this->_ArraySize		=	0;
	this->_ArrayAvailableSize	=	reservedSpace;
}

template<class _T>
constexpr  dynArr<_T>::dynArr(dynArr<_T>& copiedArr) noexcept
{
	this->_ArrayLocation		=	(_T*) malloc(sizeof(_T) * copiedArr._ArraySize);
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


template<class _T>
constexpr  dynArr<_T>::dynArr(std::initializer_list<_T> _List) noexcept
{
	this->_ArrayLocation		=	(_T*) malloc(sizeof(_T)	* _List.size());
	this->_ArraySize		=	_List.size();
	this->_ArrayAvailableSize	=	DEFAULT_ARRAYSIZE > _List.size() ? DEFAULT_ARRAYSIZE : _List.size()	* 2;

	for (size_t i = 0; i < _List.size(); i++)
	{
		_T temp			=	_T(*(_List.begin() + i));
		rsize_t elemSize	=	sizeof(_T);

		memcpy_s(
			(_T*)this->_ArrayLocation + i,
			elemSize,
			&temp,
			elemSize
		);
	}
}

template<class _T>
 inline bool dynArr<_T>::push(_T item) noexcept
 {
	assert (this->_ArrayLocation != nullptr);

	if (this->_ArraySize >= (this->_ArrayAvailableSize - 1))
	if (!realloc())
		return false;

	_T* pushloc		=	(this->_ArrayLocation)+ this->_ArraySize;
	*pushloc		=	_T(item);

	this->_ArraySize++;
	return true;
}

template<class _T>
inline _T& dynArr<_T>::pop() noexcept
{
	this->_ArraySize--;
	return (_T) * (this->_ArrayLocation + this->_ArraySize - 1);
}

/*
* Finds a new chunk of memory which the array can be placed in. 
*/
template<class _T>
_NODISCARD inline bool dynArr<_T>::realloc()
{
	_T* newLocation		=	nullptr;
	newLocation		=	(_T*)(malloc(sizeof(_T) * this->_ArrayAvailableSize * 2));

	if (newLocation == nullptr) 
	newLocation		=	(_T*)(malloc(sizeof(_T) * this->_ArrayAvailableSize + 1));
    
	if (newLocation == nullptr)
	return false;

	memcpy_s(
	newLocation,
	sizeof(_T) * this->_ArrayAvailableSize * 2,
		this->_ArrayLocation,
	sizeof(_T) * this->_ArraySize
	);

	free(this->_ArrayLocation);
	this->_ArrayLocation		=	newLocation;
	this->_ArrayAvailableSize	*=	2;
	return true;
}


#endif /* !DYNAMIC_ARRAY_IMPL*/
