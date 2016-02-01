#ifndef CSTL_VECTOR_H
#define CSTL_VECTOR_H

#ifdef __cplusplus
extern "C"{

#endif

typedef struct _vector_t
{
    void            *__store;

    void            *_Ptr_First;
    void            *_Ptr_Last;

    uint32_t        _size;
    uint32_t        _cap;
    uint32_t        _unit;
}
_vector_t,STL_Vector,*PSTL_Vector;

#define    _Ptr_Move_Count(ptr,_unit,_count)   \
            ptr = ((char*)ptr + _unit * _count)

#define     __extend2(vec,sz)    \
    size_t  max = 0x3fffffff; \
    size_t  _Capacity = vec->_cap,_Count = vec->_cap+sz; \
    /*printf("Extend,cur:%d\n",vec->_size);\*/\
    _Capacity         = max - _Capacity / 2 < _Capacity \
        ? 0 : _Capacity + _Capacity / 2; /*group to _Capacity elements*/\
    if (_Capacity < _Count) \
        _Capacity = _Count; \
    vec->__store = realloc(vec->__store,_Capacity * vec->_unit);\
    vec->_Ptr_First = vec->__store; \
    _Ptr_Move_Count(vec->_Ptr_Last,vec->_unit,_Capacity); \
    vec->_cap = _Capacity;

#define     CreateVector(__pv,Type,size)  \
        memset(__pv,0,sizeof(STL_Vector));    \
        __pv->__store            = (void*)(Type*)malloc(sizeof(Type)*size);\
        __pv->_Ptr_First         = __pv->__store;   \
        __pv->_size              = 0;\
        _Ptr_Move_Count(__pv->_Ptr_Last,__pv->_unit,size);   \
        __pv->_unit              = sizeof(Type); \
        __pv->_cap = size;


#define s _max_size(void)   0x3fffffff

/*push an element to array*/
#define  vector_add(vec,v) \
if ( ((char*)vec->_Ptr_First + vec->_size * vec->_unit) > (char*)vec->_Ptr_Last ) \
{\
    __extend2(vec,1);\
}\
*((char*)vec->_Ptr_First + vec->_size * vec->_unit ) = v;\
++(vec->_size);



#define     vector_get(vec,i,val)       \
assert( val != NULL);               \
assert( i >= 0 && i < vec->_cap);  \
*val = (*((char*)vec->_Ptr_First + i*vec->_unit));

#ifdef __cplusplus
}
#endif

#endif // CSTL_VECTOR_H
