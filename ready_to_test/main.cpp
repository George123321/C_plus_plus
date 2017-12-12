#include <iostream>
#include <cstring>
#include "vector.h"



int main() {
    Vector2D<int> a(5,3);
    Vector2D<int> b(7, 8);
    a+=b;
    a.Show();
}