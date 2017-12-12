//
// Created by George on 12.12.2017.
//

#ifndef PROJECT_VECTOR_H
#define PROJECT_VECTOR_H

template<typename T>
class Point2D
{
protected:
    T *x = new T;
    T *y = new T;
public:
    Point2D(T _x, T _y) {
        *x = _x;
        *y = _y;
    }
    virtual ~Point2D() {
        delete x;
        delete y;
        x = nullptr;
        y = nullptr;
    }

};

template<typename T>
class Vector2D : public Point2D<T> {
public:
    Vector2D(T _x, T _y) : Point2D<T>(_x, _y) {}
    void operator+=(Vector2D &other) {
        *(this->x) += *(other.x);
        *(this->y) += *(other.y);
    }
    void Show() {
        std::cout << *(this->x) << " " << *(this->y);
    }
    T getX() {
        return *(this->x);
    }
    T getY() {
        return *(this->y);
    }
};

template<typename T>
std::ostream &operator<<(std::ostream &stream, Vector2D<T>& a) {
    return stream << a.getX() << " " << a.getY();
}
#endif //PROJECT_VECTOR_H
