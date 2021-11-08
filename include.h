#pragma once

#include <cassert>
#include <memory>

class str;

template<class _ElemType>
class arr;

template<class _ElemType>
class stack;

template<class _ElemType>
class queue;


/*
CONVENTIONS

class member function declarations:

    
KEYWORD		RETURN_ElemTypeYPE		NAME	ARGS	KEYWORDS

e.g

_NODISCARD	size_t			count()			noexcept;
            void			test()			noexcept;

class member variable declarations:

TYPE		NAME;

e.g

size_t		size;


*/
