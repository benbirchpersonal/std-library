#ifndef	CIRCULAR_QUEUE_IMPL
#define	CIRCULAR_QUEUE_IMPL

#include "helpers.h"
#define DEBUG
_STDLIB_BEGIN

template <class _ElemType>
class circularQueue : public arr<_ElemType>
{
public:
	circularQueue<_ElemType>(size_t queueSize);

	bool		enqueue(const _ElemType& item)				noexcept;
	_ElemType	dequeue()									noexcept;
	_ElemType	operator[](size_t i)						noexcept;
	void		rotate()									noexcept;



	using		iterator = _ElemType*;
	_NODISCARD	iterator		begin()	const noexcept {
		return this->_ArrayLocation + _QueueHead;
	}
	_NODISCARD	iterator		end()	const noexcept {
		return this->_ArrayLocation + _QueueTail + 1;
	}
public:


	_NODISCARD  void		realloc();
				bool		reserve(size_t newSize);

	int _QueueHead;
	int _QueueTail;



public:			// INITIALIZER LIST CONSTRUCTORS

	template <typename... UList, REQUIRES(nonarrow_convertible<_ElemType, UList...>::value)>
	circularQueue(UList &&... vs)
	{
		
		this->_QueueHead = -1;
		this->_QueueTail = -1;
		process(forward<UList>(vs)...);
		this->_ArrayLocation = (_ElemType*)malloc(sizeof(_ElemType) * this->_ArraySize * 2);
		this->_ArraySize = 0;

		processSecondPass(forward<UList>(vs)...);
	}


private:

	template <typename U, typename... UList>
	void process(U&& v, UList &&... vs)
	{
		this->_ArraySize++;
		process(forward<UList>(vs)...);
	}

	void process() {}

	template <typename U, typename... UList>
	void processSecondPass(U&& v, UList &&... vs)
	{
		auto x = forward<U>(v);
		this->enqueue(forward<U>(v));

		processSecondPass(forward<UList>(vs)...);
	}
	void processSecondPass() {}


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
inline bool circularQueue<_ElemType>::enqueue(const _ElemType& item) noexcept
{
	if (_QueueHead == _QueueTail && this->_ArraySize > 1)
		return false;

	else if (this->_QueueHead == -1)
	{
		this->_QueueHead = 0;
		this->_QueueTail = 0;
		memcpy(
			this->_ArrayLocation + this->_QueueTail,
			&item,
			sizeof(item)
		);
		this->_ArraySize++;
		return true;
	}

	else if ((this->_QueueTail == (this->_ArraySize - 1)) && (this->_QueueHead != 0))
	{
		this->_QueueTail = 0;
		memcpy(
			this->_ArrayLocation + this->_QueueTail,
			&item,
			sizeof(item)
		);
		this->_ArraySize++;
		return true;
	}
	else
	{
		this->_QueueTail++;
		memcpy(
			this->_ArrayLocation + this->_QueueTail,
			&item,
			sizeof(item)
		);
		this->_ArraySize++;
	}

}

template<class _ElemType>
inline void circularQueue<_ElemType>::rotate() noexcept{
	this->enqueue(this->dequeue());
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
	this->_ArraySize--;

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

_STDLIB_END

#endif /*QUEUE_IMPL*/
