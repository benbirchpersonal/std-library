#ifndef HELPERS_INCLUDED
#define HELPERS_INCLUDED

#include <memory>				// The only include in the project (hopefully)

#ifdef DEBUG
#define assert(EX) if(EX) printf("assertion failed");
#define assert(EX, ARG) if(EX) printf("%s", ARG);
#else
#define assert(EX) (void)(EX)
#define assert(EX, ARG) if(EX) printf("%s", ARG);
#endif


#define _STDLIB_BEGIN namespace snd {
#define _STDLIB_END };

// Forward declaration of classes.

_STDLIB_BEGIN

class str;

template<class _ElemType>
class arr;

template<class _ElemType>
class stack;

template<class _ElemType>
using dynamicArray = stack<_ElemType>;

template<class _ElemType>
using list = stack<_ElemType>;


template<class _ElemType>
class queue;

template<class _ElemType>
class circularQueue;


_STDLIB_END


// identity struct used to find type of object
template<typename T>
struct identity
{
	typedef T type;
};


// own implementation of std::forward
template<typename T>
T&& forward(typename identity<T>::type& param)
{
	return static_cast<T&&>(param);
}


// false type, templated alternative to the boolean value false
struct false_type
{
	static constexpr bool value = false;
	constexpr operator bool() const noexcept { return value; }
};

// true type, templated alternative to the boolean value true
struct true_type
{
	static constexpr bool value = true;
	constexpr operator bool() const noexcept { return value; }
};


// small template "function" which returns false_type if 2 objecs are not the same type.
template<class T, class U>
struct is_same : false_type {};



// small template "function" which returns true_type if 2 objecs are the same type.
template<class T>
struct is_same<T, T> : true_type {};


// my implementation of enable_if
template <bool, typename T = void>
struct enable_if
{};

template <typename T>
struct enable_if<true, T>
{
	typedef T type;
};


// my implementation of declval
template<class T>
typename T&& declval() noexcept;

// bool sequence data structure
template <bool...> struct bool_sequence {};

template <bool... Bs>
using bool_and
= is_same<bool_sequence<Bs...>,
	bool_sequence<(Bs || true)...>>;


template <typename T>
true_type create(T v);

// template magic for initializer list


template <typename T, typename U>
decltype(create<U>({ declval<T>() }))
test_nonnarow_conv(int);

template <typename T, typename U>
false_type test_nonnarow_conv(long);


template <typename T, typename U>
using is_nonarrow_convertible
= decltype(test_nonnarow_conv<T, U>(0));


template <typename T, typename... Ts>
using nonarrow_convertible
= bool_and<is_nonarrow_convertible<Ts, T>::value...>;

template<size_t, 0>
one_type create(size_t v);

template<size_t>
zero_type create(size_t v);



#define REQUIRES(...)	typename enable_if<(__VA_ARGS__), bool>::type = true





#endif // HELPERS_INCLUDED
