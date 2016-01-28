#ifndef C_DICT_H
#define C_DICT_H


#ifdef __cplusplus
extern "C"{
#endif

#include "c_rb_tree.h"
#include "c_list.h"

#define     DICT_NODE_COUNT     3251

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
    c_list              *iterator;
};

uint32_t   _dict_hash_int(const int *k);

dict_t      *dict_create();
rb_node_t   *_dict_search(dict_t *dict, key_type key , uint32_t *hsh);
uint32_t    _dict_hash_int(const int *k);
int         _keyCmp(key_type *k1,key_type *k2);
void        dict_insert(dict_t *dict, const key_type key, const value_type v );
value_type  dict_get(dict_t *dict, key_type key);
void        dict_free(dict_t *dict);


#ifdef __cplusplus
}
#endif

#endif // C_DICT_H
