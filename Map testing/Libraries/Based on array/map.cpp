#include "map.h"
template<class TypeName, class TypeValue>
map<TypeName,TypeValue>::map()
{
    current_count=0;
    array = (mappair*)malloc(sizeof(mappair));
}

template<class TypeName, class TypeValue>
std::pair<typename map<TypeName,TypeValue>::iterator,bool> map<TypeName,TypeValue>::insert(mappair value)
{
    std::pair<map<TypeName,TypeValue>::iterator,bool> result;
    result=find(value);
    if (result.second) {
        add_size();
        array[current_count - 1] = value;
        result.first=&array[current_count - 1];
    }
    return result;
}
template<class TypeName, class TypeValue>
typename map<TypeName,TypeValue>::iterator map<TypeName,TypeValue>::insert(iterator place, mappair value)
{
    std::pair<map<TypeName,TypeValue>::iterator,bool> element = find(value);
    if (element.second) {push(place,value); return place;}
    return element.first;
}

template<class TypeName, class TypeValue>
std::pair<typename map<TypeName,TypeValue>::iterator, bool> map<TypeName, TypeValue>::find(map::mappair value) {
    std::pair<map<TypeName,TypeValue>::iterator,bool> result;
    result.second=true;
    if (current_count != 1) {
        for (size_t i = 0; i < current_count; i++) if (array[i].first == value.first) {
                result.first=&array[i];
                result.second=false;
                break;
            }
    }
    return result;
}

template<class TypeName, class TypeValue>
void map<TypeName, TypeValue>::push(map::iterator place, map::mappair value) {
    add_size();
    size_t i=get_pos(place);
    mappair buffer;
    for (; i < current_count; i++){
        buffer = array[i];
        array[i]=value;
        value = buffer;
    }
}

template<class TypeName, class TypeValue>
map<TypeName,TypeValue>::~map()
{
    free(array);
}


template<class TypeName, class TypeValue>
std::pair<TypeName,TypeValue>* map<TypeName, TypeValue>::begin() {
    return &array[0];
}

template<class TypeName, class TypeValue>
std::pair<TypeName,TypeValue>* map<TypeName, TypeValue>::end() {
    return &array[current_count - 1];
}

template<class TypeName, class TypeValue>
void map<TypeName, TypeValue>::add_size() {
    if (current_count == m_size) throw std::overflow_error("map::overflow");
    current_count++;
    array = (mappair*)realloc(array, sizeof(mappair) * current_count);
}

template<class TypeName, class TypeValue>
void map<TypeName, TypeValue>::dec_size() {
    if (current_count == m_size) throw std::overflow_error("map::overflow");
    current_count--;
    if (current_count != 0) array = (mappair*)realloc(array, sizeof(mappair) * current_count);
}

template<class TypeName, class TypeValue>
TypeValue& map<TypeName, TypeValue>::operator[](TypeName fst) {
    std::pair<TypeName,TypeValue> value{};
    value.first=fst;
    auto result =find(value);
    if (result.second) {
        this->insert(value);
        return this->end()->second;
    }
    return result.first->second;

}

template<class TypeName, class TypeValue>
TypeValue& map<TypeName, TypeValue>::at(TypeName fst) {
    std::pair<TypeName,TypeValue> value{};
    value.first=fst;
    auto result =find(value);
    if (result.second) throw std::out_of_range("map::out_of_range");
    return result.first->second;
}

template<class TypeName, class TypeValue>
map<TypeName, TypeValue> &map<TypeName, TypeValue>::operator=(const map<TypeName,TypeValue> x) {
    this->current_count=x.current_count;
    array=(mappair*)malloc(sizeof(mappair) * current_count);
    std::copy(x.array, x.array + current_count, this->array);
    return *this;
}

template<class TypeName, class TypeValue>
void map<TypeName, TypeValue>::swap(map<TypeName, TypeValue>& x) {
    map<TypeName, TypeValue> buffer = this;
    this=x;
    x=buffer;
}

template<class TypeName, class TypeValue>
void map<TypeName, TypeValue>::clear() {
    this->current_count=0;
    this->array = (mappair*)(realloc(array,sizeof(mappair)));
}

template<class TypeName, class TypeValue>
std::pair<TypeName,TypeValue>* map<TypeName, TypeValue>::erase(const map::iterator position) {
    if (position==this->end()){
        dec_size();
        return this->end();
    }
    for (auto i = position;i<this->end();i++)
    {
        *i = *(i+1);
    }
    dec_size();
    return position;
}

template<class TypeName, class TypeValue>
size_t map<TypeName, TypeValue>::erase(TypeName er_name) {
    mappair value{};value.first=er_name;
    auto res =find(value);
    if (res.second) return 0;
    else erase(res.first);
    return 1;
}

template<class TypeName, class TypeValue>
std::pair<TypeName,TypeValue>* map<TypeName, TypeValue>::erase(map::iterator first, map::iterator last) {
    for (;first<last;first++) erase(first);
    return erase(first);
}

template<class TypeName, class TypeValue>
size_t map<TypeName, TypeValue>::get_pos(map::iterator place) {
    for (int i=0; i < current_count - 1; i++) if (array[i] == *place) return i;
    return 0;
}

template<class TypeName, class TypeValue>
std::pair<std::pair<TypeName,TypeValue>* , bool> map<TypeName, TypeValue>::emplace(TypeName x, TypeValue y) {
    mappair value = {x,y};
    return insert(value);
}

template<class TypeName, class TypeValue>
std::pair<TypeName,TypeValue>*  map<TypeName, TypeValue>::emplace_hint(map::iterator place, TypeName x, TypeValue y ) {
    mappair value = {x,y};
    return insert(place,value);
}

template<class TypeName, class TypeValue>
std::pair<TypeName,TypeValue>* map<TypeName, TypeValue>::find(TypeName fst) {
    mappair value{}; value.first = fst;
    auto result = find(value);
    if (result.second) return this->end();
    return result.first;
}

template<class TypeName, class TypeValue>
size_t map<TypeName, TypeValue>::count(TypeName fst) {
    return (find(fst)!=this->end() || this->end()->first==fst);
}
