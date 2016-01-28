
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "c_list.h"
#include "string.h"

c_list_node * list_node_new()
{
    c_list_node *nd = (c_list_node*)malloc(sizeof(c_list_node));

    if ( nd )
    {
        memset(nd,0,sizeof(c_list_node));
    }

    return nd;
}

c_list * list_init()
{
    c_list *list = (c_list*)malloc(sizeof(c_list));

    c_list_node *head = list_node_new(),
                *tail = list_node_new();


    assert(list != NULL );
    assert(head != NULL );
    assert(tail != NULL );

    memset(list,0,sizeof(c_list));

    list->head = head;
    list->tail = tail;

    list->head->next = list->tail;
    list->tail ->pre = list->head;

    return list;
}
void list_free(c_list *list)
{
    c_list_node *nd = list->head,*next;

    assert(list != NULL );

    while(nd)
    {
        next = nd->next;
        free(nd);
        nd = next;
    }
    free(list);

}

void list_push_back(c_list *list, c_list_node *nd)
{

    assert(nd != NULL);
    assert(list != NULL);

    list->tail->pre ->next = nd;
    nd->next = list->tail;
    nd->pre = list->tail->pre;
    list->tail->pre = nd;
    list->size++;
}

void list_push_front(c_list *list, c_list_node *nd)
{

   assert(list != NULL);
   assert(nd != NULL);

   list->head->next ->pre = nd;

   nd->next = list->head->next;
   nd->pre = list->head;
}

c_list_node *list_read_back(c_list *list)
{
    assert(list);
    return list->tail->pre;
}

c_list_node *list_read_front(c_list *list)
{
    assert(list);
    return list->head->next;
}

void list_erase_back(c_list *list)
{
    c_list_node *nd = list->tail->pre;

    list->tail ->pre = nd->pre;
    nd->pre ->next = list->tail;

    free(nd);
    nd = NULL;
}
void list_erase_front(c_list *list)
{
    c_list_node *nd = list->head->next;

    list->head->next = nd->next;
    nd->next ->pre = list->head;

    free(nd);
    nd = NULL;
}

void list_erase(c_list *list, c_list_node *nd)
{
    c_list_node *cur = list->head->next;

    assert( nd != list->head && nd != list->tail );

    while ( cur )
    {
        if ( cur == nd )
        {
            cur->pre->next = cur->next;
            cur->next->pre = cur->pre;
            free(cur);
            break;
        }
        cur = cur->next;

    }

}
