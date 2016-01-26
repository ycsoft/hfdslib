#ifndef C_HASH_H
#define C_HASH_H

#define MaxNodeCount        10000

typedef   char*   _key_type;
typedef   int     _value_type;

typedef  struct hash_node  hash_node;
typedef  struct c_map      c_map;
typedef  enum  _bool_t    _bool_t;

#define INVALID_VALUE       0x7fffffff

#ifdef __cplusplus
extern "C"{
#endif

enum _bool_t
{
    False = 0x00000000,
    True
};

struct hash_node
{
    _key_type    key;
    _value_type  value;

    hash_node    *next;
    _bool_t      inUse;
};

struct c_map
{
    uint32_t        _size;

    hash_node       *_store[MaxNodeCount];
    uint32_t         (*size)(c_map* mp);
    _value_type     (*get)(c_map* mp ,_key_type key);
    void            (*set)(c_map* mp , _key_type key, _value_type value);
    void            (*free)(c_map* mp);
    void            (*erase)(c_map *mp, _key_type key);
};

extern hash_node * __store[MaxNodeCount];
extern uint32_t    __size;

/*create and init new node*/
hash_node       *hash_node_new();

/* caculate hash value of key*/
uint32_t        hash_value( const char * key);
uint32_t        getsize(void);

hash_node       *_create(void);
_value_type     _get( _key_type key );
void            _set( _key_type key, _value_type value);
void            _erase(_key_type key);
void            _key_copy( _key_type dest, _key_type src);
void            _value_copy( _value_type *dest, _value_type *src);
void            _hash_free(void);

c_map           *map_create(void);
uint32_t        map_size(c_map *mp);
_value_type     map_get(c_map *mp,_key_type key);
void            map_set(c_map *mp,_key_type key, _value_type value);
void            map_erase(c_map *mp, _key_type key);
void            map_free(c_map *mp);



#ifdef __cplusplus
}
#endif

#endif // C_HASH_H
