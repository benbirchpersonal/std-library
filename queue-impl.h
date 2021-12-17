#ifndef	QUEUE_IMPL
#define	QUEUE_IMPL

#include "include.h"

#define DEFAULT_QUEUE_SIZE 100

template <class _ElemType>
class queue : public arr<_ElemType> {
public:
							queue<_ElemType>();

				bool		enqueue(_ElemType item)			noexcept;
				_ElemType	dequeue()						noexcept;
	override	_ElemType	operator[](size_t i)			noexcept;
private:
	_NODISCARD	void		realloc();
private:
	_ElemType*	_queueHead;
	_ElemType*	_queueTail;

};


template<class _ElemType>
inline queue<_ElemType>::queue()
{
	this->_ElemSize			=	sizeof(_ElemType);
	this->_ArrayLocation	=	malloc(this->_ElemSize * DEFAULT_QUEUE_SIZE);
	this->_queueHead		=	(_ElemType*)this->_ArrayLocation  + (_ElemType*)DEFAULT_QUEUE_SIZE - 1;
	this->_queueTail		=	this->_queueHead;
	this->_ArraySize		=	0;
}


template <class _ElemType>
bool queue<_ElemType>::enqueue(const _ElemType& elem) noexcept {
	this->_queueTail--;
	this->_ArraySize++;
	if(this->_queueTail == this->_ArrayLocation)
		assert(realloc()); // Allocation failed, overflow? not enough heap memory.
	memcpy_s(
		this->_ArrayLocation + this->_queueTail,
		&elem,
		_ElemSize,
		_ElemSize
	);
}

template<class _ElemType>
_NODISCARD inline bool stack<_ElemType>::realloc()
{
	_ElemType* relativeTail =	this->_queueTail - this->_ArrayLocation;
	_ElemType* relativeHead =	this->_queueHead - this->_ArrayLocation;

	_ElemType* newLocation	=	reinterpret_cast<_ElemType*>(malloc(sizeof(_ElemType) * this->_ArrayAvailableSize * 2));
	if (newLocation == nullptr)
	return false;
	this->_ArrayAvailableSize	*=	2;
	memcpy_s(
		newLocation,
		sizeof(_ElemType) * this->_ArrayAvailableSize,
		this->_ArrayLocation,
		sizeof(_ElemType) * this->_ArraySize
	);

	free(this->_ArrayLocation);

	this->_ArrayLocation			=	newLocation;
	this->_queueHead 			= 	this->_ArrayLocation + relativeHead;
	this->_queueTail 			= 	this->_ArrayLocation + relativeTail;

	return true;
}

template <class _ElemType>
_ElemType queue<_ElemType>::dequeue() noexcept {
	assert(this->_ArraySize > 0);
	assert(this->_queueHead != this->_queueTail);
	this->_queueHead--;
	this->_ArraySize--;
}

#endif /*QUEUE_IMPL*/


