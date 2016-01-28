
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "c_hash.h"
#include "c_list.h"


static uint32_t dict_hash_function_seed;


_bool_t keyCmp(const void *k1, const void *k2)
{
    return (strcmp(k1,k2) == 0);
}

uint32_t    rehash(const void * key)
{
    return 0;
}

//开放地址法
hash_node *__search(c_map *map, _key_type key , uint32_t *hsh)
{
    uint32_t hashval = map->hash(key);
    int     i = hashval + 1;
    hash_node *hsnd  = map->_store[hashval], *save = NULL ,*last = NULL;

    *hsh = hashval;
    if ( !hsnd->_isUsing || map->keyCmp(key,hsnd->key))
    {
        return hsnd;
    }

    last = hsnd;
    //从已存链表中查找是否已存在该关键字
    for ( ; last!= NULL && last->next != NULL; )
    {
        last = last->next;
        if ( map->keyCmp(key,last->key))
        {
            return last;
        }
    }
    ///////////////////////////////////////////////////////
    /// \brief printf
    ///关键字不存在，重新探测可用空节点
//    printf("Retry....");
    for ( ; i < MaxNodeCount; ++i )
    {
        if ( !map->_store[i]->_isUsing )
        {
            save = map->_store[i];
            last->next = save;
            return save;
        }
    }

    for ( i = 0; i < hashval; i++ )
    {
        if ( !map->_store[i]->_isUsing )
        {
            save = map->_store[i];
            last->next = save;
            return save;
        }
    }
    //必须扩展新节点
//    save = hash_node_new();
//    last->next = save;
    save = NULL;
    return save;

}

uint32_t   genHashValue_Custom(_key_type key)
{
    uint32_t res = 0;

    return res;
}

hash_node *lookup(c_map *map, _key_type key)
{
    uint32_t  hashval = map->hash(key) ;//hash_value(key);
    _bool_t   find = False;
    hash_node *node = map->_store[ hashval ],*parent = NULL;

    if ( ! node->_isUsing )
    {
        return node;
    }
    for ( ; node != NULL ; node = node ->next)
    {
        parent = node;
        if ( map->keyCmp(node->key,key) )
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

uint32_t __hash_value(const char *key)
{
    uint32_t hashval = 5381;

    for ( hashval = 0; *key != '\0'; key++)
    {
        hashval +=  *key + 31 * hashval;
    }

    return hashval % MaxNodeCount;
}
uint32_t        __rehash(c_map  *mp, int pos )
{

    return 0;
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
hash_node   *new_node(c_map *mp)
{
    hash_node *node = hash_node_new();
    struct memList *mem = (struct memList*)malloc(sizeof(struct memList));

    mem->data = node;
    mem->next = mp->__mem;
    mp->__mem = mem;
    return node;
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

    mp->__mem = (struct memList*)malloc(sizeof(struct memList));
    mp->__mem->data = NULL;
    mp->__mem->next = NULL;

    mp->allocate_node = new_node;

    dict_hash_function_seed = 131;

    mp->_size = 0;
    for ( i = 0 ; i < MaxNodeCount; ++i)
    {
        hash_node *node = mp->allocate_node(mp);
        mp->_store[i] = node;
    }


    mp->rehash = __rehash;
    mp->keyCmp = keyCmp;
    mp->hash = __hash_value;
    mp->size = map_size;
    mp->get = map_get;
    mp->set = map_set;
    mp->erase = map_erase;
    mp->free = map_free;


    return mp;
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
    uint32_t    hashval;

    save = __search(mp,key,&hashval);//lookup(mp,key);

    if (NULL == save)
    {
        save = mp->allocate_node(mp);
        save->next = mp->_store[hashval];
        mp->_store[hashval] = save;
    }
    save->value = value;
    save->_isUsing = True;
    _key_copy(save->key,key);
    mp->_size++;
}

void            map_free(c_map *mp)
{
    size_t i = 0 ;
    hash_node       *node;
    struct memList *mem = mp->__mem , *tmp = NULL;

    while ( mem )
    {
        node = mem->data;
        if ( node )
        {
//            printf("%d\tRelease Node:%s\n",i,node->key);
            free(node->key);
            free(mem->data);
            tmp = mem->next;
            free(mem);
            mem = tmp;
        }
        else
        {
            free(mem);
            break;
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
