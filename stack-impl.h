#ifndef	DYNAMIC_ARRAY_IMPL
#define	DYNAMIC_ARRAY_IMPL
#include "helpers.h"
#define	DEFAULT_ARRAYSIZE 100
_STDLIB_BEGIN

template	<class _ElemType>
class		stack : public arr<_ElemType, 0>
{
public:
	// constructors
	constexpr						stack<_ElemType> ()						noexcept;
	constexpr						stack<_ElemType> ( size_t reservedSpace )	noexcept;
	constexpr						stack ( stack<_ElemType>& copiedArr )		noexcept;

	// push/pop
	bool							push ( _ElemType item )					noexcept;
	_ElemType& pop ()														noexcept;
	constexpr bool					reserve ( size_t newSize );


private:
	_NODISCARD		bool			realloc ();


private:
	size_t		_ArrayAvailableSize;


public:			// INITIALIZER LIST CONTRUCTOR
	/*

	this constructor is activated if all variadic arguments are of the same type, and follow all rules which constitute an
	initizlier list.

	Because of the simplistic nature of the stack, this can safely be done with only 1 pass, differing from the other array types.
*/
	template <typename... UList , REQUIRES ( nonarrow_convertible<_ElemType , UList...>::value )>
	stack ( UList&&... vs )
	{
		this->_ElemSize = sizeof ( _ElemType );
		this->_ArraySize = 0;
		this->_ArrayLocation = nullptr;
		this->reserve ( sizeof...( vs ) );
		process ( forward<UList> ( vs )... );
	}

private:
	template <typename U , typename... UList>
	void process ( U&& v , UList&&... vs )
	{
		this->push ( forward<U> ( v ) );
		process ( forward<UList> ( vs )... );		// recursively push items onto the stack
	}
	void process () {}
};

/*
	creates empty stack with default size
*/
template<class _ElemType>
constexpr stack<_ElemType>::stack () noexcept
{
	this->_ArrayLocation = ( _ElemType* ) malloc ( sizeof ( _ElemType ) * DEFAULT_ARRAYSIZE );
	this->_ArraySize = 0;
	this->_ArrayAvailableSize = DEFAULT_ARRAYSIZE;
}


/*
	creates empty stack with predefined size.
*/
template<class _ElemType>
constexpr stack<_ElemType>::stack ( size_t elements ) noexcept
{
	this->_ArrayLocation = ( _ElemType* ) malloc ( sizeof ( _ElemType ) * elements );
	this->_ArraySize = 0;

}
/*
	copy constructor.
*/
template<class _ElemType>
constexpr  stack<_ElemType>::stack ( stack<_ElemType>& copiedArr ) noexcept
{
	this->_ArrayLocation = ( _ElemType* ) malloc ( sizeof ( _ElemType ) * copiedArr._ArraySize );
	this->_ArraySize = copiedArr._ArraySize;
	this->_ArrayAvailableSize = copiedArr._ArrayAvailableSize;
	rsize_t copySize = copiedArr._ArraySize;

	memcpy_s (
		this->_ArrayLocation ,
		copySize ,
		copiedArr._ArrayLocation ,
		copySize
	);
}
/*
	push operation on the stack, adds an element to the top of the array
*/
template<class _ElemType>
inline bool stack<_ElemType>::push ( _ElemType item ) noexcept
{
	assert ( this->_ArrayLocation != nullptr );

	if ( this->_ArraySize >= ( this->_ArrayAvailableSize - 1 ) )
		if ( !realloc () )
			return false;

	_ElemType* pushloc = ( this->_ArrayLocation ) + this->_ArraySize;
	*pushloc = _ElemType ( item );

	this->_ArraySize++;
	return true;
}
/*
	pop operation on the stack, removes the top item from the array
*/
template<class _ElemType>
inline _ElemType& stack<_ElemType>::pop () noexcept
{
	assert ( this->_ArrayLocation != nullptr );
	assert ( this->_Arraysize > 0 );				// empty stack check
	this->_ArraySize--;
	return ( _ElemType ) * ( this->_ArrayLocation + this->_ArraySize - 1 );
}

/*
	reserves space for the array. reccomended for user if size is known as it allows it to be calculated at compile time.
*/

template<class _ElemType>
inline constexpr bool stack<_ElemType>::reserve ( size_t newSize )
{
	_ElemType* newLocation = nullptr;
	newLocation = ( _ElemType* ) ( malloc ( sizeof ( _ElemType ) * newSize ) );

	if ( newLocation == nullptr )
		return false;

	memcpy_s (
		newLocation ,
		sizeof ( _ElemType ) * this->_ArraySize ,
		this->_ArrayLocation ,
		sizeof ( _ElemType ) * this->_ArraySize
	);

	free ( this->_ArrayLocation );
	this->_ArrayLocation = newLocation;
	this->_ArrayAvailableSize = newSize;
	return true;
}

/*
* Finds a new chunk of memory which the array can be placed in.
*/
template<class _ElemType>
_NODISCARD inline bool stack<_ElemType>::realloc ()
{
	_ElemType* newLocation = nullptr;
	newLocation = ( _ElemType* ) ( malloc ( sizeof ( _ElemType ) * this->_ArrayAvailableSize * 2 ) );

	if ( newLocation == nullptr )
		newLocation = ( _ElemType* ) ( malloc ( sizeof ( _ElemType ) * this->_ArrayAvailableSize + 1 ) );

	if ( newLocation == nullptr )
		return false;

	memcpy_s (
		newLocation ,
		sizeof ( _ElemType ) * this->_ArrayAvailableSize * 2 ,
		this->_ArrayLocation ,
		sizeof ( _ElemType ) * this->_ArraySize
	);

	free ( this->_ArrayLocation );
	this->_ArrayLocation = newLocation;
	this->_ArrayAvailableSize *= 2;
	return true;
}

_STDLIB_END
#endif /* !DYNAMIC_ARRAY_IMPL*/
