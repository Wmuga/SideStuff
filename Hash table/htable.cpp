#include "htable.h"
#include <iostream>
#include <cmath>

template<class TypeName>
hash_table<TypeName>::hash_table():size_h(default_size_h),size_w(default_size_w),filled_slots_count(0) {
    reserve_memory();
}

template<class TypeName>
hash_table<TypeName>::hash_table(size_t _w, size_t _h):size_h(_h),size_w(_w),filled_slots_count(0) {
    reserve_memory();
}

template<class TypeName>
hash_table<TypeName>::~hash_table() = default;

template<class TypeName>
hash_table<TypeName> &hash_table<TypeName>::operator=(const hash_table<TypeName> x) {
    this->size_w=x.size_w;
    this->size_h=x.size_h;
    this->table=x.table;
    this->filled_slots_count=x.filled_slots_count;
    return *this;
}

/*
template<class TypeName>
size_t hash_table<TypeName>::hash_w(const std::string& value,size_t max_size)
{
    unsigned long long hash_key=0;
    for (char c : value)
    {
        hash_key=(hash_key*128)+(int)c;
    }
    size_t hash_key_size = ceil(log((double)hash_key)/log(2));
    hash_key*=2; hash_key^=hash_key_size;
    return hash_key%max_size;
}

template<class TypeName>
size_t hash_table<TypeName>::hash_h(std::string value,size_t max_size)
{
    unsigned long long hash_key=0;
    for (auto c = value.rbegin();c<value.rend();c++)
    {
        hash_key=(hash_key*256)+(int)*c;
    }
    size_t hash_key_size = ceil(log((double)hash_key)/log(2));
    hash_key*=2; hash_key^=hash_key_size;
    return hash_key%max_size;
}
*/

template<class TypeName>
size_t hash_table<TypeName>::hash_w(const std::string& value,size_t max_size)
{
    uint hash_result = 0;
    for (int i = 0; value[i] != 0; ++i)
        hash_result = ((max_size-1) * hash_result + value[i]) % max_size;
    hash_result = (hash_result * 2 + 1) % max_size;
    return hash_result;
}

template<class TypeName>
size_t hash_table<TypeName>::hash_h(std::string value,size_t max_size)
{
    uint hash_result = 0;
    for (int i = 0; value[i] != 0; ++i)
        hash_result = ((max_size+1) * hash_result + value[i]) % max_size;
    hash_result = (hash_result * 2 + 1) % max_size;
    return hash_result;
}

template<class TypeName>
unsigned int hash_table<TypeName>::get_prev_prime(size_t last_prime) {
    std::vector<uint> primes{};
    primes.push_back(2);
    for (size_t i=3;i<last_prime;i++)
    {
        bool is_prime = true;
        for (size_t j=0;
        j<(std::min(primes.size()-1,(unsigned int)ceil(sqrt(last_prime))));
        j++) if (i%primes[j]==0) {
            is_prime=false;
            break;
        }
        if (is_prime) primes.push_back(i);
    }
    return *(primes.end()-1);
}

template<class TypeName>
void hash_table<TypeName>::reserve_memory() {
    table.resize(size_h);
    for (size_t i=0;i<size_h;i++) table[i].resize(size_w);
}

template<class TypeName>
typename hash_table<TypeName>::Node *hash_table<TypeName>::find(const std::string& key) {
    return table[hash_h(key,size_h)][hash_w(key,size_w)].is_empty ? nullptr : &table[hash_h(key,size_h)][hash_w(key,size_w)];
}

template<class TypeName>
std::pair<typename hash_table<TypeName>::Node*, bool> hash_table<TypeName>::insert(const std::string& key, TypeName value) {
    if (find(key)) return std::make_pair(find(key),false);
    if (filled_slots_count>=size_w*size_h*state_inc) IncSize();
    table[hash_h(key,size_h)][hash_w(key,size_w)] = Node(key,value);
    filled_slots_count++;
    return std::make_pair(find(key),true);
}

template<class TypeName>
TypeName &hash_table<TypeName>::at(const std::string& key) {
    if (find(key)) return table[hash_h(key,size_h)][hash_w(key,size_w)].value;
    else throw std::out_of_range("map::out_of_range");
}

template<class TypeName>
TypeName &hash_table<TypeName>::operator[](const std::string& key) {
    return insert(key,TypeName()).first->value;
}

template<class TypeName>
size_t hash_table<TypeName>::erase(const std::string& key) {
    if (!find(key)) return 0;
    size_t prev_size = (size_h==size_w) ? pow(get_prev_prime(size_w),2) : pow(std::min(size_w,size_h),2);
    if (filled_slots_count==prev_size*state_dec) DecSize();
    table[hash_h(key,size_h)][hash_w(key,size_w)] = Node();
    filled_slots_count--;
    return 1;
}

template<class TypeName>
void hash_table<TypeName>::IncSize() {
    size_t* change_value =&(size_w<=size_h ? size_w : size_h);
    *change_value = get_next_prime(*change_value);
    hash_table<TypeName> new_table(size_w,size_h);
    *change_value=get_prev_prime(*change_value);
    for (size_t j=0;j<size_h;j++) for (size_t i=0;i<size_w;i++) if (!table[j][i].is_empty) new_table.insert(table[j][i].key,table[j][i].value);
    *this=new_table;
}

template<class TypeName>
void hash_table<TypeName>::DecSize() {
    size_t* change_value =&(size_w>=size_h ? size_w : size_h);
    *change_value = get_next_prime(*change_value);
    hash_table<TypeName> new_table(size_w,size_h);
    *change_value=get_prev_prime(*change_value);
    for (size_t j=0;j<size_h;j++) for (size_t i=0;i<size_w;i++) if (!table[j][i].is_empty) new_table.insert(table[j][i].key,table[j][i].value);
    *this=new_table;
}

template<class TypeName>
unsigned int hash_table<TypeName>::get_next_prime(size_t cur_prime) {
    size_t next_prime=cur_prime+1;
    bool is_prime;
    do {
        is_prime=true;
        for (size_t i = 2; i <= ceil(sqrt(next_prime)); i++) {
            if (next_prime % i == 0) {
                is_prime = false;
                next_prime++;
                break;
            }
        }
    }while (!is_prime);
    return next_prime;
}






