
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "c_rb_tree.h"

rb_node_t * rb_node_new(key_type key, value_type value)
{
    rb_node_t *node = (rb_node_t*)malloc(sizeof(rb_node_t));

    node->key = key;
    node->value = value;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->color = RED;
    node->used = 0;

    return node;
}

void rb_node_free(rb_node_t *node)
{
    if ( node )
    {
        free(node);
        node = NULL;
    }
}

rb_node_t * rb_node_rotate_left(rb_node_t *node, rb_node_t **root)
{

    rb_node_t *y = node->right;

    //当前节点的右孩子 为y的左孩子
    if ( (node->right = y->left) )
    {
        y ->left ->parent = node;
    }
    y->left = node; //node 成为y的左孩子

    if( (y->parent = node->parent) )
    {
        if ( node == node->parent ->right)
        {
            node->parent->right = y;
        }else
        {
            node->parent->left = y;
        }
    }else //node节点为跟节点
    {
        *root = y;
    }
    node->parent = y;
    return *root;
}

rb_node_t * rb_node_rotate_right(rb_node_t *node, rb_node_t **root)
{

    rb_node_t * y = node->left;

    if ( (node->left = y->right))
    {
        y->right->parent = node;
    }

    y->right = node;

    if ( (y->parent = node->parent) )
    {
        if ( node == node->parent ->right )
        {
            node->parent ->right = y;
        }else
        {
            node->parent->left = y;
        }
    }else
    {
        *root = y;
    }

    node->parent = y;

    return *root;
}

rb_node_t * rb_search_auxiliary(rb_node_t *root, key_type key, rb_node_t **save)
{
    rb_node_t *parent = NULL,*node;
    int32_t   ret = 0;

    node = root;

    while ( node )
    {
        parent = node;
        ret = key - node->key;
        if ( ret > 0)
        {
            node = node->right;
        }else if( ret < 0)
        {
            node = node->left;
        }else
        {
            return node;
        }
    }

    if ( save )
    {
        *save = parent;
    }

    return NULL;
}

rb_node_t * rb_search(rb_node_t *root, key_type key)
{
    return rb_search_auxiliary(root,key,NULL);
}

rb_node_t * rb_insert_rebalance(rb_node_t *node, rb_node_t **root)
{
    rb_node_t *parent,*gparent,*uncle,*tmp;

    //父节点为红色时
    while ( (parent = node->parent) && parent->color == RED)
    {

        gparent = parent->parent;
        if( NULL == gparent )
        {
            break;
        }

        if ( parent == gparent->left) //当父节点为祖父节点的左孩子时
        {
            uncle = gparent ->right;

            //叔叔节点亦为红色
            if ( uncle && uncle ->color == RED )
            {
                uncle ->color = BLACK; //将叔叔节点着为黑色
                parent->color = BLACK; //父母着为黑色，
                gparent->color = RED;
                node = gparent;
            }else
            {
                //case 2: z的叔叔为黑色
                if ( parent ->right == node ) //z为父节点的右孩子
                {
                    *root = rb_node_rotate_left(parent,root);
                    tmp = parent;
                    parent = node;
                    node = tmp;
                }
                //Case 3:z的叔叔是黑色，此时z成为左孩子
                parent->color = BLACK;
                gparent->color = RED;
                *root = rb_node_rotate_right(gparent,root);
            }

        }else
        {
            uncle = gparent ->left;

            if ( uncle && uncle->color == RED)
            {
                uncle->color = BLACK;
                parent->color = BLACK;
                gparent->color = RED;
                node = gparent;
            }else //叔叔节点是黑色
            {
                if ( parent->left == node )
                {
                    *root = rb_node_rotate_right(parent,root);
                    tmp = parent;
                    parent = node;
                    node = tmp;
                }
                parent ->color = BLACK;
                gparent ->color = RED;
                *root = rb_node_rotate_left(gparent,root);
            }
        }
    }
    (*root) ->color = BLACK;
    return *root;
}
rb_node_t * rb_add_node( rb_node_t* adnode, rb_node_t **root)
{
    rb_node_t  *parent = NULL, *node = NULL;
    int32_t   ret = 0;

    if (( node = rb_search_auxiliary(*root,adnode->key,&parent)))
    {
        //found,cannot insert repeatly,so return
        return NULL;
    }

    adnode->color = RED;
    adnode->parent = parent;

    ret = adnode->key - parent->key;

    if ( parent )
    {
        if ( ret > 0 )
        {
            parent->right = adnode;
        }else if ( ret < 0 )
        {
            parent ->left = adnode;
        }
    }else
    {
        //空树
        *root = adnode;
    }

    return rb_insert_rebalance(adnode,root);
}

