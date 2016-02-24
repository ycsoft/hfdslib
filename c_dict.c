
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "c_rb_tree.h"
#include "c_list.h"
#include "c_dict.h"


uint32_t   _dict_hash_string(const char *key)
{
    uint32_t hashval = 5381;

    for ( hashval = 0; *key != '\0'; key++)
    {
        hashval +=  *key + 31 * hashval;
    }

    return hashval % DICT_NODE_COUNT;
}

uint32_t   _dict_hash_int(const int *k)
{
    return (*k) % DICT_NODE_COUNT;
}

int         _keyCmp(key_type *k1,key_type *k2)
{
    return 0;
}
int             _NUM_CMP(void*K1,void*K2)
{
    return *(int*)K1 - *(int*)K2;
}

int             _KEY_CMP(void* X1, void *X2, int len)
{
    int kcmp_i = 0,_cmp_res = 0;
    char _cmp[128] = {0};

    for ( ; kcmp_i < len; ++kcmp_i )
    {
        _cmp[kcmp_i] = (*((char*)X1+kcmp_i)) - (*((char*)X2+kcmp_i));
    }
    for ( kcmp_i = 0 ; kcmp_i < len; ++kcmp_i )
    {
        if ( (int)_cmp[kcmp_i] == 0 ) continue;
        _cmp_res = (int)_cmp[kcmp_i];
    }
    return _cmp_res;
}

dict_t  *dict_create()
{
    dict_t      *dict = (dict_t*)malloc(sizeof(dict_t));
    size_t      i = 0;

    memset(dict,0,sizeof(dict_t));
    assert( dict!=NULL );

    for ( ; i < DICT_NODE_COUNT; ++i )
    {
        dict->_store[i] = rb_node_new(INVALID_KEY,INVALID_VALUE);//(rb_node_t*)malloc(sizeof(rb_node_t));
        assert(dict->_store[i]);
        dict->_store[i]->used = 0;
    }
    dict->hash = _dict_hash_int;
    dict->keyCmp = _keyCmp;
    dict->set = dict_insert;
    dict->get = dict_get;
//    dict->iterator = rb_node_new(INVALID_KEY,INVALID_VALUE);

//    dict->iterator = list_init();
    return dict;
}

rb_node_t * _dict_search(dict_t *dict, key_type key , uint32_t *hsh)
{
    rb_node_t       *rbnode, *lastrb;
    uint32_t        hashval = dict->hash(&key);
    size_t          i = hashval+1;
    int             ret;

    *hsh = hashval;
    rbnode = dict->_store[hashval];
    if ( ! rbnode ->used  )
    {
        return rbnode;
    }
    if (dict->keyCmp(&key, &(rbnode->key)) == 0)
        return rbnode;
    /**check if key exists in the hash chain**/
    lastrb = rb_search(rbnode,key);
    if (lastrb != NULL)
        return lastrb;
    /**key not exists, find empty node to store it**/
    for ( ; i < DICT_NODE_COUNT; ++i)
    {
        if ( !dict->_store[i]->used )
        {
            lastrb = dict->_store[i];
            return rb_add_node(lastrb,&rbnode);
        }
    }
    /**here, we know that the table is full**/
    return NULL;
}

void dict_insert(dict_t *dict, const key_type key, const value_type v )
{
    uint32_t    hashval;
    rb_node_t   *node = _dict_search(dict,key,&hashval);

    if ( node == NULL )
    {
        node = rb_node_new(key,v);
    }
    node->key = key;
    node->value = v;
    node->used = 1;
    rb_add_node(node,&dict->_store[hashval]);
}

value_type  dict_get(dict_t *dict, key_type key)
{
    uint32_t    hashval;
    rb_node_t   *node = _dict_search(dict,key,&hashval);

    assert(node != NULL);

    return node->value;
}
void dict_free(dict_t *dict)
{
    int i = 0;
    rb_node_t   *root;

    for ( ; i < DICT_NODE_COUNT; ++i )
    {
        root = dict->_store[i];
        rb_free(root);
    }
}
