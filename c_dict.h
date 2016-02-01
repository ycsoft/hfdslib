#ifndef C_DICT_H
#define C_DICT_H


#ifdef __cplusplus
extern "C"{
#endif

#include <stddef.h>

#include "c_rb_tree.h"
#include "c_list.h"

#define     DICT_NODE_COUNT     3251

#define     Dict_Hash(K, R)    \
            {\
              uint32_t  x = (uint32_t)(ptrdiff_t)K;      \
              *R = (x + x >> 3) % DICT_NODE_COUNT; \
            }

#define     Dict_Create(KT,VT,D) \
{\
    size_t      i = 0;\
    memset(D,0,sizeof(dict_t));\
    for ( ; i < DICT_NODE_COUNT; ++i )\
    {\
        D->_store[i] = (rb_node_t*)malloc(sizeof(rb_node_t));\
        Tree_Node_Init(KT,VT,D->_store[i],INVALID_KEY,INVALID_VALUE);\
        D->_store[i]->used = 0;\
    }\
}

/*
 *
 *
T : Type
D : the dict to search in
K : the key
R : result, p2p
*/
#define     _Dict_Search( T, D , K, R ) \
{   \
    uint32_t  hashval = 0, i = 0,finded = 0;\
    rb_node_t   *nd,*res = NULL;\
    Dict_Hash(K,&hashval);\
    nd = D->_store[hashval];\
    if (*(T*)nd->key == K || !nd->used){ *R = nd;}\
    else{\
       /*search in current tree node*/     \
      _tree_search(T,nd,K,(rb_node_t**)NULL,&res); \
      if ( res ) { *R = res;}  \
      else{\
        for ( i = hashval+1; i < DICT_NODE_COUNT; ++i )    \
        {\
            if (!D->_store[i]->used) { *R = D->_store[i];finded = 1;break; }\
        }\
        if (!finded){\
          for ( i = 0 ; i < hashval; ++i){if (!D->_store[i]->used){ *R = D->_store[i];finded = 1;break;} } \
        }\
        if (!finded) *R = NULL;\
      }\
    }   \
}

#define     Dict_Insert(KT,VT,D,K,V)    \
{\
    uint32_t    hashval; \
    rb_node_t   *node; \
    printf("Key=%d\n",K);\
    Dict_Hash(K,&hashval); \
    _Dict_Search(KT,D,K,&node);\
   if ( node == NULL ) \
    { \
        node = (rb_node_t*)malloc(sizeof(rb_node_t)); \
        memset(node,0,sizeof(rb_node_t));\
        Tree_Node_Init(KT,VT,node,K,V);\
    } \
    *(KT*)node->key = K; \
    *(VT*)node->value = V; \
    node->used = 1; \
    Tree_Add_Node(KT,VT,node,&D->_store[hashval]);\
}

#define     Dict_Get(KT,VT,D,K,R) \
{\
    uint32_t    hashval;\
    rb_node_t   *dg_node  ;\
    Dict_Hash(K,&hashval);\
    _tree_search(KT,D->_store[hashval],K,(rb_node_t**)NULL,&dg_node);\
    assert(dg_node != NULL);\
    *R =    *(VT*)dg_node->value;\
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
    rb_node_t           *_store[ DICT_NODE_COUNT ];
};

uint32_t        _dict_hash_int(const int *k);
dict_t          *dict_create();
rb_node_t       *_dict_search(dict_t *dict, key_type key , uint32_t *hsh);
uint32_t        _dict_hash_int(const int *k);
int             _keyCmp(key_type *k1,key_type *k2);
void            dict_insert(dict_t *dict, const key_type key, const value_type v );
value_type      dict_get(dict_t *dict, key_type key);
void            dict_free(dict_t *dict);


#ifdef __cplusplus
}
#endif

#endif // C_DICT_H
