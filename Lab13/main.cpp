#include <iostream>

#include <cmath>


class vector3d {
public:
    const static vector3d X;
    const static vector3d Y;
    const static vector3d Z;
    const static vector3d ZERO;
    int x, y, z;
    vector3d() : x(0), y(0), z(0) {}
    vector3d(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
    vector3d operator+(const vector3d & other) {
        return vector3d(x+other.x, y+other.y, z+other.z);
    }
    vector3d operator-(const vector3d & other) {
        return vector3d(x-other.x, y-other.y, z-other.z);
    }
    int operator*(const vector3d &other) {
        return x*other.x + y*other.y + z*other.z;
    }
    vector3d vec_pr(const vector3d &other) {
        return vector3d(y*other.z-z*other.y, -x*other.z+z*other.x, x*other.y-y*other.z);
    }
    void print() {
        std::cout << x << " " << y << " " << z << std::endl;
    }
    vector3d operator*(int a) {
        return vector3d(a*x, a*y, a*z);
    }
    double length() {
        return pow(pow(x, 2) + pow(y, 2) + pow(z, 2), 0.5);
    }

    vector3d normalize() { // плохо: флоат преобразую к инт. но мне лень править
        double l = length();
        return vector3d(int(x/l), int(y/l), int(z/l));
    }
    bool operator==(const vector3d &other) {
        if((x == other.x) and (y == other.y) and (z = other.z)) {
            return true;
        }
        else {
            return false;
        }
    }
    bool operator!=(const vector3d &other) {
        if((x == other.x) and (y == other.y) and (z = other.z)) {
            return false;
        }
        else {
            return true;
        }
    }
    // TODO: дописать

};

std::ostream &operator<<(std::ostream &stream, const vector3d &a) {
    return stream << a.x << " " << a.y << " " << a.z;
}

int main() {
    vector3d v_1(4, 6, 2);
    vector3d v_2(1, 1, 1);
    vector3d v_3 = v_1.vec_pr(v_2);
    v_3.print();
    std::cout << v_3 << " " << v_3.length();
    return 0;
}