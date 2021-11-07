#ifndef		DYNAMIC_ARRAY_IMPL
#define		DYNAMIC_ARRAY_IMPL

#include "include.h"

#define		DEFAULT_ARRAYSIZE	100

template	<class _T>
class		dynArr {
public:
    // constructors
    constexpr				dynArr<_T>()					noexcept;
    constexpr				dynArr<_T>(size_t reservedSpace)		noexcept;
    constexpr				dynArr(dynArr<_T>& copiedArr)			noexcept;
    constexpr				dynArr(std::initializer_list<_T> _List)		noexcept;



    // operators
    _NODISCARD		_T&		operator[](size_t index);

    // push/pop
			bool		push(_T item);
			_T&		pop();


    _NODISCARD		size_t		length()					noexcept;

    // iterators
    using		iterator =	_T*;
    _NODISCARD		iterator	begin()						const;
    _NODISCARD		iterator	end()						const;



private:
    _NODISCARD		bool		realloc();


private:
    _T*			_ArrayLocation;
    size_t		_ArrayLength;
    size_t		_ArrayAvailableLength;
};


template<class _T>
constexpr dynArr<_T>::dynArr() noexcept
{
    _ArrayLocation		=	(_T*) malloc(sizeof(_T) * DEFAULT_ARRAYSIZE);
    _ArrayLength		=	0;
    _ArrayAvailableLength	=	DEFAULT_ARRAYSIZE;
}


template<class _T>
constexpr dynArr<_T>::dynArr(size_t reservedSpace) noexcept
{
    _ArrayLocation		=	(_T*) malloc(sizeof(_T) * reservedSpace);
    _ArrayLength		=	0;
    _ArrayAvailableLength	=	reservedSpace;
}

template<class _T>
constexpr  dynArr<_T>::dynArr(dynArr<_T>& copiedArr) noexcept
{
    _ArrayLocation		=	(_T*) malloc(sizeof(_T) * copiedArr._ArrayLength);
    _ArrayLength		=	copiedArr._ArrayLength;
    _ArrayAvailableLength	=	copiedArr._ArrayAvailableLength;
    rsize_t copySize		=	copiedArr._ArrayLength;
    memcpy_s(
        _ArrayLocation,
        copySize,
        copiedArr._ArrayLocation,
        copySize
    );
}


template<class _T>
constexpr  dynArr<_T>::dynArr(std::initializer_list<_T> _List) noexcept
{
    _ArrayLocation		=	(_T*) malloc(sizeof(_T)	* _List.size());
    _ArrayLength		=	_List.size();
    _ArrayAvailableLength	=	DEFAULT_ARRAYSIZE > _List.size() ? DEFAULT_ARRAYSIZE : _List.size()	* 2;

    for (size_t i = 0; i < _List.size(); i++)
    {
        _T temp			=	_T(*(_List.begin() + i));
        rsize_t elemSize	=	sizeof(_T);

        memcpy_s(
            (_T*) _ArrayLocation + i,
            elemSize,
            &temp,
            elemSize
        );
    }
}

template<class _T>
_NODISCARD inline _T& dynArr<_T>::operator[](size_t index) {
    return *((_T*)(_ArrayLocation) + index);
}
 
template<class _T>
_NODISCARD inline size_t dynArr<_T>::length() noexcept {
    return _ArrayLength;
}


template<class _T>
 inline bool dynArr<_T>::push(_T item)
 {
    assert (_ArrayLocation != nullptr);

    if (_ArrayLength >= ( _ArrayAvailableLength - 1))
        if (!realloc())
            return false;

    _T* pushloc		=	(_ArrayLocation)+_ArrayLength;
    *pushloc		=	_T(item);

    _ArrayLength++;
    return true;
}

template<class _T>
inline _T& dynArr<_T>::pop()
{
    _ArrayLength--;
    return (_T) * (_ArrayLocation + _ArrayLength - 1);
}




/*
* Finds a new chunk of memory which the array can be placed in. 
*/
template<class _T>
_NODISCARD inline bool dynArr<_T>::realloc()
{
    _T* newLocation	=	nullptr;
    newLocation		=	(_T*)(malloc(sizeof(_T) * _ArrayAvailableLength * 2));

    if (newLocation == nullptr) 
    newLocation		=	(_T*)(malloc(sizeof(_T) * _ArrayAvailableLength + 1));
    
    if (newLocation == nullptr)
    return false;

    memcpy_s(
        newLocation,
        sizeof(_T) * _ArrayAvailableLength * 2, 
        _ArrayLocation, 
        sizeof(_T) * _ArrayLength
    );

    free(_ArrayLocation);
    _ArrayLocation		=	newLocation;
    _ArrayAvailableLength	*=	2;
    return true;
}

template<class _T> _NODISCARD _T* dynArr<_T>::begin() const {
    return  _ArrayLocation;
}

template<class _T> _NODISCARD _T* dynArr<_T>::end() const {
    return  (_ArrayLocation + _ArrayLength);
}




#endif /* !DYNAMIC_ARRAY_IMPL*/