rb_node_t * rb_insert(const key_type key, const value_type value, rb_node_t **root)
{
    rb_node_t  *parent = NULL, *node = NULL;
    int32_t   ret = 0;

    if (( node = rb_search_auxiliary(*root,key,&parent)))
    {
        //found,cannot insert repeatly,so return
        return NULL;
    }

    node = rb_node_new(key,value);
    node->color = RED;
    node->parent = parent;

    ret = key - parent->key;

    if ( parent )
    {
        if ( ret > 0 )
        {
            parent->right = node;
        }else if ( ret < 0 )
        {
            parent ->left = node;
        }
    }else
    {
        //空树
        *root = node;
    }

    return rb_insert_rebalance(node,root);

}

rb_node_t * rb_erase_balance(rb_node_t *node, rb_node_t *parent, rb_node_t *root)
{
    rb_node_t  *other = NULL,   /*兄弟节点*/
               *o_left = NULL,  /*兄弟的左孩子*/
               *o_right = NULL; /*兄弟的右孩子*/
    while ((!node || node->color == BLACK) && node != root )
    {
        //当前节点是左孩子
        if ( parent->left == node )
        {
            other = parent->right;
            if ( other->color == RED )
            {
                other->color = BLACK;
                parent->color = RED;
                root = rb_node_rotate_left(parent,root);
                other = parent ->right;
            }
            //CASE 2
            if ( (!other->left || other->left->color == BLACK) &&
                 (!other->right || other->right->color == BLACK))
            {
                other->color = RED;
                node = parent;
                parent = node->parent;
            }else//CASE 3
            {
                if (!other->right || other->right->color == BLACK)
                {
                    if((o_left = other->left))
                    {
                        o_left->color = BLACK;
                    }
                    other->color = RED;
                    root = rb_node_rotate_right(other,root);
                    other = parent->right;
                }
                //case 4:
                other->color = parent->color;
                parent->color = BLACK;
                if ( other->right )
                {
                    other->right->color = BLACK;
                }
                root = rb_node_rotate_left(parent,root);
                node = root;
                break;
            }
        }
        else /*当前节点是右孩子*/
        {
            other = parent->left;
            if ( other->color == RED)
            {
                other->color = BLACK;
                parent->color = RED;
                root = rb_node_rotate_right(parent,root);
                other = parent->left;
            }
            if ((!other->left || other->left->color == BLACK) &&
                (!other->right || other->right->color == BLACK) )
            {
                other->color = RED;
                node = parent;
                parent = node->parent;
            }else
            {
                if (!other->left || other->left->color == BLACK)
                {
                    if ( (o_right = other->right))
                    {
                        o_right->color = BLACK;
                    }
                    other->color = RED;
                    root = rb_node_rotate_left(other,root);
                    other = parent->left;
                }
                other->color = parent->color;
                parent->color = BLACK;
                if ( other->left )
                {
                    other->left->color = BLACK;
                }
                root = rb_node_rotate_right(parent,root);
                node = root;
                break;
            }
        }
    }
    if ( node )
    {
        node ->color = BLACK;
    }
    return root;
}

rb_node_t * rb_erase(const key_type key, rb_node_t *root)
{
    rb_node_t *old,*child,*parent,*left,*node;
    COLOR      color;

    if ( !(node = rb_search_auxiliary(root,key,NULL)))
    {
        fprintf(stderr,"Cannot find node U want to delete");
        return root;
    }

    old = node;

    //删除的节点有双非空节点
    if ( node->left && node->left )
    {

        //使用该节点右子数的最小元素取代待删除元素
        node = node->right;
        while( (left = node->left) )
        {
            node = node->left;
        }
        child = node->right;
        parent = node->parent;
        color = node->color;

        //若有右孩子，向上一层移动
        if ( child)
        {
            child->parent = parent;
        }
        if ( parent )
        {
            if ( parent->left == node)
            {
                parent->left = child;
            }else
            {
                parent->right = child;
            }
        }else
        {
            root = child;
        }
        //取代删除节点的是该该节点的子节点
        if ( node->parent == old)
        {
            parent = node;
        }

        node->parent = old->parent;
        node->color = old->color;
        node->right = old->right;
        node->left = old->left;

        if( old->parent )
        {
            if( old->parent ->left == old)
            {
                old->parent->left = node;
            }else
            {
                old->parent->right = node;
            }
        }else
        {
            root = node;
        }

        old->left->parent = node;
        if ( old->right)
        {
            old->right->parent = node;
        }

    }else
    {
        if ( !node->left)
        {
            child = node->right;
        }else if ( !node->right )
        {
            child = node->left;
        }
        parent = node->parent;
        color = node->color;

        if ( child)
        {
            child ->parent = parent;
        }
        if ( parent )
        {
            if ( parent->left == node)
            {
                parent->left = child;
            }else
            {
                parent->right = child;
            }
        }else
        {
            root = child;
        }
    }
    free(old);
    if ( color == BLACK)
    {
        root = rb_erase_balance(child,parent,root);
    }
    return root;
}


void rb_free(rb_node_t *root)
{
    rb_node_t *parent = root, *left = NULL , * right = NULL ,*gparent;

    if ( parent == NULL )
    {
        return;
    }
    left = root->left;
    right = root->right;

    free(root);
    rb_free(left);
    rb_free(right);
}
