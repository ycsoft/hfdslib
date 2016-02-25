#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <map>
#include <assert.h>
#include <stddef.h>
#include <sys/types.h>

#include <boost/unordered_map.hpp>

#include "ycdslib.h"
#include "test/utils.h"
#include "test/ctest.h"


#ifdef __cplusplus
extern "C"
{
#endif

extern void  ex_vector(void);
extern void  ex_list(void);
extern void  ex_dict(void);


int main(void)
{
//    ex_dict();
//    run_test();


    int i,j;
    for ( j = 0 ; j < 300; j++)
    {
        XD_Dict *dict = Dict_New();
        Dict_Init(dict,sizeof(XD_INT),sizeof(XD_INT));
        printf("times:%d\n",j+1);
        for ( i = 0 ; i < 10000; i++)
        {
            XD_INT  key = Int(i),value = Int(i);
            Dict_Insert(dict,(&key),(&value));
        }
        Dict_Free(dict);free(dict);

    }
    system("pause");
    return 0;

}

#ifdef __cplusplus
}
#endif
