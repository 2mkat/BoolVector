#include <iostream>
#include "bool_l.h"
#include "bool_l.cpp"

int main() {
    BoolVector c1(5);
   // std::cin >> c1;
    std::cout << c1 << '\n';
    std::cout << c1[2];

    return 0;
}