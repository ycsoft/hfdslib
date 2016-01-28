
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <CUnit.h>
#include <Basic.h>
#include <map>
#include <list>

#include <boost/unordered_map.hpp>

#include "c_hash.h"
#include "ctest.h"
#include "c_list.h"
#include "c_rb_tree.h"
#include "c_dict.h"


#define times    10000
#define runtimes 100


void test_init(void)
{
    c_list *list = list_init();

    CU_ASSERT(list != NULL);
    CU_ASSERT( list->size == 0);

    free(list);
}
void test_clock(void)
{
    clock_t start, end;
    char    c[6] = "hello";
    int i , j ;

    start = clock();
    for( j = 0 ;j < runtimes; ++j)
    for ( i = 0 ; i < times; ++i)
    {
        clock();
    }
    end = clock();
    fprintf(stdout,"clock Time Ellapsed:%dms\n",end-start);
}
void test_rb_hash(void)
{
    int i = 0 , j = 0;
    clock_t start, end;
    dict_t  *dict = dict_create();

    start = clock();
    for( j = 0 ;j < runtimes; ++j)
    for ( i = 0 ; i < times; ++i)
    {
        dict->set(dict,i,j);
    }
    end = clock();
    fprintf(stdout,"HF_Map Time Ellapsed:%dms\n",end-start);
}

void base_rb_hash(void)
{
    int i = 0 , j = 0;


}

void test_hash(void)
{
    int i = 0 , j = 0;
    clock_t start, end;
    c_map   * map = map_create();

    char   *key[times];

    for ( i = 0 ; i < times; i++)
    {
        key[i] = (char*)malloc(sizeof(char)*32);
        sprintf(key[i],"%d",i);
    }

    start = clock();
    for( j = 0 ;j < runtimes; ++j)
    for ( i = 0 ; i < times; ++i)
    {
        map->set(map,key[i],i);
    }
    end = clock();
    fprintf(stdout,"HF_HashMap hash Time Ellapsed:%dms\n",end-start);
    map->free(map);

    for ( i = 0 ; i < times; i++)
    {
        free(key[i]);
    }
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
        {"HF_HashMap",test_hash},
        {"HF_Map",test_rb_hash},
        {"HF_List",test_list},
        {"Std::List",test_std_list},
        {"boost unorderd_map",test_boost_map},
        {"HF Tree",test_rb_tree},
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

void test_list(void)
{
        uint32_t         i = 0 , j = 0;
        c_list          *list = list_init();
        clock_t         start,end;
        const char*     pstr;

        start = clock();
        for ( j = 0 ; j < runtimes; ++j)
        for ( i = 0 ; i < times; ++i)
        {
            c_list_node *nd = list_node_new();
            list_push_back(list,nd);
        }
        end = clock();
        list_free(list);
        fprintf(stdout,"HF_list Time Ellapsed:%dms\n",(end-start));
}
void test_std_list(void)
{
    uint32_t         i = 0 , j = 0;
    std::list<int>   list;
    clock_t         start,end;
    start = clock();
    for ( j = 0 ; j < runtimes; ++j)
    for ( i = 0 ; i < times; ++i)
    {
        list.push_back(i);
    }
    end = clock();
    list.clear();

    fprintf(stdout,"std::list Time Ellapsed:%dms\n",(end-start));
}

void test_boost_map(void)
{
    int i = 0 , j = 0;
    clock_t start, end;
    boost::unordered_map<char*,int> boost_map;
    char   *key[times];

    for ( i = 0 ; i < times; i++)
    {
        key[i] = (char*)malloc(sizeof(char)*32);
        sprintf(key[i],"%dms",i);
    }


    start = clock();
    for( j = 0 ;j < runtimes; ++j)
    for ( i = 0 ; i < times; ++i)
    {
        boost_map.insert(std::make_pair(key[i],i));
    }
    end = clock();
    fprintf(stdout,"boost::unorderd_map Time Ellapsed:%dms\n",end-start);

    for ( i = 0 ; i < times; i++)
    {
        free(key[i]);
    }
}
void test_rb_tree(void)
{
    uint32_t         i = 0 , j = 0;
    rb_node_t       *rb = rb_node_new(0,0);
    clock_t         start,end;

    start = clock();
    for ( j = 0 ; j < runtimes; ++j)
    for ( i = 0 ; i < times; ++i)
    {
        rb_insert(i+1,i+1,&rb);
    }
    rb_free(rb);
    end = clock();

    fprintf(stdout,"HF_Tree Time Ellapsed:%dms\n",end-start);

}
