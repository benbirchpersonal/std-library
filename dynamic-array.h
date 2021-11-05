#ifndef DYNAMIC_ARRAY_IMPL
#define DYNAMIC_ARRAY_IMPL

#include <memory>
#include <cassert>

template <class _T>
class dynArr {
public:
	dynArr<_T>();
	dynArr<_T>(size_t reservedSpace);
private:
	_T* _ArrayLocation;
	size_t _ArrayLength;
	size_t _ArrayAvailableLength;
};


template<class _T>
inline dynArr<_T>::dynArr()
{
	_ArrayLocation = malloc(sizeof(_T) * 100);
	_ArrayLength = 0;
	_ArrayAvailableLength = 100;
}


template<class _T>
inline dynArr<_T>::dynArr(size_t reservedSpace)
{
	_ArrayLocation = malloc(sizeof(_T) * reservedSpace);
	_ArrayLength = 0;
	_ArrayAvailableLength = reservedSpace;
}





#endif /* !DYNAMIC_ARRAY_IMPL*/




