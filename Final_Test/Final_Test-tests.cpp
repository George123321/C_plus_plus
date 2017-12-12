//
// Created by George on 12.12.2017.
//

#include <gtest/gtest.h>
#include "class.h"



TEST(Matrix, elemMatrix) {
    Matrix<int> a;
    EXPECT_EQ(a.get_elem(0, 0), 1);
}

TEST(Matrix, init) {
    Matrix<int> a(2, 3);
    int p = 0;
    for(int i =0; i<2; i++) {
        for(int j =0; j<3; j++) {
            p++;
            a.set_matrix(i, j, p);
        }
    }
    EXPECT_EQ(a.get_elem(1, 2), 6);
}

TEST(Matrix, EQ) {
    Matrix<int> a(2, 3);
    int p = 0;
    for(int i =0; i<2; i++) {
        for(int j =0; j<3; j++) {
            p++;
            a.set_matrix(i, j, p);
        }
    }
    Matrix<int> b(2, 3);
    b = a;
    EXPECT_EQ(a.get_elem(1, 2), b.get_elem(1, 2));
}

TEST(Matrix, plus) {
    Matrix<int> a(2, 3);
    int p = 0;
    for(int i =0; i<2; i++) {
        for(int j =0; j<3; j++) {
            p++;
            a.set_matrix(i, j, p);
        }
    }

    Matrix<int> b(2, 3);
    int q = 2;
    for(int i =0; i<2; i++) {
        for(int j =0; j<3; j++) {
            q++;
            b.set_matrix(i, j, q);
        }
    }
    Matrix<int> c = a+b;
    EXPECT_EQ(c.get_elem(1, 2), 14);
}

TEST(Matrix, minus) {
    Matrix<int> a(2, 3);
    int p = 0;
    for(int i =0; i<2; i++) {
        for(int j =0; j<3; j++) {
            p++;
            a.set_matrix(i, j, p);
        }
    }

    Matrix<int> b(2, 3);
    int q = 2;
    for(int i =0; i<2; i++) {
        for(int j =0; j<3; j++) {
            q++;
            b.set_matrix(i, j, q);
        }
    }
    Matrix<int> c = a-b;
    EXPECT_EQ(c.get_elem(1, 2), -2);
}

TEST(Matrix, plus_EQ) {
    Matrix<int> a(2, 3);
    int p = 0;
    for(int i =0; i<2; i++) {
        for(int j =0; j<3; j++) {
            p++;
            a.set_matrix(i, j, p);
        }
    }

    Matrix<int> b(2, 3);
    int q = 2;
    for(int i =0; i<2; i++) {
        for(int j =0; j<3; j++) {
            q++;
            b.set_matrix(i, j, q);
        }
    }
    a += b;
    EXPECT_EQ(a.get_elem(1, 2), 14);
}

TEST(Matrix, minus_EQ) {
    Matrix<int> a(2, 3);
    int p = 0;
    for(int i =0; i<2; i++) {
        for(int j =0; j<3; j++) {
            p++;
            a.set_matrix(i, j, p);
        }
    }

    Matrix<int> b(2, 3);
    int q = 2;
    for(int i =0; i<2; i++) {
        for(int j =0; j<3; j++) {
            q++;
            b.set_matrix(i, j, q);
        }
    }
    a -= b;
    EXPECT_EQ(a.get_elem(1, 2), -2);
}

TEST(Matrix, transpose) {
    Matrix<int> a(2, 3);
    int p = 0;
    for(int i =0; i<2; i++) {
        for(int j =0; j<3; j++) {
            p++;
            a.set_matrix(i, j, p);
        }
    }
    Matrix<int> b = a.transpose();
    EXPECT_EQ(b.get_elem(2, 1), 6);
}

TEST(Matrix, multiply_matrix) {
    Matrix<double> a(2, 3);
    Matrix<double> b(3, 3);
    int p = 0;
    for(int i =0; i<2; i++) {
        for(int j =0; j<3; j++) {
            p++;
            a.set_matrix(i, j, p);
        }
    }
    int q = 0;
    for(int i =0; i<3; i++) {
        for(int j =0; j<3; j++) {
            q++;
            b.set_matrix(i, j, q);
        }
    }
    Matrix<double> c = a*b;
    std::cout << c;
    EXPECT_EQ(c.get_elem(1, 2), 96);
}

TEST(Matrix, multiply_scal) {
    Matrix<double> a(2, 3);
    int p = 0;
    for(int i =0; i<2; i++) {
        for(int j =0; j<3; j++) {
            p++;
            a.set_matrix(i, j, p);
        }
    }
    Matrix<double> c = a*(2.0);
    EXPECT_EQ(c.get_elem(1, 2), 18);
}

TEST(Matrix, pow) {
    Matrix<double> a(2, 3);
    int p = 0;
    for(int i =0; i<2; i++) {
        for(int j =0; j<3; j++) {
            p++;
            a.set_matrix(i, j, p);
        }
    }
    Matrix<double> c = a^(2.0);
    EXPECT_EQ(c.get_elem(1, 2), 36);
}