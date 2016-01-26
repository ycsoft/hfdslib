
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <string.h>

#include "c_hash.h"

hash_node * __store[MaxNodeCount];
uint32_t    __size = 0;

hash_node * _create(void)
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
//    uint32_t seed = 131;

//    while ( *key )
//    {
//        hashval = hashval * seed + (*key++);
//    }
//    return (hashval & 0x7FFFFFFF)%MaxNodeCount;

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
    memset(node->key,0,32);
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
_value_type _get(_key_type key)
{
    uint32_t            hashval = hash_value(key);
    _value_type         res     = INVALID_VALUE;
    hash_node           *nd     = __store[hashval];

    while (nd->inUse && nd != NULL )
    {
        if ( strcmp(nd->key,key) == 0)
        {
            return nd->value;
        }
        nd = nd->next;
    }

    return res;
}
void _erase(_key_type key)
{
    uint32_t    hashval = hash_value(key);
    hash_node   *node = __store[ hashval ];

    while( node )
    {
        if( strcmp(node->key,key) == 0)
        {
            node->inUse = False;
            --__size;
            return;
        }
        node = node->next;
    }
}

void _set(_key_type key, _value_type value)
{
    uint32_t hash = hash_value(key);
    hash_node *cur = __store[hash],*nd = cur,*parent = nd,*save = NULL;
    while( nd != NULL )
    {
        parent = nd;
        if( nd->inUse )
        {
            if( strcmp(nd->key,key) == 0)
            {
                fprintf(stderr,"update...\n");
                nd->value = value;
                return;
            }

        }else
        {
            nd->inUse = True;
            _key_copy(nd->key,key);
            _value_copy(&nd->value,&value);
            __size++;
            return;
        }
        nd = nd->next;
    }

    fprintf(stderr,"allocate new node...\n");
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


c_map           *map_create(void)
{
    c_map *mp = (c_map*)malloc(sizeof(c_map));
    size_t i = 0;

    mp->_size = 0;
    for ( i = 0 ; i < MaxNodeCount; ++i)
    {
        hash_node *node = hash_node_new();
        mp->_store[i] = node;
    }

    mp->size = map_size;
    mp->get = map_get;
    mp->set = map_set;
    mp->erase = map_erase;
    mp->free = map_free;

}

uint32_t        map_size(c_map *mp)
{
    return  mp->_size;
}

_value_type     map_get(c_map *mp,_key_type key)
{
    uint32_t  hashval   = hash_value(key);
    hash_node *node     = mp->_store[hashval];
    _value_type value   = INVALID_VALUE;

    while( node )
    {
        /* found */
        if ( strcmp(node->key, key) == 0 )
        {
            return node->value;
        }else
        {
            node = node->next;
        }
    }

    return value;
}

void            map_set(c_map *mp,_key_type key, _value_type value)
{
    uint32_t       hashval = hash_value(key);
    hash_node      *node   = mp->_store[ hashval ],
                   *parent = NULL,
                   *save   = NULL;

    static          uint32_t  rp = 0;

    while ( node )
    {
        parent = node;
        if ( !node->inUse )
        {
            _key_copy(node->key,key);
            _value_copy(&node->value,&value);
            node->inUse = True;
            mp->_size ++;
            return;
        }else if ( strcmp(node->key,key) == 0 )
        {
            fprintf(stderr,"updating...\n");
            _value_copy(&node->value, &value);
            return;
        }else
        {
            node = node ->next;
        }
    }

    ++rp;
    fprintf(stderr,"repeat...times:%d\n",rp);

    save = hash_node_new();
    parent->next = save;
    save->inUse = True;
    _key_copy(save->key,key);
    _value_copy(&save->value,&value);
    mp->_size++;
}

void            map_free(c_map *mp)
{
    size_t i = 0 ;
    hash_node   *node = NULL,*next;

    for ( i = 0 ; i < MaxNodeCount; ++i)
    {
        node = mp->_store[i];
        while ( node )
        {
            next = node->next;
            free(node);
            node = NULL;
            node = next;
        }
    }
    free(mp);
}

void            map_erase(c_map *mp, _key_type key)
{
    uint32_t    hashval = hash_value(key);
    hash_node   *node = mp->_store[ hashval ];

    while ( node )
    {
        if ( strcmp(node->key,key) == 0 )
        {
            node->inUse = False;
            mp->_size--;
            node->value = INVALID_VALUE;
            return;
        }
        node = node->next;
    }
}
