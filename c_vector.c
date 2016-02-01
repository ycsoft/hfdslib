#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "c_vector.h"

size_t _max_size(void)
{
    return 0x3fffffff/*1073741823*/;
}



size_t _Grow_to(pc_vector vec,size_t _Count)
{	// grow by 50% or at least to _Count
    size_t _Capacity = vec->_cap;

    _Capacity = _max_size() - _Capacity / 2 < _Capacity
        ? 0 : _Capacity + _Capacity / 2;	// try to grow by 50%
    if (_Capacity < _Count)
        _Capacity = _Count;
    return (_Capacity);
}
void  __extend( pc_vector vec, int sz)
{
    uint32_t _capacity = vec->_cap + sz,
             _size     = _Grow_to(vec,_capacity);

    vec->__store = realloc(vec->__store,(_size+1) * vec->_unit );
    vec->_Ptr_First = vec->__store;
    vec->_Ptr_Last = (char*)vec->__store + _size * vec->_unit;
    vec->_cap = _size;

}

c_vector    *vector_init(uint32_t unit,uint32_t size )
{
    c_vector    *_vec = (c_vector*)malloc(sizeof(c_vector));

    memset(_vec,0,sizeof(c_vector));

    assert(_vec != NULL);
    assert( size > 0 );

    _vec->__store = malloc( unit *size);

    _vec->_Ptr_First = _vec->__store;
    _vec->_Ptr_Last = (char*)_vec->_Ptr_First + size* unit;
    _vec->_cap = size;
    _vec->_size = 0;
    _vec->_unit = unit;
    return _vec;
}

void   push_back(phfvector vec, vec_value_type v)
{
//    if ( (char*)vec->__inner_vec->_Ptr_First + vec->__inner_vec ->_size * vec->__inner_vec->_unit >= vec->__inner_vec->_Ptr_Last )
//    {
//        __extend(vec->__inner_vec,1);
//    }
//    *((char*)vec->__inner_vec->_Ptr_First + vec->__inner_vec ->_size * vec->__inner_vec->_unit)  = *((void*)v);
//    ++(vec->__inner_vec->_size);
    //    int pos = vec->__inner_vec ->_size;
//    if ( (char*)vec->__inner_vec->_Ptr_First + pos * vec->__inner_vec->_unit >= vec->__inner_vec->_Ptr_Last )
//    {
//        __extend(vec->__inner_vec,1);
//    }
//    *((char*)vec->__inner_vec->_Ptr_First + pos)  = (*v);
//    ++(vec->__inner_vec->_size);
}

vec_value_type        vect_get( phfvector vec,int i)
{
    assert( i >= 0 && i < vec->__inner_vec->_cap);

    return *((char*)vec->__inner_vec->_Ptr_First + i);
}
void        vector_free(phfvector vec)
{
    free(vec->__inner_vec->__store);
    free(vec->__inner_vec);
}

void
*create_vector(phfvector vec,uint32_t unit,uint32_t size )
{
    vec->__inner_vec = vector_init(unit,size);

    vec->push_back = push_back;
    vec->get       = vect_get;
    vec->free      = vector_free;

}
