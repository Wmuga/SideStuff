/*
 * Just a stupid idea of recreating std::map
 */

#include <utility>
#include <cstdlib>
#include <algorithm>
#include <stdexcept>

#ifndef __SIZE_TYPE__
#define __SIZE_TYPE__ long unsigned int
#endif
#if !(defined (size_t))
typedef __SIZE_TYPE__ size_t;
#endif

#ifndef _GLIBCXX_MAP
#define _GLIBCXX_MAP

template<class TypeName, class TypeValue>
class map
{
private:
    typedef std::pair<TypeName,TypeValue> mappair;
    mappair* array;
    size_t current_count;
    //const size_t m_size = -1;
    const size_t m_size = 100000;


public:
    typedef mappair* iterator;
    map();
    ~map();
    map<TypeName,TypeValue>& operator=(const map<TypeName,TypeValue>);
    //-----------Modifiers-----------
    std::pair<iterator,bool> insert(mappair);
    std::pair<iterator,bool> emplace(TypeName,TypeValue);
    iterator insert(iterator, mappair);
    iterator emplace_hint(iterator ,TypeName,TypeValue);
    void swap(map<TypeName,TypeValue>&);
    void clear();
    iterator erase(iterator);
    size_t erase(TypeName);
    iterator erase(iterator,iterator);
    //-----------element access-----------
    TypeValue& at(TypeName);
    TypeValue& operator[](TypeName);
    //-----------iterators-----------
    iterator begin();
    iterator end();
    //-----------capacity-----------
    bool empty(){return current_count == 0;}
    size_t size(){return current_count;}
    size_t max_size(){return m_size;}
    //----------operations----------
    iterator find(TypeName);
    size_t count(TypeName);

private:
    std::pair<iterator,bool> find(mappair);
    size_t get_pos(iterator);
    void push(iterator, mappair);
    void add_size();
    void dec_size();
};


#endif //_GLIBCXX_MAP