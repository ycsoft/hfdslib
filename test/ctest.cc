
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <list>
#include <stdint.h>

#include <CUnit.h>
#include <Basic.h>

#include "c_hash.h"
#include "ctest.h"
#include "c_list.h"

void test_list(void)
{

    const uint32_t  times = 100000 ;
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

void test_init(void)
{
    c_list *list = list_init();

    CU_ASSERT(list != NULL);
    CU_ASSERT( list->size == 0);

    free(list);
}

void test_hash(void)
{
    c_map  *map = map_create();

    map->set(map,"1",1);
    map->set(map,"2",2);
    map->set(map,"3",3);
    map->set(map,"4",4);
    map->set(map,"5",5);
    map->set(map,"6",6);
    map->set(map,"7",7);

    CU_ASSERT( map->size(map) == 7);
    CU_ASSERT( map->get(map,"1") == 1);
    CU_ASSERT( map->get(map,"2") == 2);
    CU_ASSERT( map->get(map,"3") == 3);
    CU_ASSERT( map->get(map,"4") == 4);
    CU_ASSERT( map->get(map,"5") == 5);
    CU_ASSERT( map->get(map,"6") == 6);
    CU_ASSERT( map->get(map,"7") == 7);

    map->erase(map,"6");
    CU_ASSERT(map->get(map,"6") == INVALID_VALUE);

    CU_ASSERT(map->size(map) == 6);

    map->free(map);
}

void test_push_back(void)
{
    c_list *list = list_init();

    c_list_node *n1 = list_node_new(),
                *n2 = list_node_new(),
                *n3 = list_node_new();

    CU_ASSERT( list != NULL );

    list_push_back(list,n1);
    list_push_back(list,n2);
    list_push_back(list,n3);

    CU_ASSERT( list->size == 3 );
    CU_ASSERT( list->tail->pre == n3);
    CU_ASSERT( list->head->next == n1);

    list_free(list);
}


void run_test(void)
{
    int ret;

    CU_BasicRunMode mode = CU_BRM_VERBOSE;
    CU_ErrorAction  erract = CUEA_IGNORE;
    CU_ErrorCode    err;


    CU_TestInfo tests[] =
    {
        {"test_init",test_init},
        {"test_push_back",test_push_back},
        {"test_hash",test_hash},
        CU_TEST_INFO_NULL
    };

    CU_SuiteInfo suits[] =
    {
        {"suit_1",NULL,NULL,NULL,NULL,tests},
        CU_SUITE_INFO_NULL
    };

    if ( CUE_SUCCESS != CU_initialize_registry())
    {
        fprintf(stderr,"Test Error\n");
        return;
    }

    err = CU_register_suites(suits);
    if( CUE_SUCCESS != err)
    {
        fprintf(stderr,"Test ERROR\n");
        return;
    }

    CU_basic_set_mode(mode);
    CU_set_error_action(erract);

    ret = CU_basic_run_tests();

    fprintf(stderr,"Test Complete: Return: %d\n",ret);
}


