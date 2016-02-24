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

//#include "c_list.h"
#include "c_vector.h"

#include "test/utils.h"
#include "test/ctest.h"

#include "c_rb_tree.h"
#include "c_dict.h"

#include "cdef.h"

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
    run_test();

    return 0;
}

#ifdef __cplusplus
}
#endif
