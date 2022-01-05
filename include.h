#pragma once
#ifndef INCLUDED
#define INCLUDED
#include <cassert>
#include <memory>

class str;
typedef str string;

template<class _ElemType>
class arr;

template<class _ElemType>
class stack;

template<class _ElemType>
using dynamicArray = stack<_ElemType>

template<class _ElemType>
using list = stack<_ElemType>


template<class _ElemType>
class queue;

template<class _ElemType>
class circularQueue;

#include "array-impl.h"
#include "stack-impl.h"
#include "queue-impl.h"
#include "circular-queue-impl.h"
#include "string-impl.h"



#endif
