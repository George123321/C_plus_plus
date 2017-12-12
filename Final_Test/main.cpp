#include <iostream>
#include "class.h"

int main() {
    Matrix<int> a(2, 3);
    Matrix<int> b(3, 3);
    a.write_matrix();
    b.write_matrix();
    Matrix<int> c = a*b;
    std::cout << c;
    Matrix<int> d = c.transpose();
    std::cout << d;
    return 0;
}