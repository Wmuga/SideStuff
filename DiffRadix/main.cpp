#include <iostream>
#include "double_r.h"

int main() {
    /*
    double_r d1,d2;
    d1 = 199.031;
    d2 = 12.99;
     */
    double_r d1("199.031",11);
    double_r d2("12.99",11);
    std::cout<< d1 << "-" << d2 << "=" << d2-d1 << std::endl;
    return 0;
}
