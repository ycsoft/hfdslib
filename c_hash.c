
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <string.h>

#include "c_hash.h"


hash_node *lookup(c_map *map, _key_type key)
{
    uint32_t  hashval = hash_value(key);

    _bool_t   find = False;

    hash_node *node = map->_store[ hashval ],*parent = NULL;

    if ( !node ->inUse )
        return node;

    for ( ; node != NULL ; node = node ->next)
    {
        parent = node;
        if ( strcmp(node->key,key) == 0)
        {
            find = True;
            return node;
        }
    }

    if (!find )
    {
        node = hash_node_new();
        parent->next = node;
    }
    return node;
}

uint32_t hash_value(const char *key)
{
    uint32_t hashval = 0;

    for ( hashval = 0; *key != '\0'; key++)
    {
        hashval +=  *key + 131 * hashval;
    }

    return hashval % MaxNodeCount;
}
hash_node   *hash_node_new()
{
    hash_node *node = (hash_node*)malloc(sizeof(hash_node));

    memset(node,0,sizeof(hash_node));
    node->key = (_key_type)malloc(sizeof(char)*KEY_LEN);
    memset(node->key,0,KEY_LEN);
    return node;
}

void   _key_copy( _key_type dest, _key_type src)
{
    memcpy(dest,src,KEY_LEN);
}
void    _value_copy( _value_type *dest, _value_type *src)
{
    *dest = *src;
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
    hash_node *node = lookup(mp,key);

    if ( node->inUse )
    {
        return node->value;
    }
}

void            map_set(c_map *mp,_key_type key, _value_type value)
{

    hash_node *save = NULL;

    save = lookup(mp,key);

    save->value = value;
    _key_copy(save->key,key);
    save->inUse = True;

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
    hash_node *node = lookup(mp,key);

    if ( node->inUse )
    {
       node->inUse = False;
       memset(node->key,0,KEY_LEN);
    }

}
