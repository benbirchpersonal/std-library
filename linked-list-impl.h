#include "include.h"

template <class _ElemType>
class node {
public:
        node(_ElemType& data);
        node();
        
public:
        _ElemType       data;
        node*           next;
       
}

template <class _ElemType>
node<_ElemType>::node(_ElemType& data){
	
}


template <class _ElemType>
class linkedList {
public:
        constexpr                            linkedList<_ElemType>()    noexcept;
        _NODISCARD      const _ElemType&     operator[](size_t index);
        
private:
        node<_ElemType>*      base;
        size_t                listSize;

private:
        _NODISCARD      size_t                traverseAndCount()        noexcept;

}


template<class _ElemType>
linkedList<_ElemType>::linkedList(){
        this->base = node
        
}


template<class _ElemType>
_NODISCARD size_t linkedList<_ElemType>::traverseAndCount(){
        node<_ElemType>* current           =       base;
        size_t           count             =       0;
        while(current->next != nullptr)
        {
                count++;
                current                    =       current->next;
        }
        return count;
}
template<class _ElemType>
_NODISCARD const _ElemType& linkedList<_ElemType>::operator[](size_t index){
        node<_ElemType>* current           =       base;
        for(int i = 0; i < index; i++){
                assert(current != nullptr);
                current                    =       current->next;
        }
        return *current;
} 
