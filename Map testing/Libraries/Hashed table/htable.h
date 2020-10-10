//
// Created by Alex on 07.08.2020.
//

#ifndef HASH_TABLE
#define HASH_TABLE

#include <utility>
#include <vector>
#include <cstring>
#include <string>

#if !(defined(size_t))
typedef unsigned int size_t;
#endif

template<class TypeName>
class hash_table
{
    typedef unsigned int uint;
    struct Node{
        std::string key;
        TypeName value;
        bool is_empty;
        Node(const std::string& _key,const TypeName& _value):key(_key),value(_value),is_empty(false){};
        Node():is_empty(true),key(""),value() {};
    };
public:
    //--------
    hash_table();
    hash_table(size_t,size_t);
    ~hash_table();
    hash_table<TypeName>& operator=(hash_table<TypeName>);
    //--------Modifiers--------
    std::pair<Node*,bool> insert(const std::string&,TypeName);
    size_t erase(const std::string&);
    //-------Access to elements-------
    TypeName& at(const std::string&);
    TypeName& operator[](const std::string&);
    //--------Operations--------
    Node* find(const std::string&);

private:
    //--------Array and data--------
    std::vector<std::vector<Node> > table{};
    size_t filled_slots_count;
    size_t size_w;
    size_t size_h;
    constexpr static const double state_inc = 0.75;
    constexpr static const double state_dec = 0.4;
    constexpr static const size_t default_size_w = 3;
    constexpr static const size_t default_size_h = 3;
    //--------Functions for resize--------
    void reserve_memory();
    void IncSize();
    void DecSize();
    uint get_next_prime(size_t);
    uint get_prev_prime(size_t);
    size_t hash_w(const std::string&,size_t);
    size_t hash_h(std::string,size_t);
};

#endif //HASH_TABLE
