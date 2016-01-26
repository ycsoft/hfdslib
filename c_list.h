#ifndef C_LIST_H
#define C_LIST_H

typedef struct c_list_node c_list_node;
typedef struct c_list c_list;

#ifdef __cplusplus
extern "C"
{
#endif

struct c_list_node
{
    c_list_node *pre;
    c_list_node *next;
    void   *data;
};

struct c_list
{
    c_list_node     *head;
    c_list_node     *tail;
    uint32_t         size;
};

c_list_node*    list_node_new();

c_list*         list_init();
void            list_free(c_list *list);

void    list_push_back(c_list *list, c_list_node *nd);
void    list_push_front(c_list *list, c_list_node *nd);

void    list_erase_back(c_list *list);
void    list_erase_front(c_list *list);
void    list_erase(c_list *list, c_list_node *nd);

c_list_node *list_read_back(c_list *list);
c_list_node *list_read_front(c_list *list);


#ifdef __cplusplus
}
#endif

#endif // C_LIST_H
