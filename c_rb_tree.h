#ifndef C_RB_TREE_H
#define C_RB_TREE_H



typedef int key_type;
typedef int value_type;

typedef enum COLOR COLOR;

typedef struct rb_node_t  rb_node_t;

#define INVALID_KEY     0x7fffffff
#define INVALID_VALUE   0x7fffffff

#ifdef __cplusplus
extern "C"
{
#endif


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

    key_type    key;
    value_type  value;

    COLOR     color;
    int       used;
};

struct rb_tree
{
    rb_node_t *root;
    uint32_t   nodecount;
};

rb_node_t * rb_node_new(key_type key, value_type value);
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
