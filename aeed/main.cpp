#include <iostream>
#include "ae_coder.h"

int main(int argc,char* argv[]) {
    /*
    std::string file_in = R"(D:\Documents\GitHub\Labs_Progs\Side stuff\aeed\test.mp4)";
    std::string file_out = R"(D:\Documents\GitHub\Labs_Progs\Side stuff\aeed\test.ae)";
    try {
        ae_encoder(file_in, file_out);
    } catch (std::exception& error) {
        std::cout<<error.what();
    }
     */
    std::string filename = R"(D:\Documents\GitHub\SideStuff\aeed\ae_coder.cpp)";
    std::string filename1 = R"(D:\Documents\GitHub\SideStuff\aeed\ae_coder1.cpp.rle)";
    //rle::encode4(filename);
    rle::decode4(filename1);
    return 0;
}