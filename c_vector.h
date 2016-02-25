#ifndef C_VECTOR_H
#define C_VECTOR_H

#ifdef __cplusplus
extern "C"
{
#endif
/////////////////////////////////////////////////////

#define vec_value_type  void*
#define Vector          hfvector

#define         Vector_New()    (phfvector)malloc(sizeof(hfvector))

#define         Vector_Create(Type,vec,sz)  \
    create_vector(vec,sizeof(Type),sz)

#define         Vector_Free(vec) \
                vector_free(vec)


#define         Vector_Push_back(Type,vec,v) \
    if ( (char*)vec->__inner_vec->_Ptr_First + vec->__inner_vec ->_size * vec->__inner_vec->_unit >= (char*)vec->__inner_vec->_Ptr_Last )\
    {\
        __extend(vec->__inner_vec,1);\
        assert(vec->__inner_vec!=NULL);\
    }\
    *(Type*)((char*)vec->__inner_vec->_Ptr_First + vec->__inner_vec ->_size * vec->__inner_vec->_unit)  = v;\
    ++(vec->__inner_vec->_size)

#define         Vector_Get(Type,vec,i)\
    *(Type*)((char*)vec->__inner_vec->_Ptr_First + i * vec->__inner_vec->_unit)

size_t _max_size(void);

typedef struct _vector
{
    vec_value_type  __store;
    vec_value_type _Ptr_First;
    vec_value_type _Ptr_Last;

    uint32_t        _size;
    uint32_t        _cap;
    uint32_t        _unit; //element size

}
c_vector,*pc_vector;

typedef struct _hfvector    hfvector,*phfvector;


struct _hfvector
{
    pc_vector              __inner_vec;

    void                  (*push_back)(phfvector vec, vec_value_type v);
    vec_value_type        (*get)(phfvector vec, int i);
    void                  (*free)(phfvector vec);
};

void                    *create_vector(phfvector vec,uint32_t unit,uint32_t size );
c_vector                *vector_init( uint32_t unit,uint32_t size );
void                    push_back(phfvector vec, vec_value_type v);
vec_value_type          vect_get( phfvector vec,int i);
void                    vector_free(phfvector vec);

void                    __extend( pc_vector vec, int sz);
size_t                  _Grow_to(pc_vector vec,size_t _Count);
/////////////////////////////////////////////////////



/////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#endif // C_VECTOR_H
