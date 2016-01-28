#ifndef C_HASH_H
#define C_HASH_H


#define MaxNodeCount        3251

#define Max_Rey             3

#define KEY_LEN             32

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
    _bool_t      _isUsing;
    hash_node    *next;
};
struct memList
{
    void *data;
    struct memList *next;
};

struct c_map
{
    uint32_t        _size;
    hash_node       *_store[MaxNodeCount];
    struct memList  *__mem;


    _bool_t         (*keyCmp)(const void* k1, const void *k2);
    hash_node       (*find_node)(c_map* mp);
    uint32_t        (*hash)(const void* key);
    uint32_t        (*rehash)(int pos);
    uint32_t         (*size)(c_map* mp);
    _value_type     (*get)(c_map* mp ,_key_type key);
    void            (*set)(c_map* mp , _key_type key, _value_type value);
    void            (*free)(c_map* mp);
    void            (*erase)(c_map *mp, _key_type key);

    hash_node*      (*allocate_node)(c_map* mp);


};

/*create and init new node*/
hash_node       *hash_node_new();

/* caculate hash value of key*/
uint32_t        __hash_value( const char * key);
uint32_t        __rehash(c_map *mp,int pos);
uint32_t        genHashValue_Redis(const void *key, int len);
uint32_t        genHashValue_HF(const void *key, int len);

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
