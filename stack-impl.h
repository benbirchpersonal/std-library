#ifndef	QUEUE_IMPL
#define	QUEUE_IMPL

#include "helpers.h"
#define DEFAULT_QUEUE_SIZE 100

_STDLIB_BEGIN
template <class _ElemType>
class queue : public arr<_ElemType, 0>
{
public:
	queue<_ElemType> ();

	bool						enqueue ( const _ElemType& item )			noexcept;
	_ElemType					dequeue ()									noexcept;
	_ElemType					operator[]( size_t i )						noexcept;
	void						rotate ()									noexcept;

	using		iterator = _ElemType*;
	_NODISCARD	iterator		begin ()									const noexcept
	{
		return _QueueTail;
	}
	_NODISCARD	iterator		end ()										const noexcept
	{
		return _QueueHead + 1;
	}

protected:


	_NODISCARD  void		realloc ();
	constexpr   bool 		reserve ( size_t newSize );

	_ElemType* _QueueHead;
	_ElemType* _QueueTail;

	_ElemType* _ArrayUpperBound;

	size_t _ArrayAllocatedSize;


public:

	// INITIALIZER LIST CONSTRUCTORS

	/*
		this constructor is activated if all variadic arguments are of the same type, and follow all rules which constitute an
		initizlier list.

		The queue differs from the other array structures as it is more fragile in its structure in memory, as it constantly
		moves when objects are added and removed to accomodate, so the size of the array is calculated first in the first pass
		to prevent issues and unexpected behaviour.
	*/

	template <typename... UList , REQUIRES ( nonrrow_convertible<_ElemType , UList...>::value )>		// template magic - see helpers.h
	queue ( UList&&... vs )
	{
		this->_ElemSize = sizeof ( _ElemType );
		this->_ArraySize = 0;
		this->_ArrayLocation = nullptr;
		process ( forward<UList> ( vs )... );			// determine size of initializer list

		this->_ArrayLocation = ( _ElemType* ) malloc ( sizeof ( _ElemType ) * this->_ArraySize * 2 );

		this->_ArrayUpperBound = this->_ArrayLocation + ( this->_ArraySize * 2 );

		this->_ArrayAllocatedSize = ( sizeof ( _ElemType ) * this->_ArraySize * 2 );

		this->_QueueHead = this->_ArrayLocation + ( ( this->_ArraySize * 2 ) / 2 );
		this->_QueueTail = _QueueHead;
		this->_ArraySize = 0;

		processSecondPass ( forward<UList> ( vs )... );	// copy initizlier list 
	}


private:
	/*
		recursively incraments arraySize.
	*/
	template <typename U , typename... UList>
	void process ( U&& v , UList&&... vs )
	{
		this->_ArraySize++;
		process ( forward<UList> ( vs )... );		// recursively call with forward to remove one item from initializer list
	}

	void process () {}		// empty recursive base case

	/*
		recursively copies elements into
	*/
	template <typename U , typename... UList>
	void processSecondPass ( U&& v , UList&&... vs )
	{
		auto x = forward<U> ( v );
		this->enqueue ( forward<U> ( v ) );

		processSecondPass ( forward<UList> ( vs )... );
	}
	void processSecondPass () {}
};


/*
	default constructor, creates empty queue with default size, and places head and tail of queue in the center of allocated memory
	to allow for growth.
*/
template<class _ElemType>
inline queue<_ElemType>::queue ()
{
	this->_ArrayLocation = ( _ElemType* ) malloc ( sizeof ( _ElemType ) * DEFAULT_QUEUE_SIZE );

	this->_ArrayUpperBound = this->_ArrayLocation + DEFAULT_QUEUE_SIZE;

	this->_ArraySize = 0;
	this->_ArrayAllocatedSize = DEFAULT_QUEUE_SIZE;

	this->_QueueHead = this->_ArrayLocation + ( DEFAULT_QUEUE_SIZE / 2 );
	this->_QueueTail = _QueueHead;

}

/*
	adds an item to the rear of the queue. returns false if failiure.
*/
template<class _ElemType>
inline bool queue<_ElemType>::enqueue ( const _ElemType& item ) noexcept
{
	if ( this->_ArraySize == 0 )
	{
		*this->_QueueTail = _ElemType ( item );
		this->_ArraySize = 1;
		return true;
	}


	if ( ( this->_QueueTail - 1 ) <= this->_ArrayLocation )
		realloc ();														// reallocate if not big enough to accomodate.

	this->_ArraySize++;
	this->_QueueTail--;
	*this->_QueueTail = _ElemType ( item );
	return true;

}

template<class _ElemType>
inline _ElemType queue<_ElemType>::dequeue () noexcept
{
	assert ( this->_ArraySize > 0 );
	this->_QueueHead--;
	this->_ArraySize--;
	return *( this->_QueueHead + 1 );
}

