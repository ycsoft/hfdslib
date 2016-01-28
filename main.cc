#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <map>

#include <boost/unordered_map.hpp>

//#include "c_list.h"
//#include "c_hash.h"
//#include "c_rb_tree.h"
#include "c_dict.h"

#include "test/ctest.h"
#include "test/utils.h"

#define times 10000
#define runtimes 100

typedef struct _Test
{
    int a;
    int b;
    struct _Test  *next;
}_Test;

typedef char ** pp_c;

int main(void)
{

//    test_hash();
//    test_list();
//    test_boost_map();
//    test_rb_tree();

//    test_clock();


    run_test();

    return 0;
}
