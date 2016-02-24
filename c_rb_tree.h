#ifndef C_RB_TREE_H
#define C_RB_TREE_H


#include "cdef.h"

typedef void* key_type;
typedef void* value_type;

typedef enum COLOR COLOR;

typedef struct rb_node_t  rb_node_t;

#define INVALID_KEY     0x7fffffff
#define INVALID_VALUE   0x7fffffff

#ifdef __cplusplus
extern "C"
{
#endif

#define         Tree_Node_Init(N,K,V)    \
{\
    int _KT = getType(K),_VT = getType(V);\
    int KSZ = ((BaseType*)K)->size + sizeof(BaseType), VSZ = ((BaseType*)V)->size + sizeof(BaseType);\
    N->key   = malloc(KSZ);   \
    N->value = malloc(VSZ);\
    assert(N->key!=NULL);assert(N->value!=NULL);\
    N->ksz = KSZ;\
    N->vsz = VSZ;\
    N->parent = NULL;    \
    N->left = NULL;  \
    N->right = NULL; \
    N->color = RED;  \
    N->used = 0;\
    switch( _KT){\
      case INT:\
      case REAL:\
      case BOOL:\
      case STRING:\
        {\
          Default_Copy(N->key,K);\
          break; \
        }\
    default:{((BaseType*)K)->copy(N->key,K);break;}\
    }\
    switch( _VT){\
      case INT:\
      case REAL:\
      case BOOL:\
      case STRING:\
        {\
          Default_Copy(N->value,V); \
          break;\
        }\
      default:{((BaseType*)V)->copy(N->value,V);break;}\
    }\
}

#define         Node_Set(N,K,V)    \
{\
    int _KT = getType(K),_VT = getType(V);\
    N->parent = NULL;    \
    N->left = NULL;  \
    N->right = NULL; \
    N->color = RED;  \
    N->used = 0;\
    switch( _KT){\
      case INT:\
      case REAL:\
      case BOOL:\
      case STRING:\
        {\
          Default_Copy(N->key,K);\
          break; \
        }\
    default:{((BaseType*)K)->copy(N->key,K);break;}\
    }\
    switch( _VT){\
      case INT:\
      case REAL:\
      case BOOL:\
      case STRING:\
        {\
          Default_Copy(N->value,V); \
          break;\
        }\
      default:{((BaseType*)V)->copy(N->value,V);break;}\
    }\
}


/**
root: pointer,root node
K: key
save : pointer to pointer, resutl's parent
res: pointer to pointer, result
**/
#define         _tree_search(R,K,CMP,SV,RS)\
{\
    rb_node_t *ts_pt = NULL,*ts_nd;\
    int        ret = 0;\
    ts_nd = R;\
    while ( ts_nd )  \
    {   \
        ts_pt = ts_nd;\
        ret = CMP(K,ts_nd->key);\
        if ( ret > 0)\
        {\
            ts_nd = ts_nd->right;\
            *RS = ts_nd;\
        }else if( ret < 0)\
        {\
            ts_nd = ts_nd->left;\
            *RS = ts_nd;\
        }else\
        {\
            *RS = ts_nd;\
            break;\
        }\
    }\
    if ( SV )\
    {\
        *SV = ts_pt;\
    }\
}

#define     Tree_Add_Node(ND,RT) \
{\
    rb_node_t  *ad_parent = NULL, *ad_nd = NULL,*ad_root = *RT;\
    int32_t   ret = 0;\
    int     (*compare)(void *a1,void *a2);\
    compare = Default_Compare;\
    _tree_search(*RT,ND->key,compare,&ad_parent,&ad_nd);    \
    if ( !ad_nd )\
    {\
    ND->color = RED;\
    ND->parent = ad_parent;\
    if ( ad_parent )\
    {\
        ret = compare(ND->key,ad_root->key);\
        if ( ret > 0 )\
        {\
            ad_parent->right = ND;\
        }else if ( ret < 0 )\
        {\
            ad_parent->left = ND;\
        }\
    }else\
    {\
        *RT = ND;\
    }\
    rb_insert_rebalance(ND,RT);\
    }\
}
//root : pointer to pointer
enum COLOR
{
    INIT    = 0x00000000,
    RED     = 0x00000001,
    BLACK   = 0x00000002
};



struct rb_node_t
{
    rb_node_t *left;  //left child
    rb_node_t *right; //right child
    rb_node_t *parent; //parent node

    void*       key;
    void*       value;

    int         ksz; //key size
    int         vsz; //value size

    int         (*_key_compare)(void* k1,void* k2);
    void        (*_key_copy)(void *dest, void *src);
    void        (*_value_copy)(void *dest, void* src);

    COLOR     color;
    int       used;

};

struct rb_tree
{
    rb_node_t *root;
    uint32_t   nodecount;
};


rb_node_t * rb_node_new(key_type key, value_type value);
rb_node_t * _rbnode_new(int ksz,int vsz, void *k,void*v);
void        rb_node_free(rb_node_t * node);

rb_node_t * rb_node_rotate_left( rb_node_t *node, rb_node_t **root);

rb_node_t * rb_node_rotate_right(rb_node_t *node, rb_node_t **root);

rb_node_t * rb_search_auxiliary(rb_node_t *root, key_type key, rb_node_t **save);

rb_node_t * rb_search(rb_node_t *root, key_type key);

rb_node_t * rb_insert_rebalance(rb_node_t *node, rb_node_t **root);
rb_node_t * rb_insert(const key_type key, const value_type value, rb_node_t **root);
rb_node_t * rb_add_node( rb_node_t* node, rb_node_t **root);


rb_node_t * rb_erase_balance(rb_node_t *node, rb_node_t *parent, rb_node_t *root);

rb_node_t * rb_erase(const key_type key, rb_node_t *root);

void        rb_free( rb_node_t *root);

#ifdef __cplusplus
}
#endif

#endif // C_RB_TREE_H
