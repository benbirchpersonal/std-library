#ifndef	QUEUE_IMPL
#define	QUEUE_IMPL

#include "helpers.h"
#define DEFAULT_QUEUE_SIZE 100

_STDLIB_BEGIN
template <class _ElemType>
class queue : public arr<_ElemType>
{
public:
	queue<_ElemType>();

	bool		enqueue(const _ElemType& item)				noexcept;
	_ElemType	dequeue()									noexcept;
	_ElemType	operator[](size_t i)						noexcept;
	void		rotate()									noexcept;

	using		iterator = _ElemType*;
	_NODISCARD	iterator		begin()	const noexcept {
		return _QueueTail;
	}
	_NODISCARD	iterator		end()	const noexcept {
		return _QueueHead + 1;
	}

protected:


	_NODISCARD  void		realloc();
				bool		reserve(size_t newSize);

	_ElemType* _QueueHead;
	_ElemType* _QueueTail;

	_ElemType* _ArrayUpperBound;

	size_t _ArrayAllocatedSize;


public:			// INITIALIZER LIST CONSTRUCTORS

	template <typename... UList, REQUIRES(nonarrow_convertible<_ElemType, UList...>::value)>
	queue(UList &&... vs)
	{
		this->_ElemSize = sizeof(_ElemType);
		this->_ArraySize = 0;
		this->_ArrayLocation = nullptr;
		process(forward<UList>(vs)...);

		this->_ArrayLocation = (_ElemType*) malloc(sizeof(_ElemType) * this->_ArraySize * 2 );

		this->_ArrayUpperBound = this->_ArrayLocation + (this->_ArraySize * 2);

		this->_ArrayAllocatedSize = (sizeof(_ElemType) * this->_ArraySize * 2);

		this->_QueueHead = this->_ArrayLocation + ((this->_ArraySize * 2) / 2);
		this->_QueueTail = _QueueHead;
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

	void process(){}

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
inline queue<_ElemType>::queue()
{
	this->_ArrayLocation = (_ElemType*)malloc(sizeof(_ElemType) * DEFAULT_QUEUE_SIZE);

	this->_ArrayUpperBound = this->_ArrayLocation + DEFAULT_QUEUE_SIZE;

	this->_ArraySize = 0;
	this->_ArrayAllocatedSize = DEFAULT_QUEUE_SIZE;

	this->_QueueHead = this->_ArrayLocation + (DEFAULT_QUEUE_SIZE / 2);
	this->_QueueTail = _QueueHead;

}


template<class _ElemType>
inline bool queue<_ElemType>::enqueue(const _ElemType& item) noexcept
{
	if (this->_ArraySize == 0)
	{
		*this->_QueueTail = _ElemType(item);
		this->_ArraySize = 1;
		//this->_QueueTail--;
		return true;
	}


	if ((this->_QueueTail - 1) <= this->_ArrayLocation)
		realloc();

	this->_ArraySize++;
	this->_QueueTail--;
	/*
	memcpy_s(
		this->_QueueTail,
		this->_ElemSize,
		&item,
		this->_ElemSize
	);
	*/
	*this->_QueueTail = _ElemType(item);
	return true;

}

template<class _ElemType>
inline _ElemType queue<_ElemType>::dequeue() noexcept
{
	assert(this->_ArraySize > 0);
	this->_QueueHead--;
	this->_ArraySize--;
	return *(this->_QueueHead + 1);
}

template<class _ElemType>
inline _ElemType queue<_ElemType>::operator[](size_t i) noexcept
{
	assert(i < this->_ArraySize);
	return *(this->begin() + i);
}

template<class _ElemType>
inline void queue<_ElemType>::realloc()
{
	if (this->_ArraySize >= this->_ArrayAllocatedSize)
	{
		_ElemType* tempArrayLocation = (_ElemType*)malloc(sizeof(_ElemType) * this->_ArrayAllocatedSize * 2);
#ifdef DEBUG
		memset(tempArrayLocation, 0, sizeof(_ElemType) * this->_ArrayAllocatedSize * 2);
#endif
		size_t centerDistanceFromTail = (this->_ArrayLocation + (this->_ArrayAllocatedSize / 2)) - this->_QueueTail;

		memcpy_s(
			tempArrayLocation + this->_ArrayAllocatedSize - centerDistanceFromTail,
			this->_ArraySize * sizeof(_ElemType*),
			this->_QueueTail,
			this->_ArraySize * sizeof(_ElemType*)
		);
		this->_ArrayAllocatedSize *= 2;
		this->_ArrayUpperBound = tempArrayLocation + (this->_ArrayAllocatedSize);

		this->_QueueTail = tempArrayLocation + (this->_ArrayAllocatedSize / 2) - centerDistanceFromTail;
		this->_QueueHead = this->_QueueTail + this->_ArraySize - 1;

		free(this->_ArrayLocation);
		this->_ArrayLocation = tempArrayLocation;
	}

	else
	{
		_ElemType* tempArrayLocation = (_ElemType*)malloc(sizeof(_ElemType) * this->_ArrayAllocatedSize);
#ifdef DEBUG
		memset(tempArrayLocation, 0, sizeof(_ElemType) * this->_ArrayAllocatedSize);
#endif
		size_t centerDistanceFromTail = (this->_ArrayLocation + (this->_ArrayAllocatedSize / 2)) - this->_QueueTail;

		memcpy_s(
			tempArrayLocation + (this->_ArrayAllocatedSize) - centerDistanceFromTail,
			this->_ArraySize * sizeof(_ElemType*),
			this->_QueueTail,
			this->_ArraySize * sizeof(_ElemType*)
		);

		this->_ArrayUpperBound = tempArrayLocation + (this->_ArrayAllocatedSize);

		this->_QueueTail = tempArrayLocation + (this->_ArrayAllocatedSize) - centerDistanceFromTail;
		this->_QueueHead = this->_QueueTail + this->_ArraySize - 1;

		free(this->_ArrayLocation);
		this->_ArrayLocation = tempArrayLocation;
	}


}

template<class _ElemType>
inline void queue<_ElemType>::rotate() noexcept{
	this->enqueue(this->dequeue());
}

template<class _ElemType>
inline bool queue<_ElemType>::reserve(size_t newSize)
{
	assert(newSize > this->_ArrayAllocatedSize);
	_ElemType* tempArrayLocation = (_ElemType*)malloc(sizeof(_ElemType) * newSize);
#ifdef DEBUG
	memset(tempArrayLocation, 0, sizeof(_ElemType) * this->_ArrayAllocatedSize * 2);
#endif
	size_t centerDistanceFromTail = (this->_ArrayLocation + (this->_ArrayAllocatedSize / 2)) - this->_QueueTail;

	memcpy_s(
		tempArrayLocation + this->_ArrayAllocatedSize - centerDistanceFromTail,
		this->_ArraySize * sizeof(_ElemType*),
		this->_QueueTail,
		this->_ArraySize * sizeof(_ElemType*)
	);
	this->_ArrayAllocatedSize = newSize;
	this->_ArrayUpperBound = tempArrayLocation + (this->_ArrayAllocatedSize);

	this->_QueueTail = tempArrayLocation + (this->_ArrayAllocatedSize / 2) - centerDistanceFromTail;
	this->_QueueHead = this->_QueueTail + this->_ArraySize - 1;

	free(this->_ArrayLocation);
	this->_ArrayLocation = tempArrayLocation;
	return true;
}


_STDLIB_END
#endif /*QUEUE_IMPL*/
