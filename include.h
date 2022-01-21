#pragma once
#include <cassert>
#include <memory>

#define _STDLIB_BEGIN namespace snd {
#define _STDLIB_END };

template <typename T>
class initList;


_STDLIB_BEGIN

class str;
typedef str string;

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



#include "array-impl.h"
#include "stack-impl.h"
#include "queue-impl.h"
#include "circular-queue-impl.h"
//#include "string-impl.h"
#include "initializer-list.h"
