#pragma once
#define STRING
#define ARRAY
#define DYNAMIC_ARRAY

#ifdef ARRAY
#include "array-impl.h"
#endif

#ifdef DYNAMIC_ARRAY
#include "dynamic-array.h"
#endif

#ifdef STRING
#include "string-impl.h"
#endif
