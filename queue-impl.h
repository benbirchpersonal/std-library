#pragma once


#include "include.h"
template <class _ElemType>
class queue : public arr<_ElemType> {
public:
			bool		enqueue(_ElemType item)			noexcept;
			_ElemType	dequeue()				noexcept;
private:
	
};


template <class _ElemType>
bool queue<_ElemType>::enqueue(_ElemType elem) noexcept{

}

template <class _ElemType>
_ElemType queue<_ElemType>::dequeue() noexcept {

}
