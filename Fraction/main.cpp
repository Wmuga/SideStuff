#include <iostream>
#include "Fraction.h"

int main() {
    Fraction newFraction(10,2);
    std::cout << newFraction << std::endl;
    newFraction=newFraction-Fraction(6,1);
    std::cout << newFraction << std::endl;
    return 0;
}