template<class _ElemType>
inline _ElemType queue<_ElemType>::operator[]( size_t i ) noexcept
{
	assert ( i < this->_ArraySize );
	return *( this->begin () + i );
}



/*
	Reallocates queue if too big for allocated space.
*/
template<class _ElemType>
inline void queue<_ElemType>::realloc ()
{
	if ( this->_ArraySize >= this->_ArrayAllocatedSize )
	{
		_ElemType* tempArrayLocation = ( _ElemType* ) malloc ( sizeof ( _ElemType ) * this->_ArrayAllocatedSize * 2 );
#ifdef DEBUG
		memset ( tempArrayLocation , 0 , sizeof ( _ElemType ) * this->_ArrayAllocatedSize * 2 );					// zeros memory for debug
#endif
		size_t centerDistanceFromTail = ( this->_ArrayLocation + ( this->_ArrayAllocatedSize / 2 ) ) - this->_QueueTail;

		memcpy_s (
			tempArrayLocation + this->_ArrayAllocatedSize - centerDistanceFromTail ,
			this->_ArraySize * sizeof ( _ElemType* ) ,
			this->_QueueTail ,
			this->_ArraySize * sizeof ( _ElemType* )
		);
		this->_ArrayAllocatedSize *= 2;
		this->_ArrayUpperBound = tempArrayLocation + ( this->_ArrayAllocatedSize );

		this->_QueueTail = tempArrayLocation + ( this->_ArrayAllocatedSize / 2 ) - centerDistanceFromTail;
		this->_QueueHead = this->_QueueTail + this->_ArraySize - 1;

		free ( this->_ArrayLocation );
		this->_ArrayLocation = tempArrayLocation;
	}

	else
	{
		_ElemType* tempArrayLocation = ( _ElemType* ) malloc ( sizeof ( _ElemType ) * this->_ArrayAllocatedSize );
#ifdef DEBUG
		memset ( tempArrayLocation , 0 , sizeof ( _ElemType ) * this->_ArrayAllocatedSize );						// zeros memory for debug
#endif
		size_t centerDistanceFromTail = ( this->_ArrayLocation + ( this->_ArrayAllocatedSize / 2 ) ) - this->_QueueTail;

		memcpy_s (
			tempArrayLocation + ( this->_ArrayAllocatedSize ) - centerDistanceFromTail ,
			this->_ArraySize * sizeof ( _ElemType* ) ,
			this->_QueueTail ,
			this->_ArraySize * sizeof ( _ElemType* )
		);

		this->_ArrayUpperBound = tempArrayLocation + ( this->_ArrayAllocatedSize );

		this->_QueueTail = tempArrayLocation + ( this->_ArrayAllocatedSize ) - centerDistanceFromTail;
		this->_QueueHead = this->_QueueTail + this->_ArraySize - 1;

		free ( this->_ArrayLocation );
		this->_ArrayLocation = tempArrayLocation;
	}


}
/*
	Performs rotation on data.
	e.g. 12345 rotated becomes 51234
							   ^----|
*/
template<class _ElemType>
inline void queue<_ElemType>::rotate () noexcept
{
	this->enqueue ( this->dequeue () );
}


/*
	reserves space for the queue. reccomended for user if size is known as it allows it to be calculated at compile time.
*/

template<class _ElemType>
inline constexpr bool queue<_ElemType>::reserve ( size_t newSize )
{
	assert ( newSize > this->_ArrayAllocatedSize );
	_ElemType* tempArrayLocation = ( _ElemType* ) malloc ( sizeof ( _ElemType ) * newSize );
#ifdef DEBUG
	memset ( tempArrayLocation , 0 , sizeof ( _ElemType ) * this->_ArrayAllocatedSize * 2 );
#endif
	size_t centerDistanceFromTail = ( this->_ArrayLocation + ( this->_ArrayAllocatedSize / 2 ) ) - this->_QueueTail;

	memcpy_s (
		tempArrayLocation + this->_ArrayAllocatedSize - centerDistanceFromTail ,
		this->_ArraySize * sizeof ( _ElemType* ) ,
		this->_QueueTail ,
		this->_ArraySize * sizeof ( _ElemType* )
	);
	this->_ArrayAllocatedSize = newSize;
	this->_ArrayUpperBound = tempArrayLocation + ( this->_ArrayAllocatedSize );

	this->_QueueTail = tempArrayLocation + ( this->_ArrayAllocatedSize / 2 ) - centerDistanceFromTail;
	this->_QueueHead = this->_QueueTail + this->_ArraySize - 1;

	free ( this->_ArrayLocation );
	this->_ArrayLocation = tempArrayLocation;
	return true;
}

_STDLIB_END
#endif /*QUEUE_IMPL*/
