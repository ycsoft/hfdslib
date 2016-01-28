#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <map>

#include <boost/unordered_map.hpp>

#include "c_list.h"
#include "c_hash.h"
#include "c_rb_tree.h"
#include "test/ctest.h"

#define times 10000
#define runtimes 100

typedef struct _Test
{
    int a;
    int b;
    struct _Test  *next;
}_Test;

void test_list2(void)
{

    uint32_t         i = 0 , j = 0;
    c_list          *list = list_init();
    c_map           *mp = map_create();
    rb_node_t       *rb = rb_node_new(0,0);
    c_list_node     *nodes[times];
    clock_t         start,end;
    _Test           ts;

    std::map<char*,int> std_map;

    boost::unordered_map<char*,int> boost_map;

    char   *key[times];

    for ( i = 0 ; i < times; i++)
    {
        key[i] = (char*)malloc(sizeof(char)*32);
        nodes[i] = list_node_new();
        sprintf(key[i],"%d",i);
    }

    start = clock();
    for ( j = 0 ; j < runtimes; ++j)
    for ( i = 0 ; i < times; ++i)
    {
        c_list_node *nd = list_node_new();
        list_push_back(list,nd);
    }
    free(list);
    end = clock();


    fprintf(stdout,"c_list Time Ellapsed:%d\n",(end-start));


    start = clock();
    for( j = 0 ;j < runtimes; ++j)
    for ( i = 0 ; i < times; ++i)
    {
        mp->set(mp,key[i],i);

    }
    mp->free(mp);
    end = clock();
    fprintf(stdout,"c_hash Time Ellapsed:%d\n",end-start);


    start = clock();
    for( j = 0 ;j < runtimes; ++j)
    for ( i = 0 ; i < times; ++i)
    {
        //mp->set(mp,key[i],i);
        std_map[key[i]] = i;
    }
    end = clock();
    fprintf(stdout,"std::map Time Ellapsed:%d\n",end-start);


    start = clock();
    for( j = 0 ;j < runtimes; ++j)
    for ( i = 0 ; i < times; ++i)
    {
        boost_map[key[i]] = i;
    }
    end = clock();
    fprintf(stdout,"boost::map Time Ellapsed:%d\n",end-start);

    start = clock();
    for ( j = 0 ; j < runtimes; ++j)
    for ( i = 0 ; i < times; ++i)
    {
        rb_insert(i+1,i+1,&rb);
    }
    rb_free(rb);
    end = clock();

    fprintf(stdout,"rb_tree Time Ellapsed:%d\n",end-start);


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

//void test_rb_tree(void)
//{
//    rb_node_t *root = rb_node_new(1,1);

//    rb_insert(2,2,&root);
//    rb_insert(3,3,&root);
//    rb_insert(4,4,&root);
//    rb_insert(5,5,&root);

//    rb_free(root);
//}

int main(void)
{

    test_hash();
    test_list();
    test_boost_map();
    test_rb_tree();

    return 0;
}
