
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <CUnit.h>
#include <Basic.h>
#include <map>
#include <vector>
#include <list>

#include <boost/unordered_map.hpp>

#include "c_hash.h"
#include "ctest.h"
#include "c_list.h"
#include "c_rb_tree.h"
#include "c_dict.h"
#include "c_vector.h"
#include "cstl_vector.h"
#include "test/listclass.hpp"
#include "test/vectorclass.hpp"

#define times    100
#define runtimes 40

typedef struct _Test
{
    int i ;
    int j ;
}_Test;

void test_init(void)
{

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
{/*
    int i = 0 , j = 0;
    clock_t start, end;
    dict_t  *dict = dict_create();


    start = clock();
    for( j = 0 ;j < runtimes; ++j)
    {

    for ( i = 0 ; i < times; ++i)
    {
        dict->set(dict,i,j);
    }
    }
    end = clock();
    fprintf(stdout,"HF_Map Time Ellapsed:%dms\n",end-start);
    */
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
    {

        for ( i = 0 ; i < times; ++i)
        {
            map->set(map,key[i],i);
        }

    }
    map->free(map);
    end = clock();
    fprintf(stdout,"HF_HashMap hash Time Ellapsed:%dms\n",end-start);


    for ( i = 0 ; i < times; i++)
    {
        free(key[i]);
    }
}


void base_vector(void)
{
//    pc_vector   vec = vector_init(10);
//    int i = 0;

//    for ( ; i < 1000000; ++i )
//    {
//        push_back(vec,i);
//        CU_ASSERT(i == vect_get(vec,i));
//    }
}

void run_test(void)
{
    int ret;

    CU_BasicRunMode mode = CU_BRM_VERBOSE;
    CU_ErrorAction  erract = CUEA_IGNORE;
    CU_ErrorCode    err;


    CU_TestInfo tests[] =
    {
        {"base_vector",base_vector},
//        {"HF_HashMap",test_hash},
//        {"HF_Map",test_rb_hash},
        {"CPLUS List",test_cplus_list},
        {"HF_List",test_list},
        {"Std::List",test_std_list},
        {"HF_Vector",test_hf_vector},
        {"HF_CPLUS_Vector",test_cplus_vector},
        {"std_vector",test_std_vector},
        {"boost unorderd_map",test_boost_map},
//        {"HF Tree",test_rb_tree},
//        {"Test Malloc",test_malloc},
//        {"Test Realloc",test_realloc},
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
    HF_List         *list = List_Create(int);
    clock_t         start,end;

    start = clock();
    for ( j = 0 ; j < runtimes; ++j)
    {

        for ( i = 0 ; i < times; ++i)
        {
            List_Push_Back(int,list,i);
        }

    }
    end = clock();
    List_Free(list);
    fprintf(stdout,"HF_list Time Ellapsed:%dms\n",(end-start));
}
void test_cplus_list(void)
{
    uint32_t         i = 0 , j = 0;
    HList<int>            list;
    clock_t         start,end;

    start = clock();
    for ( j = 0 ; j < runtimes; ++j)
    {

        for ( i = 0 ; i < times; ++i)
        {
            list.add(i);
        }

    }
    end = clock();
    fprintf(stdout,"HF_list Time Ellapsed:%dms\n",(end-start));
}
void test_cplus_vector(void)
{
    uint32_t         i = 0 , j = 0;
    HFVector<int>            list;
    clock_t         start,end;

    start = clock();
    for ( j = 0 ; j < runtimes; ++j)
    {

        for ( i = 0 ; i < times; ++i)
        {
            list.add(i);
        }

    }
    end = clock();
    fprintf(stdout,"HF_list Time Ellapsed:%dms\n",(end-start));
}
void test_hf_vector(void)
{
    uint32_t         i = 0 , j = 0;
    hfvector        *vec = (hfvector*)malloc(sizeof(hfvector));
    clock_t         start,end;
//    STL_Vector      *svec = (STL_Vector*)malloc(sizeof(STL_Vector));


//    create_vector(&vec,10);
//    CreateVector(svec,int,10);
    Vector_Create(int,vec,10);
    start = clock();
    for ( j = 0 ; j < runtimes; ++j)
    {
        for ( i = 0 ; i < times; ++i)
        {
            Vector_Push_back(int,vec,i);
//            vec.push_back(&vec,(void*)i);
        }

    }
    end = clock();

    Vector_Free(vec);
//    free(svec->__store);
//    free(svec);
//    vec.free(&vec);
    fprintf(stdout,"HF_Vector Time Ellapsed:%dms\n",(end-start));
}
void test_std_vector(void)
{
    uint32_t         i = 0 , j = 0;
    std::vector<int>    vec;
    clock_t         start,end;


    start = clock();
    i = vec.max_size();
    for ( j = 0 ; j < runtimes; ++j)
    {
        for ( i = 0 ; i < times; ++i)
        {
           vec.push_back(i);
        }

    }
    end = clock();
    vec.clear();
    fprintf(stdout,"Std_Vector Time Ellapsed:%dms\n",(end-start));
}
void test_malloc(void)
{
    uint32_t         i = 0 , j = 0;
    clock_t         start,end;
    char            *c;

    start = clock();
    for ( j = 0 ; j < runtimes; ++j)
    {
        for ( i = 0 ; i < times; ++i)
        {
            c = (char*)malloc(1);
        }

    }
    end = clock();
    fprintf(stdout,"malloc Time Ellapsed:%dms\n",(end-start));
}

void test_realloc(void)
{
    uint32_t         i = 0 , j = 0;
    clock_t         start,end;
    char            *c = NULL;

    start = clock();
    for ( j = 0 ; j < runtimes; ++j)
    {
        for ( i = 0 ; i < times; ++i)
        {
            c = (char*)realloc(c,4);
            free(c);
        }

    }
    end = clock();
    fprintf(stdout,"realloc Time Ellapsed:%dms\n",(end-start));
}

void test_std_list(void)
{
    uint32_t         i = 0 , j = 0;

    clock_t         start,end;
    start = clock();
    for ( j = 0 ; j < runtimes; ++j)
    {
        std::list<int>   list;
    for ( i = 0 ; i < times; ++i)
    {
        list.push_back(i);
    }
    list.clear();
    }
    end = clock();


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
    {

        for ( i = 0 ; i < times; ++i)
        {
            boost_map.insert(std::make_pair(key[i],i));
        }

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
        //rb_insert(i+1,i+1,&rb);
    }
    rb_free(rb);
    end = clock();

    fprintf(stdout,"HF_Tree Time Ellapsed:%dms\n",end-start);

}
