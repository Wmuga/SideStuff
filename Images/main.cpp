#include "bmp.h"
#include "test_func.h"


int main() {
    bmp_rw newBmp;
    newBmp.create(".\\Test.bmp",5,5,32);
    newBmp.write_line(0,0,5,5,{255,255,255},0.7);
    newBmp.wclose();
    return 0;
}