#include <memory>
#include <initializer_list>


template <class _ElemType1, class _ElemType2> 
class pair {
public:
	pair<_ElemType>();
	pair<_ElemType>(const std::initializer_list<_ElemType1, _ElemType2>&);
	pair<_ElemType>(const _ElemType&, const _ElemType2&);
	~pair();
	
	const void	 operator=(const pair<_ElemType1, _ElemType2>& copy);
	const _ElemType1& first();
	const _ElemType2& second();
	
	void swap() noexcept;



private:
	_ElemType* _first;
	_ElemType* _second;
}

template <class _ElemType1, class _ElemType2> 
pair::pair(){
	this->_first = (_ElemType1*)malloc(sizeof(_ElemType1) + sizeof(_ElemType2));
	this->_second = (_ElemType2)(this->_first + 1);

	#ifdef DEBUG
		printf("created empty pair at %p", this->_first);
	#endif

}

template <class _ElemType1, class _ElemType2> 
pair::pair(const std::initializer_list<_ElemType1, _ElemType2>& initList)  {
	assert(initList.size() == 2);
	this->_first = (_ElemType1*)malloc(sizeof(_ElemType1) + sizeof(_ElemType2));
	this->second = this->_first + 1;
	memcpy_s(
		(void*) 		this->_first,
					sizeof(_ElemType1) + sizeof(_ElemType2),
		(const void*)	        &initList,
					sizeof(_ElemType1) + sizeof(_ElemType2)
	);

	#ifdef DEBUG
		printf("copied initializer_list to %p", this->_first);
	#endif
}

template <class _ElemType1, class _ElemType2> 
pair::pair((const _ElemType1& obj1, const _ElemType2& obj2)  {
	assert(initList.size() == 2);
	this->_first = (_ElemType1*)malloc(sizeof(_ElemType1) + sizeof(_ElemType2));
	this->_second = (_ElemType2*) (this->_first + 1;)
	memcpy_s(
		(void*) 		this->_first,
					sizeof(_ElemType1),
		(const void*)	        obj1,
					sizeof(_ElemType1)
	);

	memcpy_s(
		(void*) 		this->_second,
					sizeof(_ElemType2),
		(const void*)	        obj2,
					sizeof(_ElemType2)
	);

	#ifdef DEBUG
		printf("copied initializer_list to %p", this->_first);
	#endif
}

template <class _ElemType1, class _ElemType2> 
pair::~pair(){
	#ifdef DEBUG
		printf("out of scope at %p",this->_first );
	#endif

		if(this->first)
			free(this->first);

}

template <class _ElemType1, class _ElemType2> 
const _ElemType1& pair::first() {
	return this->_first;
}
template <class _ElemType1, class _ElemType2> 
const _ElemType2& pair::second() {
	return this->_second;
}


template <class _ElemType1, class _ElemType2> 
const void pair::operator=(const pair<_ElemType1, _ElemType2>& copy) {
	memcpy_s(
		this,
		sizeof(this),
		copy,
		sizeof(this)
	);
}




template <class _ElemType1, class _ElemType2> 
void pair::swap() {
	_ElemType1* temp = (_ElemType1*) malloc(sizeof(_ElemType1));
	assert(this->_first != nullptr);
	assert(this->_second != nullptr);
	assert(typeof(_ElemType1) == typeof(_ElemType2))
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

}
