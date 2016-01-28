
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <string.h>

#include "c_hash.h"


static uint32_t dict_hash_function_seed;

hash_node *lookup(c_map *map, _key_type key)
{
    uint32_t  hashval = map->hash(key, strlen(key)) ;//hash_value(key);
    _bool_t   find = False;
    hash_node *node = map->_store[ hashval ],*parent = NULL;

//    printf("Key=%s\tKey Hash:%d\n",key,hashval);
    if ( ! node->_isUsing )
    {
        return node;
    }
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

//        printf("Repeat\n");
//        system("pause");
        node = hash_node_new();
        parent->next = node;
    }
    return node;
}

uint32_t hash_value(const char *key)
{
    uint32_t hashval = 5381;

    for ( hashval = 0; *key != '\0'; key++)
    {
        hashval +=  *key + 31 * hashval;
    }

    return hashval % MaxNodeCount;
}
uint32_t genHashValue_HF(const void *key, int len)
{
    uint32_t    hashval = dict_hash_function_seed;
    size_t      i       = 0;

    char *ptr = key;

    for ( i = 0 ; i < len; ++i)
    {
        if (*ptr == '\0')
            break;
        hashval = hashval  + 31 * hashval + *ptr++;
    }

    return hashval % MaxNodeCount;

}

uint32_t genHashValue_Redis(const void *key, int len)
{
    uint32_t seed = dict_hash_function_seed;
    const uint32_t m = 0x5bd1e995;
    const int r = 24;

    /* Initialize the hash to a 'random' value */
    uint32_t h = seed ^ len;

    /* Mix 4 bytes at a time into the hash */
    const unsigned char *data = (const unsigned char *)key;

    while(len >= 4) {
        uint32_t k = *(uint32_t*)data;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    /* Handle the last few bytes of the input array  */
    switch(len) {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0]; h *= m;
    };

    /* Do a few final mixes of the hash to ensure the last few
     * bytes are well-incorporated. */
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return (unsigned int)h%MaxNodeCount;
}

hash_node   *hash_node_new()
{
    hash_node *node = (hash_node*)malloc(sizeof(hash_node));

    memset(node,0,sizeof(hash_node));
    node->key = (_key_type)malloc(sizeof(char)*KEY_LEN);
    memset(node->key,0,KEY_LEN);
    node->value  = INVALID_VALUE;
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

    dict_hash_function_seed = rand()% 13131;

    mp->_size = 0;
    for ( i = 0 ; i < MaxNodeCount; ++i)
    {
        hash_node *node = hash_node_new();
        mp->_store[i] = node;
    }

    mp->hash = genHashValue_HF;
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

    if ( node->_isUsing )
    {
        return node->value;
    }
}

void            map_set(c_map *mp,_key_type key, _value_type value)
{

    hash_node *save = NULL;

    save = lookup(mp,key);

    save->value = value;
    save->_isUsing = True;
    _key_copy(save->key,key);
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

    if ( node->_isUsing )
    {
       node->_isUsing = False;
       memset(node->key,0,KEY_LEN);
    }

}
