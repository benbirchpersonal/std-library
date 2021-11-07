#pragma once
#ifdef ARRAY
#include "array-impl.h"
#endif

#ifdef STRING
#include "string-impl.h"
#endif

#ifdef DYNAMIC_ARRAY
#include "dynamic-array.h"
#endif


/*
CONVENTIONS

class member function declarations:

	
KEYWORD		RETURN_TYPE		NAME	ARGS	KEYWORDS

e.g

_NODISCARD	size_t			count()			noexcept;
			void			test()			noexcept;

class member variable declarations:

TYPE		NAME;

e.g

size_t		size;


*/
