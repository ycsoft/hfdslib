#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <list>

#include "c_rb_tree.h"
#include "c_list.h"

#include "c_hash.h"

#include "test/ctest.h"

void search_prime(int start, int end)
{
    int i = 0 , j = 0, k = 0,find = 0;
    for ( i = start; i < end; ++i)
    {
        find = 1;
        for ( j = 2 ; j < i; j++)
        {
            if ( i % j == 0)
            {
                find = 0;
                break;
            }
        }
        if ( find == 1)
        {
            k++;
            fprintf(stdout,"%d\t",i);
            if ( k % 5 == 0 )
                fprintf(stdout,"\n");
        }

    }
    fprintf(stdout,"OK\n");
}

int main(void)
{
    int v = 10;
    char key[32] = {0};
    c_map *map = NULL;
    //run_test();

//    search_prime(1000,10000);
    test_list();

//    map = map_create();

//    map->set(map,"yang",1);
//    map->set(map,"yang",3);

//    printf("yang = %d\n",map->get(map,"yang"));
//    printf("chen = %d\n",map->get(map,"chen"));

    return 0;
}

