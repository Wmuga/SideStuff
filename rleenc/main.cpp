#include <iostream>
#include "rle.h"

int main() {
    rle_encoder enc;
    std::string filename = R"(D:\Documents\GitHub\Labs_Progs\Side stuff\rleenc\test.mp4)";
    enc.encode(filename);
    return 0;
}
