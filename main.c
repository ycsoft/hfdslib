#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "c_list.h"
#include "c_hash.h"
#include "c_rb_tree.h"

#define times 100000

void test_list2(void)
{

    uint32_t         i = 0;
    c_list *list = list_init();
    c_map  *mp = map_create();
    clock_t start,end;
    char   *key[times];
    for ( i = 0 ; i < times; i++)
    {
        key[i] = (char*)malloc(sizeof(char)*32);
        sprintf(key[i],"%d",i);
    }

//    std::list<c_list_node*>   clist;

    start = clock();
    for ( i = 0 ; i < times; ++i)
    {
        c_list_node *nd = list_node_new();
        list_push_back(list,nd);
    }
    free(list);
    end = clock();


    fprintf(stdout,"c_list Time Ellapsed:%d\n",(end-start));

    start = clock();
    for ( i = 0 ; i < times; ++i)
    {
        mp->set(mp,key[i],i);
    }
    mp->free(mp);

    end = clock();
    fprintf(stdout,"c_hash Time Ellapsed:%d\n",end-start);


    for( i = 0 ; i < times; ++i)
        free(key[i]);

    start = clock();
    for ( i = 0 ; i < times; ++i)
    {
        key[i] = (char*)malloc(32);
    }
    end = clock();
    printf("malloc time:%d\n",end-start);

    start = clock();
    for ( i = 0 ; i < times; ++i)
    {
        sprintf(key[i],"Hello World");
    }
    end = clock();
    printf("sprintf time:%d\n",end-start);

    start = clock();
    for ( i = 0 ; i < times; ++i)
    {
        memcpy(key[i],"Hello World",32);
    }
    end = clock();
    printf("memcpy time:%d\n",end-start);

    for( i = 0 ; i < times; ++i)
        free(key[i]);

}


int main(void)
{
    test_list2();
    return 0;
}
