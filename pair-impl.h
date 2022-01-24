#ifndef PAIR_INCLUDED
#define PAIR_INCLUDED

#include "helpers.h"

_STDLIB_BEGIN
template <class _ElemType1, class _ElemType2> 
class pair {
public:
	pair();
	pair(const _ElemType1&, const _ElemType2&);
	pair(std::initializer_list<_ElemType1> initList);
	~pair();

	const void	 operator=(const pair<_ElemType1, _ElemType2>& copy);
	const _ElemType1& first();
	const _ElemType2& second();

	pair<_ElemType1, _ElemType2> swap() noexcept;



private:
	_ElemType1* _first;
	_ElemType2* _second;
};






template <class _ElemType1, class _ElemType2> 
pair<_ElemType1, _ElemType2>::pair(){
	this->_first = (_ElemType1*)malloc(sizeof(_ElemType1) + sizeof(_ElemType2));
	this->_second = (_ElemType2)(this->_first + 1);

	#ifdef DEBUG
		printf("created empty pair at %p", this->_first);
	#endif

}

template <class _ElemType1, class _ElemType2> 
pair<_ElemType1 ,_ElemType2>::pair(const _ElemType1& obj1, const _ElemType2& obj2)  {
	this->_first = (_ElemType1*)malloc(sizeof(_ElemType1) + sizeof(_ElemType2));
	this->_second = (_ElemType2*)(this->_first + 1);
	memcpy_s(
		(void*) 		this->_first,
					sizeof(_ElemType1),
		(const void*)	        &obj1,
					sizeof(_ElemType1)
	);

	memcpy_s(
		(void*) 		this->_second,
					sizeof(_ElemType2),
		(const void*)	        &obj2,
					sizeof(_ElemType2)
	);

	#ifdef DEBUG
		printf("copied initializer_list to %p", this->_first);
	#endif
}

template <class _ElemType1, class _ElemType2>
pair<_ElemType1, _ElemType2>::pair(std::initializer_list<_ElemType1> initList) {
	this->_first = (_ElemType1*)malloc(sizeof(_ElemType1) + sizeof(_ElemType2));
	this->_second = (_ElemType2*)(this->_first + 1);
	memcpy_s(
		(void*)this->_first,
		sizeof(_ElemType1),
		initList.begin(),
		sizeof(_ElemType1)
	);

	memcpy_s(
		(void*)this->_second,
		sizeof(_ElemType2),
		initList.end(),
		sizeof(_ElemType2)
	);

#ifdef DEBUG
	printf("copied initializer_list to %p", this->_first);
#endif
}





template <class _ElemType1, class _ElemType2> 
pair<_ElemType1, _ElemType2>::~pair(){
	#ifdef DEBUG
		printf("out of scope at %p",this->_first );
	#endif

}

template <class _ElemType1, class _ElemType2> 
const _ElemType1& pair<_ElemType1, _ElemType2>::first() {
	return *this->_first;
}
template <class _ElemType1, class _ElemType2> 
const _ElemType2& pair<_ElemType1, _ElemType2>::second() {
	return *this->_second;
}


template <class _ElemType1, class _ElemType2> 
const void pair<_ElemType1, _ElemType2>::operator=(const pair<_ElemType1, _ElemType2>& copy) {
	memcpy_s(
		this,
		sizeof(this),
		copy,
		sizeof(this)
	);
}




template <class _ElemType1, class _ElemType2> 
pair<_ElemType1, _ElemType2> pair<_ElemType1, _ElemType2>::swap() noexcept{
	_ElemType1* temp = (_ElemType1*) malloc(sizeof(_ElemType1));
	assert(this->_first != nullptr);
	assert(this->_second != nullptr);
	assert(typeid(_ElemType1) == typeid(_ElemType2));
	memcpy_s(
		temp, 
		sizeof(_ElemType1),
		this->_first,
		sizeof(_ElemType1)
	);
	
	memcpy_s(
		this->_first, 
		sizeof(_ElemType1),
		this->_second,
		sizeof(_ElemType1)
	);
	
	memcpy_s(
		this->_second, 
		sizeof(_ElemType1),
		temp,
		sizeof(_ElemType1)
	);

	return *this;

}

_STDLIB_END


#endif // PAIR_INCLUDED
