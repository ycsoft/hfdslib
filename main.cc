#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <list>

#include "c_rb_tree.h"
#include "c_list.h"

#include "c_hash.h"

#include "test/ctest.h"


int main(void)
{
    int v;
    char key[32] = {0};
    c_map *map = NULL;
    //run_test();

    test_list();
    return 0;
}

