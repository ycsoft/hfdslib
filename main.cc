#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <map>
#include <assert.h>

#include <boost/unordered_map.hpp>

//#include "c_list.h"
//#include "c_vector.h"

#include "test/ctest.h"

#include "c_rb_tree.h"
#include "c_dict.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

extern void  ex_vector(void);
extern void  ex_list(void);

typedef int*  PT;
int main(void)
{

    uint32_t    h = 0;
    dict_t  *dict  = (dict_t*)malloc(sizeof(dict_t));

    Dict_Create(int,int,dict);
    Dict_Insert(int,int,dict,1,5);
    Dict_Insert(int,int,dict,3,7);

    Dict_Insert(int,int,dict,2,15);
    Dict_Insert(int,int,dict,4,17);
    Dict_Insert(int,int,dict,5,15);
    Dict_Insert(int,int,dict,7,17);
    printf("Over");
//    Dict_Get(int,int,dict,5,&h);

//    printf("%d\n",h);

    return 0;
}

#ifdef __cplusplus
}
#endif
