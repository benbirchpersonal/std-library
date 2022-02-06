#ifndef	CIRCULAR_QUEUE_IMPL
#define	CIRCULAR_QUEUE_IMPL

#include "include.h"
#define DEBUG
template <class _ElemType>
class circularQueue : public arr<_ElemType> {
public:
				circularQueue<_ElemType>(size_t queueSize);
				circularQueue<_ElemType>(std::initializer_list<_ElemType> initList);

	bool		enqueue(const _ElemType& item)				noexcept;
	_ElemType	dequeue()									noexcept;
	_ElemType	operator[](size_t i)						noexcept;

public:


	_NODISCARD  void		realloc();
	bool		reserve(size_t newSize);

	int _QueueHead;
	int _QueueTail;


};

template<class _ElemType>
inline circularQueue<_ElemType>::circularQueue(size_t queueSize)
{
	this->_ArrayLocation = (_ElemType*)malloc(sizeof(_ElemType) * queueSize);
#ifdef DEBUG
	memset(this->_ArrayLocation, 0, sizeof(_ElemType) * queueSize);
#endif	
	this->_ArraySize = queueSize;
	this->_QueueHead = -1;
	this->_QueueTail = -1;

}

template<class _ElemType>
inline circularQueue<_ElemType>::circularQueue(std::initializer_list<_ElemType> initList)
{

	this->_ArrayLocation = (_ElemType*)malloc(sizeof(_ElemType) * initList.size());
#ifdef DEBUG
	memset(this->_ArrayLocation, 0, sizeof(_ElemType) * initList.size());
#endif	
	this->_ArraySize = initList.size();
	this->_QueueHead = -1;
	this->_QueueTail = -1;

	for (const _ElemType& x : initList)
		this->enqueue(x);

}

template<class _ElemType>
inline bool circularQueue<_ElemType>::enqueue(const _ElemType& item) noexcept
{
	if ((this->_QueueHead == 0 && this->_QueueTail == this->_ArraySize - 1) || (this->_QueueTail == (this->_QueueHead - 1) % (this->_ArraySize - 1)) )
		return false;

	else if (this->_QueueHead == -1) {
		this->_QueueHead = 0;
		this->_QueueTail = 0;
		memcpy(
			this->_ArrayLocation + this->_QueueTail,
			&item,
			sizeof(item)
		);
		return true;
	}

	else if ((this->_QueueTail == (this->_ArraySize - 1)) && (this->_QueueHead != 0)) {
		this->_QueueTail = 0;
		memcpy(
			this->_ArrayLocation + this->_QueueTail,
			&item,
			sizeof(item)
		);
		return true;
	}
	else {
		this->_QueueTail++;
		memcpy(
			this->_ArrayLocation + this->_QueueTail,
			&item,
			sizeof(item)
		);
	}
	
}

template<class _ElemType>
inline _ElemType circularQueue<_ElemType>::dequeue() noexcept
{


	_ElemType data = *(this->_ArrayLocation + this->_QueueHead);
	//this->_ArrayLocation + this->_QueueHead = 0;
	if (this->_QueueHead == this->_QueueTail)
	{
		this->_QueueHead = -1;
		this->_QueueTail = -1;
	}
	else if (this->_QueueHead == this->_ArraySize - 1)
		this->_QueueHead = 0;
	else
		this->_QueueHead++;

	return data;
}

template<class _ElemType>
inline _ElemType circularQueue<_ElemType>::operator[](size_t i) noexcept
{
	assert(this->_ArraySize != 0);
	assert(i < this->_ArraySize);

	if (this->_QueueHead - i < 0)
		i = this->_ArraySize - i;

	return *(this->_ArrayLocation + i);
}

#endif /*QUEUE_IMPL*/
