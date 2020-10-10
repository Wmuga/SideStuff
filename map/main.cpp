#include <iostream>
#include "hmap.h"

int main() {
    map<char,int> test;
    std::pair<char,int> pt= {'a',1};
    auto res = test.insert(pt);
    pt.first='b';
    test.insert(test.begin(),pt);
    pt.first='c';
    test.insert(test.end(),pt);
    for (auto map_pos = test.begin();map_pos<=test.end();map_pos++) std::cout << map_pos->first << " " << map_pos->second << "\n";
    std::cout << test['k'] << "\n";
    test['k']=10;
    std::cout << test['k']<< "\n";
    test.erase(test.begin());
    for (auto map_pos = test.begin();map_pos<=test.end();map_pos++) std::cout << map_pos->first << " " << map_pos->second << "\n";
    test.clear();
    std::cout<<test.empty();
    test.emplace('k',10);
    std::cout << test['k']<< "\n";
    return 0;
}
