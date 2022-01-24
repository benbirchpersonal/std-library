#include "includes.h"
#include "helpers.h"

#define DEFAULT_DYNAMIC_ARRAY_SIZE 100

template <class _ElemType>
class dynamicArray : arr<_ElemType> 
{
			dynamicArray<_ElemType>();

private:
	_ElemType*	_DataTail;
	_ElemType* 	_DataHead;
}





template<class _ElemType>
dynamicArray<_ElemType>::dynamicArray(){
	this->_DataTail = static_cast<_ElemType*>(malloc(sizeof(_ElemType) * DEFAULT_DYNAMIC_ARRAY_SIZE));
}
