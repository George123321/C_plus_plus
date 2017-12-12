//
// Created by George on 12.12.2017.
//

#ifndef PROJECT_CLASS_H
#define PROJECT_CLASS_H

#include <cmath>
template<typename T>
class Matrix {
private:
    int n = *(new int);// n - кол-во строк, m - кол-во столбцов
    int m = *(new int);
    T **array = new T * [n];
public:
    Matrix() : n(1), m(1) {
        array[0] = new T [1];
        *array[0] = 1;
    }
    T get_elem(int k, int l) {
        return array[k][l];
    }
    int get_length() {
        return n;
    }
    int get_width() {
        return m;
    }
    Matrix(int _n, int _m) : n(_n), m(_m) {
        for(int i = 0; i < n; i++) {
            array[i] = new T [m];
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                array[i][j] = 0;
            }
        }
    }
    void write_matrix() {
        T tmp = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                std::cin >> tmp;
                array[i][j] = tmp;
            }
        }
    }
    void set_matrix(int k, int l, T data) { // в концепции ООП нельзя, но надо как-то тестить
        array[k][l] = data;
    }
    /*
    void print() {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                std::cout << array[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }*/
    Matrix<T> operator+(const Matrix & other) {
        Matrix<T> res(n, m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                res.array[i][j] = array[i][j] + other.array[i][j];
            }
        }
        return res;
    }

    Matrix<T> operator-(const Matrix & other) {
        Matrix<T> res(n, m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                res.array[i][j] = array[i][j] - other.array[i][j];
            }
        }
        return res;
    }

    void operator+=(const Matrix & other) {
        for(int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                array[i][j] += other.array[i][j];
            }
        }
    }

    Matrix<T> & operator=(const Matrix & other) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                array[i][j] = other.array[i][j];
            }
        }
        return *this;
    }

    void operator-=(const Matrix & other) {
        for(int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                array[i][j] -= other.array[i][j];
            }
        }
    }

    Matrix<T> transpose() {
        Matrix<T> res(m, n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                res.array[j][i] = array[i][j];
            }
        }
        return res;
    }

    T scalar(Matrix<T> & a) { // умножаем строку на стоку - вспомогательная прога
        T res;
        for(int i = 0; i < m; i++) {
            res += array[0][i] + a.array[0][i];
        }
        return res;
    }

    Matrix<T> operator*(Matrix<T> & a) {
        Matrix<T> res(n, a.get_width());
        T tmp;
        Matrix<T> b(a.get_width(), a.get_length());
        b = a.transpose();
        for(int i = 0; i < n; i++){
            for(int j = 0; j < a.get_width() ;j ++) {
                tmp = 0;
                for (int k = 0; k < m; k++) {
                    tmp += array[i][k] * b.array[j][k];
                }
                res.array[i][j] = tmp;
            }
        }
        return res;
    }

    Matrix<T> operator*(T a) {
        Matrix<T> res(n, m);
        res = *this;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                res.array[i][j] += a*array[i][j];
            }
        }
        return res;
    }

    Matrix<T> operator^(T a) {
        Matrix<T> res(n, m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                res.array[i][j] = pow(array[i][j], a);
            }
        }
        return res;
    }

    bool operator==(Matrix<T> & a) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(array[i][j] != a.array[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(Matrix<T> & a) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(array[i][j] == a.array[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    ~Matrix() {
        for(int i = 0; i < n; i++) {
            delete [] array[i];
        }
        delete[] array;
        delete &n;
        delete &m;
    }
};


template<typename T>
std::ostream &operator<<(std::ostream &stream, Matrix<T>& a) {
    for(int i = 0; i < a.get_length(); i++) {
        for(int j = 0; j < a.get_width(); j++) {
            std::cout << a.get_elem(i ,j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
#endif //PROJECT_CLASS_H
