#include "include.h"
#ifndef INITIALIZER_LIST_INCLUDED
#define INITIALIZER_LIST_INCLUDED




template<typename T>
struct identity
{
	typedef T type;
};

template<typename T>
T&& forward ( typename identity<T>::type& param )
{
	return static_cast<T&&>( param );
}

struct false_type
{
	static constexpr bool value = false;
	constexpr operator bool () const noexcept { return value; }
};
struct true_type
{
	static constexpr bool value = true;
	constexpr operator bool () const noexcept { return value; }
};

template<class T , class U>
struct is_same : false_type {};

template<class T>
struct is_same<T , T> : true_type {};

template <bool , typename T = void>
struct enable_if
{};

template <typename T>
struct enable_if<true , T>
{
	typedef T type;
};



template<class T>
typename T&& declval () noexcept;


template <bool...> struct bool_sequence {};

template <bool... Bs>
using bool_and
= is_same<bool_sequence<Bs...> ,
	bool_sequence<( Bs || true )...>>;

template <typename T>
true_type create ( T v );


template <typename T , typename U>
decltype( create<U> ( { declval<T> () } ) )
test_nonnarow_conv ( int );

template <typename T , typename U>
false_type test_nonnarow_conv ( long );


template <typename T , typename U>
using is_nonarrow_convertible
= decltype( test_nonnarow_conv<T , U> ( 0 ) );


template <typename T , typename... Ts>
using nonarrow_convertible
= bool_and<is_nonarrow_convertible<Ts , T>::value...>;


# define REQUIRES(...)	typename enable_if<(__VA_ARGS__), bool>::type = true

template <typename T>
class initList
{
public:

	snd::dynamicArray<T> _List;

	template <typename... UList ,
		REQUIRES ( nonarrow_convertible<T , UList...>::value )>
		initList ( UList &&... vs ) //
	{
		_List.reserve ( sizeof...( vs ) );
		process ( forward<UList> ( vs )... );
	}
	template <typename U , typename... UList>
	void process ( U&& v , UList &&... vs )
	{
		_List.push ( forward<U> ( v ) );
		process ( forward<UList> ( vs )... );
	}
	void process () {}

	initList<T> (const initList<T>& copied)
	{
		this->_List = copied->_List;
	}



};





#endif // INITIALIZER_LIST_INCLUDED
