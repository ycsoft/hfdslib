#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "c_list.h"

#ifdef __cplusplus
extern "C"
{
#endif


void  ex_list(void)
{

    HF_List *list = List_Create(int);

    int v;


    List_Push_Back(int,list,1);
    List_Push_Back(int,list,2);
    List_Push_Back(int,list,3);
    list->iterator = List_Begin(list);
    while ( list->iterator != List_End(list))
    {
        printf("%d\n",*(int*)list->iterator->data);
        list->iterator = list->iterator->next;
    }

}
#ifdef __cplusplus
}
#endif
