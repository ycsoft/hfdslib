#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "c_vector.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _point
{
    int x;
    int y;
    int z;
}Point;

void  ex_vector(void)
{
    hfvector *vec = (phfvector)malloc(sizeof(hfvector));
    Point p,p1,p2;

    Vector_Create(Point,vec,10);
    p.x = 1;
    p.y = 1;
    p.z = 1;
    Vector_Push_back(Point,vec,p);
    p.x = 2;
    p.y = 2;
    p.z = 2;
    Vector_Push_back(Point,vec,p);

    p1 = Vector_Get(Point,vec,0);
    p2 = Vector_Get(Point,vec,1);

    Vector_Free(vec);
}
#ifdef __cplusplus
}
#endif
