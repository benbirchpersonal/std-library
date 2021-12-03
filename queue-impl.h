#ifndef	QUEUE_IMPL
#define	QUEUE_IMPL

#include "include.h"

#define DEFAULT_QUEUE_SIZE 100

template <class _ElemType>
class queue : public arr<_ElemType> {
public:
					queue<_ElemType>();

			bool		enqueue(_ElemType item)			noexcept;
			_ElemType	dequeue()				noexcept;
	override	_ElemType	operaror[](size_t i)			noexcept;
private:
			void		reallocate();
private:
	_ElemType*	_queueHead;
	_ElemType*	_queueTail;

};


template<class _ElemType>
inline queue<_ElemType>::queue()
{
	this->_ElemSize			=	sizeof(_ElemType);
	this->_ArrayLocation		=	malloc(this->_ElemSize * DEFAULT_QUEUE_SIZE);
	this->_queueHead		=	this->_ArrayLocation   + DEFAULT_QUEUE_SIZE;
	this->_queueTail		=	this->_queueHead;
	this->_ArraySize		=	0;
}


template <class _ElemType>
bool queue<_ElemType>::enqueue(_ElemType elem) noexcept {
}

template <class _ElemType>
_ElemType queue<_ElemType>::dequeue() noexcept {
	assert(this->_ArraySize > 0); 								// Empty Queue
}

#endif /*QUEUE_IMPL*/



