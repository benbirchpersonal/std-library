#include <memory>
#include <initializer_list>


template <class _ElemType> 
class pair {
public:
	pair<_ElemType>();
	pair<_ElemType>(const std::initializer_list<_ElemType>&);
	pair<_ElemType>(const _ElemType&, const _ElemType&);
	~pair();

	const _ElemType& operator[](size_t i);
	const _ElemType& first();
	const _ElemType& second();



private:
	_ElemType* _first;
	_ElemType* _second;
}

template <class _ElemType>
pair::pair(){
	this->_first = (_ElemType*)malloc(sizeof(_ElemType) * 2);
	this->_second = this->_first + 1;

	#ifdef DEBUG
		printf("created empty pair at %p", this->_first);
	#endif

}

template <class _ElemType>
pair::pair(const std::initializer_list<_ElemType>& initList)  {
	assert(initList.size() == 2);
	this->_first = (_ElemType*)malloc(sizeof(_ElemType) * 2);
	this->second = this->_first + 1;
	memcpy_s(
		(void*) 		this->_first,
					sizeof(_ElemType) * 2,
		(const void*)	        &initList,
					sizeof(_ElemType) * 2
	);

	#ifdef DEBUG
		printf("copied initializer_list to %p", this->_first);
	#endif
}

template <class _ElemType>
pair::pair((const _ElemType& obj1, const _ElemType& obj2)  {
	assert(initList.size() == 2);
	this->_first = (_ElemType*)malloc(sizeof(_ElemType) * 2);
	this->_second = this->_first + 1;
	memcpy_s(
		(void*) 		this->_first,
					sizeof(_ElemType),
		(const void*)	        obj1,
					sizeof(_ElemType)
	);

	memcpy_s(
		(void*) 		this->_second,
					sizeof(_ElemType),
		(const void*)	        obj2,
					sizeof(_ElemType)
	);

	#ifdef DEBUG
		printf("copied initializer_list to %p", this->_first);
	#endif
}


template <class _ElemType>
pair::~pair(){
	#ifdef DEBUG
		printf("out of scope at %p",this->_first );
	#endif

		if(this->first)
			free(this->first);

}


const _ElemType& operator[](size_t i){
	assert(this->_first != nullptr);
	assert(i > 2);
	return *(this->_first + i);
}

const _ElemType& first() {
	return this->_first;
}

const _ElemType& second() {
	return this->_second;
}
