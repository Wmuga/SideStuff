#include "hash_table.h"

int main() {
    hash_table<int> test;
    if(!test.insert("a",5).second) std::clog << 1;
    if(!test.insert("abn",4).second) std::clog << 1;
    if(!test.insert("ahgfd",23).second) std::clog << 1;
    if(!test.insert("adaf",987).second) std::clog << 1;
    if(!test.insert("alkjnhbgvf",123).second) std::clog << 1;
    if(!test.insert("a234",666).second) std::clog << 1;
    if(!test.insert("afghjk",345).second) std::clog << 1;
    if(!test.insert("abdfdhbf",98).second) std::clog << 1;
    if(!test.insert("adjasndjasnd",5).second) std::clog << 1;
    if(!test.insert("bgfdsfer",5).second) std::clog << 1;
    if(!test.insert("pepega",5).second) std::clog << 1;
    if(!test.insert("pepegahands",5).second) std::clog << 1;
    if(!test.insert("pepegasad",5).second) std::clog << 1;

    std::cout << test["a"] << " " << test["abn"] << " " << test["a234"];
    return 0;
}
