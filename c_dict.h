#ifndef C_DICT_H
#define C_DICT_H


#ifdef __cplusplus
extern "C"{
#endif

#include <stddef.h>

#define     XD_Dict             dict_t
#define     Node                rb_node_t


#define     DICT_NODE_COUNT     9973
#define     REHS_STEP           3


#define     Dict_Hash(K, R)    \
            {\
              int  __x = (uint32_t)(ptrdiff_t)((XD_INT*)K)->_value;      \
              *R = (__x + (__x >> 3)) % DICT_NODE_COUNT; \
            }

#define     Dict_New()      (dict_t*)malloc(sizeof(dict_t))

#define     Dict_Init(D,KSZ,VSZ) \
{\
    int __i;\
    D->_count = 0;\
    D->_store   = (Node**)calloc(DICT_NODE_COUNT,sizeof(Node*));\
    D->_free                    =   Vector_New();\
    Vector_Create(Node*,D->_free,DICT_NODE_COUNT);\
    for ( __i = 0 ; __i < DICT_NODE_COUNT; ++__i )\
    {\
    D->_store[__i]              = (Node*)calloc(1,sizeof(Node));\
    Vector_Push_back(Node*,D->_free,D->_store[__i]);\
    D->_store[__i]->value       = calloc(1,VSZ);\
    D->_store[__i]->key         = calloc(1,KSZ);\
    D->_store[__i]->color       = RED;  \
    D->_capacity                = DICT_NODE_COUNT;\
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
    Node   *ds_nd,*ds_res = NULL;\
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
      _tree_search(ds_nd,K,compare,(Node**)NULL,&ds_res); \
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
    Node   *di_node,*_di_tmp; \
    Dict_Hash(K,&di_hashval); \
    _di_tmp = D->_store[di_hashval];\
    _Dict_Search(D,K,&di_node);\
   if ( di_node == NULL ) \
    { \
        di_node = (Node*)calloc(1,sizeof(Node)); \
        Vector_Push_back(Node*,D->_free,di_node);\
        Tree_Node_Init(di_node,K,V);\
    } else\
        Node_Set(di_node,K,V);\
    Tree_Add_Node(di_node,&D->_store[di_hashval]);\
    di_node->used = 1; \
}
#define     Dict_Free(D) \
    for ( int i = 0 ; i < D->_free->__inner_vec->_size; i++ )\
    {\
        Node *_nd = Vector_Get(Node*,D->_free,i);\
        free(_nd->key);free(_nd->value);\
        free(_nd);\
    }\
    Vector_Free(D->_free);free(D->_free);free(D->_store)
#define     Dict_Get(D,K,R) \
{\
    int _TP = getType(R);\
    Node   *dg_node = NULL  ;\
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
    Node           **_store;
    uint32_t             _capacity;
    Vector              *_free;
};

#ifdef __cplusplus
}
#endif

#endif // C_DICT_H
