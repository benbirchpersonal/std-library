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
	size_t 		_ArrayAllocatedSize;
}





template<class _ElemType>
dynamicArray<_ElemType>::dynamicArray(){
	this->_DataTail = static_cast<_ElemType*>(malloc(sizeof(_ElemType) * DEFAULT_DYNAMIC_ARRAY_SIZE));
	this->_DataHead = this->_DataTail + DEFAULT_DYNAMIC_ARRAY_SIZE;
	this->_ArrayLocation = this->_DataTail + DEFAULT_DYNAMIC_ARRAY_SIZE + 1;
	this->_ArraySize = 0;
	this->_ArrayAllocatedSize = DEFAULT_DYNAMIC_ARRAY_SIZE;
}
