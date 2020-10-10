#include <iostream>
#include "ae_coder.h"

int main(int argc,char* argv[]) {
    std::string file_in = R"(D:\Documents\GitHub\Labs_Progs\Side stuff\aeed\test.mp4)";
    std::string file_out = R"(D:\Documents\GitHub\Labs_Progs\Side stuff\aeed\test.ae)";
    try {
        ae_encoder(file_in, file_out);
    } catch (std::exception& error) {
        std::cout<<error.what();
    }
    return 0;
}