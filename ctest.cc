
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <list>
#include <stdint.h>

#include "ctest.h"
#include "c_list.h"

void test_list()
{

    uint32_t  times = 10000000 , i = 0;
    c_list *list = list_init();
    clock_t start,end;

    std::list<c_list_node*>   clist;

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
        c_list_node *nd = list_node_new();
        clist.push_back(nd);
    }
    clist.clear();
    end = clock();


    fprintf(stdout,"c++ list Time Ellapsed:%d\n",end-start);

}
