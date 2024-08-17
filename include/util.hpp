#ifndef UTIL_
#define UTIL_
#include "cmath"
#include <Pair.hpp>

const int infinity = 0x3f3f3f3f;

template <typename T>
void swapp(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
class Cell
{
private:
    T object;
    Cell<T> *next;

public:
    Cell() : object(T()), next(nullptr){};

    template <typename U>
    friend class LinkedList;

    template <typename U> // ignore
    friend class SortedLinkedList;

    template <typename U> // ignore
    friend class LinkedStack;
};

double pow(double n, int p)
{
    if (p == 0)
        return 1.0;

    bool isNegative = (p < 0);
    if (isNegative)
    {
        n = 1.0 / n;
        p = -p;
    }

    double result = 1.0;
    while (p > 0)
    {
        if (p % 2 == 1)
        {
            result *= n;
        }

        n *= n;
        p /= 2;
    }

    return result;
}

double euclid_dist(Pair<double, double> &u, Pair<double, double> &v)
{

    return std::sqrt((pow((v.getFirst() - u.getFirst()), 2) + pow((v.getSecond() - u.getSecond()), 2)));
}

#endif