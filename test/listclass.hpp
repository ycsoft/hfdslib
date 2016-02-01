#ifndef LISTCLASS_H
#define LISTCLASS_H


struct c_list;
template<typename   T>
class HList
{
public:
    HList()
    {
        _list = List_Create(T);
    }

    void    add(T t)
    {
        List_Push_Back(T,_list,t);
    }
    T       front()
    {
        return List_Read_Front(T,_list);
    }
    T       back()
    {
        return List_Read_Back(T,_list);
    }
    T       pop_front()
    {
        T res = list_read_front(T,_list);
        List_Erase_Front(_list);
        return T;
    }

    ~HList()
    {
        List_Free(_list);
    }
private:
    c_list         *_list;
};

#endif // LISTCLASS_H
