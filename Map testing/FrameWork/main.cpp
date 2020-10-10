#include "hash_table.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <ctime>

struct Node
{
    char key[10];
    int value;
};


size_t tester_insert(std::ofstream* out,const std::vector<Node>& array)
{
    clock_t start,end;
    size_t coll;
    //for (size_t i=5000-1;i<1000000;i+=5000)
    for (size_t i=0;i<100;i+=1)
    {
        coll=0;
        *out<<i+1<<std::endl;
        std::clog<<"Insert "<<i+1<<std::endl;
        hash_table<int> _map(11,11);
        start=clock();
        for (size_t j=0;j<i;j++)
        {
            if(!_map.insert(array[j].key,array[j].value).second)coll++;
        }
        end=clock();
        *out<<end-start<<std::endl;
        std::clog<<end-start<<std::endl;
    }
    return coll;
}

size_t tester_find(std::ofstream* out,const std::vector<Node>& array)
{
    clock_t start,end;
    size_t coll;
    //for (size_t i=5000-1;i<1000000;i+=5000)
    for (size_t i=0;i<100;i+=1)
    {
        coll=0;
        *out<<i+1<<std::endl;
        std::clog<<"Find "<<i+1<<std::endl;
        hash_table<int> _map(11,11);
        for (size_t j=0;j<i;j++)
        {
            if(!_map.insert(array[j].key,array[j].value).second)coll++;
        }
        start=clock();
        _map.find(array[i/2].key);
        end=clock();
        *out<<end-start<<std::endl;
        std::clog<<end-start<<std::endl;
    }
    return coll;
}

size_t tester_erase(std::ofstream* out,const std::vector<Node>& array)
{
    clock_t start,end;
    size_t coll;
    //for (size_t i=5000-1;i<1000000;i+=5000)
    for (size_t i=0;i<100;i+=1)
    {
        coll=0;
        *out<<i+1<<std::endl;
        std::clog<<"Erase "<<i+1<<std::endl;
        hash_table<int> _map(11,11);
        for (size_t j=0;j<i;j++)
        {
            if(!_map.insert(array[j].key,array[j].value).second)coll++;
        }
        start=clock();
        _map.erase(array[i/2].key);
        end=clock();
        *out<<end-start<<std::endl;
        std::clog<<end-start<<std::endl;
    }
    return coll;
}

size_t tester_main(size_t (*tester_func)(std::ofstream*,const std::vector<Node>&),const std::string& fout)
{
    std::ofstream out1("..\\out1.txt");
    std::ofstream out2("..\\out2.txt");
    std::ofstream out3("..\\out3.txt");

    std::ifstream in1("..\\in.txt",std::ios::binary);

    std::vector<Node> in_ar;
    while(true) {
        Node el{};
        in1.read((char*)&el, sizeof(Node));
        if (in1.eof()) break;
        in_ar.push_back(el);
    }
    in1.close();
    std::thread t1(tester_func,&out1,in_ar);
    std::thread t2(tester_func,&out2,in_ar);
    size_t collisions = tester_func(&out3,in_ar);
    t1.join();
    t2.join();
    out1.close();out2.close();out3.close();

    std::ifstream fin1("..\\out1.txt");
    std::ifstream fin2("..\\out2.txt");
    std::ifstream fin3("..\\out3.txt");

    std::ofstream out(fout);

    while (true)
    {
        size_t count;
        size_t val1;
        size_t val2;
        size_t val3;
        fin1 >> count; fin2 >> count; fin3 >> count;
        fin1 >> val1; fin2 >> val2; fin3 >> val3;
        if (fin1.eof() || fin2.eof() || fin3.eof()) break;
        out << count << "\n";
        out << val1 << "\n" << val2 << "\n" << val3 << std::endl;
    }

    fin1.close();fin2.close();fin3.close(); out.close();
    remove("..\\out1.txt");remove("..\\out2.txt");remove("..\\out3.txt");
    return collisions;
}


int main() {
    size_t coll = tester_main(tester_insert,  "..\\Insert.txt");
    size_t coll2 = tester_main(tester_find,    "..\\Find.txt");
    size_t coll3 = tester_main(tester_erase,   "..\\Erase.txt");
    std::ofstream off("collisions.txt");
    off<<coll << " "<< coll2 << " " << coll3;
    return 0;
}
