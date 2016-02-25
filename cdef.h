#ifndef CDEF_H
#define CDEF_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum{ INT,REAL, STRING, BOOL, CUSTOM } EType;

typedef struct _Base
{
    int         type;
    int         size;
    int         (*compare)(void *thiz,void *other);
    void        (*copy)( void *thiz,void *other);
}BaseType;

typedef struct INT_Type
{
    BaseType    _cls;
    int         _value;
}XD_INT;

typedef struct Real_Type
{
    BaseType       _cls;
    double         _value;
}XD_Real;

typedef struct String_Type
{
    BaseType    _cls;
    char        *_value;
}XD_String;

typedef struct Custom_Type
{
    BaseType    _cls;
    void        *_value;
}XD_Custom;

int     Default_Compare(void *a1, void *a2);

void    Default_Copy( void *a1, void *a2);


#define         Int(X)          {{INT,sizeof(int),Default_Compare,Default_Copy},X}
#define         Real(X)         {{REAL,sizeof(double),Default_Compare,Default_Copy},X}
#define         String(X)       {{STRING,sizeof(char*),Default_Compare,Default_Copy},X}


#define     getType(data)       (((BaseType*)data)->type)

#ifdef __cplusplus
}
#endif

#endif // CDEF_H

