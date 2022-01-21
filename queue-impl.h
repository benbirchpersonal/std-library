#ifndef	QUEUE_IMPL
#define	QUEUE_IMPL

#include "include.h"
#define DEFAULT_QUEUE_SIZE 100

_STDLIB_BEGIN
template <class _ElemType>
class queue : public stack<_ElemType>
{
public:
	queue<_ElemType> ();
	queue<_ElemType> ( std::initializer_list<_ElemType> initList );

	bool		enqueue ( const _ElemType& item )				noexcept;
	_ElemType	dequeue ()									noexcept;
	_ElemType	operator[]( size_t i )						noexcept;

protected:


	_NODISCARD  void		realloc ();
	bool		reserve ( size_t newSize );

	_ElemType* _QueueHead;
	_ElemType* _QueueTail;

	_ElemType* _ArrayUpperBound;

	size_t _ArrayAllocatedSize;

};




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

template<class _ElemType>
inline queue<_ElemType>::queue ( std::initializer_list<_ElemType> initList )
{
	this->_ArrayLocation = ( _ElemType* ) malloc ( sizeof ( _ElemType ) * ( DEFAULT_QUEUE_SIZE > initList.size () ? DEFAULT_QUEUE_SIZE : initList.size () * 2 ) );

	this->_ArrayUpperBound = this->_ArrayLocation + ( DEFAULT_QUEUE_SIZE > initList.size () ? DEFAULT_QUEUE_SIZE : initList.size () * 2 );

	this->_ArraySize = 0;
	this->_ArrayAllocatedSize = ( DEFAULT_QUEUE_SIZE > initList.size () ? DEFAULT_QUEUE_SIZE : initList.size () * 2 );

	this->_QueueHead = this->_ArrayLocation + ( ( DEFAULT_QUEUE_SIZE > initList.size () ? DEFAULT_QUEUE_SIZE : initList.size () * 2 ) / 2 );
	this->_QueueTail = _QueueHead;

	for ( const _ElemType& x : initList )
	{
		this->enqueue ( x );
	}
}


template<class _ElemType>
inline bool queue<_ElemType>::enqueue ( const _ElemType& item ) noexcept
{
	if ( this->_ArraySize == 0 )
	{
		*this->_QueueTail = _ElemType ( item );
		this->_ArraySize = 1;
		//this->_QueueTail--;
		return true;
	}


	if ( ( this->_QueueTail - 1 ) <= this->_ArrayLocation )
		realloc ();

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
	//assert((this->_QueueHead - i) >= this->_ArrayLocation);
	return *( this->_QueueHead - i );
}

template<class _ElemType>
inline void queue<_ElemType>::realloc ()
{
	if ( this->_ArraySize >= this->_ArrayAllocatedSize )
	{
		_ElemType* tempArrayLocation = ( _ElemType* ) malloc ( sizeof ( _ElemType ) * this->_ArrayAllocatedSize * 2 );
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
		memset ( tempArrayLocation , 0 , sizeof ( _ElemType ) * this->_ArrayAllocatedSize );
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

template<class _ElemType>
inline bool queue<_ElemType>::reserve ( size_t newSize )
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
}


_STDLIB_END
#endif /*QUEUE_IMPL*/
