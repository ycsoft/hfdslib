
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "cdef.h"

int  getType(void *data)
{
    return ((BaseType*)data)->type;
}


int     Default_Compare(void *a1, void *a2)
{
    int tp1 = getType(a1), tp2 = getType(a2);
    switch( tp1 )
    {
    case INT:{
        XD_INT  *x1 = (XD_INT*)a1,*x2 = (XD_INT*)a2;
        return x1->_value - x2->_value;}
    case REAL:{
        XD_Real *x1 = (XD_Real*)a1,*x2 = (XD_Real*)a2;
        return x1-x2;}
    case STRING:{
        char *s1 = ((XD_String*)a1)->_value,
             *s2 = ((XD_String*)a2)->_value;
        return strcmp(s1,s2);
        }
    }
}

void    Default_Copy( void *a1, void *a2)
{
    int tp = getType(a2);
    switch( tp )
    {
    case INT:{
        XD_INT  *x2 = (XD_INT*)a2;
        ((XD_INT*)a1)->_cls = x2->_cls;
        ((XD_INT*)a1)->_value = x2->_value;
        break;
        }
    case REAL:{
        XD_Real *x1 = (XD_Real*)a1,*x2 = (XD_Real*)a2;
        x1->_cls = x2->_cls;
        x1->_value = x2->_value;
        break;}
    case STRING:{
        char  *s2 = ((XD_String*)a2)->_value;
        BaseType    *base = (BaseType*)a2;
        int sz = base->size;
        ((XD_String*)a1)->_cls = (*base);
        ((XD_String*)a1)->_value = malloc(sz);
        strcpy(((XD_String*)a1)->_value,s2);
        break;
        }
    }
}
