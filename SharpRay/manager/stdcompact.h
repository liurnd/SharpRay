#ifndef STDCOMPACT_H
#define STDCOMPACT_H
#include <list>
template<class T>
T* compactVector(const std::list<T>& v)
{
    T* tmp = new T[v.size()];
    for(int i = 0; i < v.size(); i++)
        tmp[i] = v[i];
    return tmp;
}

#endif // STDCOMPACT_H
