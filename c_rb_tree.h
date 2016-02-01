#ifndef C_RB_TREE_H
#define C_RB_TREE_H



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

#define         Tree_Node_Init(KT,VT,N,K,V)    \
{    N->key   = malloc(sizeof(KT));   \
    N->value = malloc(sizeof(VT));   \
    *(KT*)N->key = K;  \
    *(VT*)N->value = V;  \
    N->parent = NULL;    \
    N->left = NULL;  \
    N->right = NULL; \
    N->color = RED;  \
    N->used = 0;\
}

/**
root: pointer,root node
K: key
save : pointer to pointer, resutl's parent
res: pointer to pointer, result
**/
#define         _tree_search(KT,base,K,save,res)\
{\
    rb_node_t *pt = NULL,*nd;\
    int32_t   ret = 0;\
    nd = base;\
    printf("0x%x\n",nd);\
    while ( nd )  \
    {   \
        pt = nd;\
        printf("3 %d\n",K);\
        ret = K - ( *(KT*)nd->key );\
        printf("4\n");\
        printf("ret=%d\n",ret);\
        if ( ret > 0)\
        {\
            nd = nd->right;\
            *res = nd;\
        }else if( ret < 0)\
        {\
            nd = nd->left;\
            *res = nd;\
        }else\
        {\
            *res = nd;\
            break;\
        }\
    }\
    if ( save )\
    {\
        *save = pt;\
    }\
}

#define     Tree_Add_Node(KT,VT,ND,RT) \
{\
    rb_node_t  *parent = NULL, *nd = NULL,*root = (*RT);\
    rb_node_t  **pa = &parent,**pn = &nd;\
    int32_t   ret = 0;\
    printf("1\n");\
    _tree_search(KT,*RT,*(KT*)ND->key,pa,pn);    \
    printf("2\n");\
    if ( !node )\
    {\
    ND->color = RED;\
    ND->parent = parent;\
    if ( parent )\
    {\
        ret = *(KT*)ND->key - (*(KT*)root->key);\
        if ( ret > 0 )\
        {\
            parent->right = ND;\
        }else if ( ret < 0 )\
        {\
            parent->left = ND;\
        }\
    }else\
    {\
        *RT = ND;\
    }\
    printf("to balance\n");\
    rb_insert_rebalance(ND,RT);\
    }\
}
//root : pointer to pointer
#define     Tree_Insert(KT,VT,K,V,root)\
{\
    rb_node_t  *parent = NULL, *node = NULL;\
    int32_t   ret = 0;\
    _tree_search(KT,*root,K,&parent,&node);\
    printf("search ok\n");\
    if ( node )\
    {\
        *(KT*)node->key = K;\
        *(VT*)node->value = V;\
    }else{\
        node = (rb_node_t*)malloc(sizeof(rb_node_t));\
        memset(node,0,sizeof(rb_node_t));\
        node->key = malloc(sizeof(KT));\
        node ->value = malloc(sizeof(VT));\
        *(KT*)node->key = K;\
        *(VT*)node->value = V;\
        \
        node->color = RED;\
        node->parent = parent;\
        ret = K - (*(KT*)parent->key);\
        if ( parent )\
        {\
            if ( ret > 0 )\
            {\
                parent->right = node;\
            }else if ( ret < 0 )\
            {\
                parent ->left = node;\
            }\
        }else\
        {\
            *root = node;\
        }\
        rb_insert_rebalance(node,root);\
    }\
}


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
