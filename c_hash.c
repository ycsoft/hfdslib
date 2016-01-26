
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <string.h>

#include "c_hash.h"

hash_node * __store[MaxNodeCount];
uint32_t    __size = 0;

hash_node * create(void)
{
    size_t i = 0;


    for ( i = 0 ; i < MaxNodeCount; ++i)
    {
        hash_node *nd = hash_node_new();

        __store[i] = nd;
    }
    return __store;
}

uint32_t hash_value(const char *key)
{
    uint32_t hashval;

    for ( hashval = 0; *key != '\0'; key++)
    {
        hashval = *key + 31 * hashval;
    }

    return hashval % MaxNodeCount;
}
hash_node   *hash_node_new()
{
    hash_node *node = (hash_node*)malloc(sizeof(hash_node));
    node->key = (_key_type)malloc(sizeof(char)*32);
    node->next = NULL;
    node->inUse = False;
    node->value = 0;
    return node;
}

void   _key_copy( _key_type dest, _key_type src)
{
    strcpy(dest,src);
}
void    _value_copy( _value_type *dest, _value_type *src)
{
    *dest = *src;
}
_value_type get(_key_type key)
{
    uint32_t            hashval = hash_value(key);
    _value_type         res     = INVALID_VALUE;
    hash_node *nd = __store[hashval] , *save = NULL;

    while (nd->inUse && nd != NULL )
    {
        save = nd;
        if ( strcmp(nd->key,key) == 0)
        {
            return nd->value;
        }
        nd = nd->next;
    }

    return res;
}
void set(_key_type key, _value_type value)
{
    uint32_t hash = hash_value(key);
    hash_node *cur = __store[hash],*nd = cur,*parent = nd,*save = NULL;

    while( nd != NULL )
    {
        parent = nd;
        if( nd->inUse )
        {
            /* if key exists, modify its value*/
            if( strcmp(nd->key,key) == 0)
            {
                nd->value = value;
                return;
            }
        }else
        {
            nd->next = NULL;
            _key_copy(nd->key,key);
            _value_copy(&nd->value,&value);
            __size++;
            return;
        }
        nd = nd->next;
    }

    /* alloc new node to store the k-v */
    save = hash_node_new();
    parent->next = save;
    save->inUse = True;

    _key_copy(save->key,key);
    _value_copy(&save->value,&value);
    __size++;
}

uint32_t        getsize(void)
{
    return  __size;
}

void     _hash_free(void)
{
    size_t i = 0;
    for ( i = 0 ; i < MaxNodeCount; ++i)
    {
        free(__store[i]);
        __store[i] = NULL;
    }
}
