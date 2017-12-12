//
// Created by George on 12.12.2017.
//

#include <gtest/gtest.h>
//#include "main.cpp"
#include "vector.h"


TEST(Vector2D, getX_test) {
    Vector2D<int> a(4, 5);
    EXPECT_EQ(a.getX(), 4) << "Equal size!";
    Vector2D<int> b(1, 2);
    a+=b;
    EXPECT_EQ(a.getX(), 5);
    EXPECT_EQ(a.getY(), 7);
}

TEST(Vector2D, plus_test) {
    Vector2D<int> a(4, 5);
    Vector2D<int> b(1, 2);
    a+=b;
    EXPECT_EQ(a.getX(), 5);
    EXPECT_EQ(a.getY(), 7);
}