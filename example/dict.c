#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "c_hash.h"
#include "c_list.h"
#include "c_rb_tree.h"
#include "c_dict.h"
#include "cdef.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct   _VAL
{
    int a;
    int b;
}_VAL;




int char_cmp(void *k1, void *k2)
{
    printf("CMP====%s --- %s, return:%d\n",(char*)k1,(char*)k2,strcmp((char*)k1,(char*)k2));
    return strcmp((char*)k1,(char*)k2);
}

int key_compare(void * left, void * right)
{

}

void  ex_dict(void)
{
    XD_String       sk1 = String("Yang"),//{{STRING,5,Default_Compare,Default_Copy},"Yang"},
                    sv1 = String("Yang1") ,//{{STRING,5,Default_Compare,Default_Copy},"Yang1"},
                    sk2 = String("Chen"),//{{STRING,5,Default_Compare,Default_Copy},"Chen"},
                    sv2 = String("Chen2");//{{STRING,5,Default_Compare,Default_Copy},"Chen2"};

    XD_INT          ik1 = Int(4),//{{INT,4,Default_Compare,Default_Copy},1},
                    ik2 = Int(4);//{{INT,4,Default_Compare,Default_Copy},2};

    XD_INT          v1 = Int(4),//{{INT,4,Default_Compare,Default_Copy},11},
                    v2 = Int(4);//{{INT,4,Default_Compare,Default_Copy},22};

    XD_INT          test = Int(0);//{{INT,4,Default_Compare,Default_Copy},0};

    XD_String       stest = String("");//{{STRING,5,Default_Compare,Default_Copy},""};
    XD_Dict         *dict = calloc(1,sizeof(XD_Dict));

    Dict_Init(dict,sizeof(XD_String),sizeof(XD_String));
    Dict_Insert(dict,(&sk1),(&sv1));
    printf("===========================\n");
    Dict_Insert(dict,(&sk2),(&sv2));

    Dict_Get(dict,(&sk1),(&stest));
    printf("%s\n",stest._value);

}
#ifdef __cplusplus
}
#endif
