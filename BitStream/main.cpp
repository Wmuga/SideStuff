#include "BitStream.h"
#include <iostream>

int main() {
    /*
    bitWriteStream fout(R"(D:\Documents\GitHub\SideStuff\BitStream\file.bin)");
    fout.WriteBits(4,4);
    fout.WriteBits(1,4);
     */
    bitReadStream fin(R"(D:\Documents\GitHub\SideStuff\BitStream\file.bin)");
    std::cout << "0x" <<fin.ReadBits(4) << fin.ReadBits(4);
    return 0;
}
