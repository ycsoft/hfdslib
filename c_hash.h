#ifndef C_HASH_H
#define C_HASH_H

#define MaxNodeCount        5

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
    uint32_t         (*size)(void);

    hash_node*      (*create)(void);
    _value_type     (*get)( _key_type key);
    void            (*set)( _key_type key, _value_type value);
    void            (*clear)(void);
};

extern hash_node * __store[MaxNodeCount];
extern uint32_t    __size;

hash_node   *hash_node_new();

uint32_t hash_value( const char * key);

hash_node       *create(void);
_value_type     get( _key_type key );
void            set( _key_type key, _value_type value);

uint32_t        getsize(void);

void            _key_copy( _key_type dest, _key_type src);
void            _value_copy( _value_type *dest, _value_type *src);

void            _hash_free(void);


#ifdef __cplusplus
}
#endif

#endif // C_HASH_H
