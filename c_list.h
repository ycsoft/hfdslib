#ifndef C_LIST_H
#define C_LIST_H

#define     LIST_INIT_SIZE      1000
#define     LIST_INC_SIZE       1000

typedef struct c_list_node c_list_node;
typedef struct c_list c_list;



#ifdef __cplusplus
extern "C"
{
#endif

#define     HF_List     c_list

#define     List_Create( Type ) \
            list_init(sizeof(Type))

#define     List_Free(list) \
            list_free(list)

#define     List_Push_Back(Type,list,v) \
           {\
                c_list_node *node = list_node_new(sizeof(Type)); \
                *(Type*)(node->data) = v; \
                _list_push_back(list,node);\
           }

#define     List_Push_Front(Type,list,v) \
           {\
                c_list_node *node = list_node_new(sizeof(Type)); \
                *(Type*)node->data = v; \
                _list_push_front(list,node);\
           }

#define     List_Erase_Back(list) \
            list_erase_back(list);

#define     List_Erase_Front(list) \
            list_erase_front(list);

#define     List_Erase(Type,list,v) \
{\
    c_list_node *cur = list->head->next;\
    assert( nd != list->head && nd != list->tail );\         \
    while ( cur )\
    {\
        if ( *(Type*)cur->data == *(Type*)nd->data )\
        {\
            cur->pre->next = cur->next;\
            cur->next->pre = cur->pre;\
            free(cur);\
            break;\
        }\
        cur = cur->next;\
        \
    }\
}

#define     List_Free(list) \
            list_free(list)

#define     List_Read_Front(Type,list) \
            *(Type*)(_list_read_front(list)->data)
#define     List_Read_Back(Type,list) \
            *(Type*)(_list_read_back(list)->data)

#define     List_Begin(list)  list->head->next
#define     List_End(list)    list->tail

struct c_list_node
{
    c_list_node *pre;
    c_list_node *next;
    void        *data;
};

struct c_list
{
    c_list_node     *head;
    c_list_node     *tail;
    c_list_node     *iterator;

    uint32_t         size;

};

c_list_node*    list_node_new(int unit);

c_list*         list_init(int unit);
void            list_free(c_list *list);

void    _list_push_back(c_list *list, c_list_node *nd);
void    _list_push_front(c_list *list, c_list_node *nd);

void    list_push_back (c_list *list, void *value, int unit);
void    list_push_front(c_list *list, void *value, int unit);

void    list_erase_back(c_list *list);
void    list_erase_front(c_list *list);
void    list_erase(c_list *list, c_list_node *nd);



c_list_node *_list_read_back(c_list *list);
c_list_node *_list_read_front(c_list *list);

void *  list_read_back(c_list *list);
void *  list_read_front(c_list *list);


#ifdef __cplusplus
}
#endif

#endif // C_LIST_H
