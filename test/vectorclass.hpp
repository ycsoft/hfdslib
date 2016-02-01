#ifndef VECTORCLASS_H
#define VECTORCLASS_H

template<typename T>

class  HFVector
{
public:
    HFVector(int sz = 10)
    {
        _vec = (hfvector*)malloc(sizeof(hfvector));
        Vector_Create(T,_vec,sz);
    }
    void add(T v)
    {
        Vector_Push_back(T,_vec,v);
    }
    T get( int i)
    {
        return Vector_Get(T,_vec,i);
    }
    ~HFVector()
    {
        Vector_Free(_vec);
    }

private:
    hfvector    *_vec;
};

#endif // VECTORCLASS_H
