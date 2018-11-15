#ifndef FUNCIONAL_HPP
#define FUNCIONAL_HPP

#include <functional>
#include <algorithm>

using namespace std::placeholders;

template<typename ContainerFromT, typename ContainerToT, typename Function>
void fmap(ContainerToT *ret, Function f, const ContainerFromT &lista)
{
    ret->resize(lista.size());
    std::transform(lista.begin(), lista.end(), ret->begin(), f);
}


template<typename ContainerT, typename Function>
ContainerT ffilter(Function f, const ContainerT &lista)
{
    ContainerT ret;
    for(typename ContainerT::const_iterator it = lista.begin(); it != lista.end(); ++it)
    {
        if(f(*it) == true)
        {
            ret.push_back(*it);
        }
    }
    return ret;
}


template<typename ContainerT, typename Function>
void ffilter(ContainerT *ret, Function f, const ContainerT &lista)
{
    for(typename ContainerT::const_iterator it = lista.begin(); it != lista.end(); ++it)
    {
        if(f(*it) == true)
        {
            ret->push_back(*it);
        }
    }
}


template<typename T, typename ContainerT, typename Function>
void freduce(T *ret, Function f, const ContainerT &lista)
{
    assert(lista.size() >= 2);
    
    *ret = *(lista.begin());
    for(typename ContainerT::const_iterator it = lista.begin() + 1; it!=lista.end(); ++it)
    {
        *ret = f(*ret, *it);
    }
}


template<typename ContainerT, typename Function>
bool fany(Function f, const ContainerT &lista)
{
    bool ret = false;
    for(typename ContainerT::const_iterator it = lista.begin(); it != lista.end(); ++it)
    {
        if(f(*it) == true)
        {
            ret = true;
            break;
        }
    }
    return ret;
}


template<typename ContainerT, typename Function>
bool fall(Function f, const ContainerT &lista)
{
    bool ret = true;
    for(typename ContainerT::const_iterator it = lista.begin(); it != lista.end(); ++it)
    {
        if(f(*it) == false)
        {
            ret = false;
            break;
        }
    }
    return ret;
}


template<typename ContainerT>
ContainerT take(size_t n, const ContainerT &lista)
{
    ContainerT ret;
    size_t tam = min(n, lista.size());
    size_t i = 0;
    for(typename ContainerT::const_iterator it = lista.begin(); it != lista.end() && i < tam; ++it, ++i)
    {
        ret.push_back(*it);
    }
    return ret;
}


template<typename ContainerT>
ContainerT drop(size_t n, const ContainerT &lista)
{
    ContainerT ret;
    if(n < lista.size())
    {
        for(typename ContainerT::const_iterator it = lista.begin() + n; it != lista.end(); ++it)
        {
            ret.push_back(*it);
        }
    }
    return ret;
}


#endif // ** FUNCIONAL_HPP **
