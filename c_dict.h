#ifndef C_DICT_H
#define C_DICT_H


#ifdef __cplusplus
extern "C"{
#endif

#include <stddef.h>

#include "c_vector.h"
#include "cdef.h"

#define     XD_Dict     dict_t

#define     DICT_NODE_COUNT     9973

#define     REHS_STEP           3


#define     Dict_Hash(K, R)    \
            {\
              int  __x = (uint32_t)(ptrdiff_t)((XD_INT*)K)->_value;      \
              *R = (__x + (__x >> 3)) % DICT_NODE_COUNT; \
            }

#define     Dict_New()      (SP_Dict*)malloc(sizeof(SP_Dict))

#define     Dict_Init(D,KSZ,VSZ) \
{\
    int __i;\
    D->_count = 0;\
    D->_store   = (rb_node_t**)calloc(DICT_NODE_COUNT,sizeof(rb_node_t*));\
    D->_free                    =   Vector_New();\
    Vector_Create(int,D->_free,DICT_NODE_COUNT);\
    Vector_Push_back(int,D->_free,(ptrdiff_t)(D->_store));\
    for ( __i = 0 ; __i < DICT_NODE_COUNT; ++__i )\
    {\
    D->_store[__i]              = (rb_node_t*)calloc(1,sizeof(rb_node_t));\
    Vector_Push_back(int,D->_free,(ptrdiff_t)(D->_store[__i]));\
    D->_store[__i]->value       = calloc(1,VSZ);\
    D->_store[__i]->key         = calloc(1,KSZ);\
    D->_store[__i]->color       = RED;  \
    D->_capacity                = DICT_NODE_COUNT;\
    }\
}

#define     Dict_Enlarge(D,KSZ,VSZ) \
{\
    int __i,__count = D->_capacity * 3;\
    D->_store   = (rb_node_t**)realloc(D->_store,sizeof(rb_node_t*)*__count);\
    for ( __i = D->_capacity ; __i < __count; ++__i )\
    {\
    D->_store[__i]              = (rb_node_t*)calloc(1,sizeof(rb_node_t));\
    D->_store[__i]->value       = calloc(1,VSZ);\
    D->_store[__i]->key         = calloc(1,KSZ);\
    D->_store[__i]->parent      = NULL;    \
    D->_store[__i]->left        = NULL;  \
    D->_store[__i]->right       = NULL; \
    D->_store[__i]->color       = RED;  \
    D->_store[__i]->used        = 0;\
    D->_capacity                = __count;\
    }\
}


/*
 *
 *
T : Type
D : the dict to search in
K : the key
R : result, p2p,返回值
寻找空余节点，用于存储键值
*/
#define     _Dict_Search(D,K,R) \
{   \
    int (*compare)(void *arg1,void *arg2);\
    int KT = getType(K);\
    uint32_t  __ds_hv = 0, ds_i = 0,__finded = 0;\
    rb_node_t   *ds_nd,*ds_res = NULL;\
    Dict_Hash(K,&__ds_hv);\
    switch (KT) \
    {\
            case REAL:\
            case BOOL:\
            case INT:\
            case STRING:\
            {\
                compare = Default_Compare;break;\
            }\
            default:\
            {\
                compare = ((BaseType*)K)->compare;\
                break;\
            }\
    }\
    ds_nd = D->_store[__ds_hv];\
    if (!ds_nd->used||compare(ds_nd->key,K) == 0 )\
    { *R = ds_nd;\
    }\
    else{\
      _tree_search(ds_nd,K,compare,(rb_node_t**)NULL,&ds_res); \
      if ( ds_res ) { *R = ds_res;}  \
      else\
      {\
        for ( ds_i = __ds_hv+1; ds_i + REHS_STEP < D->_capacity; )    \
        {\
            if (!D->_store[ds_i]->used || compare(D->_store[ds_i]->key,K) == 0) \
            { *R = D->_store[ds_i];\
                __finded = 1;break; \
            }\
            ds_i += REHS_STEP;\
        }\
        if (!__finded){\
          for ( ds_i = 0 ; ds_i + REHS_STEP < __ds_hv;)\
          {if (!D->_store[ds_i]->used || compare(D->_store[ds_i]->key,K) == 0)\
                { *R = D->_store[ds_i];\
                  __finded = 1;break;} \
            ds_i += REHS_STEP;\
          } \
        }\
        if (!__finded) \
        {*R = NULL;\
        }\
      }\
    }   \
}

#define     Dict_Insert(D,K,V)    \
{\
    static int _I = 0; \
    uint32_t    di_hashval; \
    rb_node_t   *di_node,*_di_tmp; \
    Dict_Hash(K,&di_hashval); \
    _di_tmp = D->_store[di_hashval];\
    _Dict_Search(D,K,&di_node);\
   if ( di_node == NULL ) \
    { \
        di_node = (rb_node_t*)calloc(1,sizeof(rb_node_t)); \
        Tree_Node_Init(di_node,K,V);\
    } else\
        Node_Set(di_node,K,V);\
    Tree_Add_Node(di_node,&D->_store[di_hashval]);\
    di_node->used = 1; \
}

#define     Dict_Get(D,K,R) \
{\
    int _TP = getType(R);\
    rb_node_t   *dg_node = NULL  ;\
    _Dict_Search(D,K,&dg_node);\
    assert(dg_node != NULL);\
    switch(_TP)\
    {\
      case INT:\
        {\
            ((XD_INT*)R)->_value = ((XD_INT*)(dg_node->value))->_value;break;\
        }\
      case REAL:\
        {\
            ((XD_Real*)R)->_value = ((XD_Real*)(dg_node->value))->_value;break;\
        }\
      case STRING:\
        {\
            ((XD_String*)R)->_value = ((XD_String*)(dg_node->value))->_value;break;\
        }\
    }\
}
typedef struct dict_t    dict_t;
typedef struct dict_t    _dict_t;

struct dict_t
{
    uint32_t             _count;
    int32_t             (*keyCmp)(void *k1, void *k2);
    uint32_t            (*hash)(const void *key);
    void                (*set)(dict_t *dict,const key_type key,const value_type v );
    value_type          (*get)(dict_t *dict, key_type key);
    rb_node_t           **_store;
    uint32_t             _capacity;
    Vector              *_free;
};

uint32_t        _dict_hash_int(const int *k);
dict_t          *dict_create();
rb_node_t       *_dict_search(dict_t *dict, key_type key , uint32_t *hsh);
uint32_t        _dict_hash_int(const int *k);
int             _keyCmp(key_type *k1,key_type *k2);
void            dict_insert(dict_t *dict, const key_type key, const value_type v );
value_type      dict_get(dict_t *dict, key_type key);
void            dict_free(dict_t *dict);

int             _NUM_CMP(void*K1,void*K2);
int             _KEY_CMP(void* X1, void *X2, int len);


#ifdef __cplusplus
}
#endif

#endif // C_DICT_H
