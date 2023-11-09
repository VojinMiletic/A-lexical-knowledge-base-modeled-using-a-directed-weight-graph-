#ifndef _vector_h_
#define _vector_h_
#include <iostream>
#include "Iterator.h"

template<typename DT>
class Vector {
private:
    DT* tab;
    int sizeVector;
    int capacityVector;
public:
    Vector() : tab(nullptr), sizeVector(), capacityVector() {}
    explicit Vector(int size);
    Vector(int size, int value);
    Vector(const std::initializer_list<DT>& v);
    Vector(const Vector<DT>& v);
    Vector(Vector<DT>&& v);

    Vector& operator=(const Vector<DT>& v);
    Vector& operator=(Vector<DT>&& v);

    ~Vector();

    bool operator==(const Vector<DT>& v);
    bool operator!=(const Vector<DT>& v);

    int capacity();
    int size();


    const DT& back() const;
    DT& back();

    DT& operator[](int size);
    const DT& operator[](int size) const;

    friend class Iterator<DT>;
    typedef class Iterator<DT> iterator;

    Iterator<DT> erase(Iterator<DT> pos);;
    Iterator<DT> insert(Iterator<DT> pos, const DT& value);

    Iterator<DT> end();
    Iterator<DT> begin();
};

template<typename DT>
Vector<DT>::Vector(int size) : sizeVector(size), capacityVector(size) {
    tab = new DT[sizeVector];
}

template<typename DT>
Vector<DT>::Vector(int size, int value) : sizeVector(size), capacityVector(size) {
    tab = new DT[sizeVector];

    for (int i = 0; i < sizeVector; i++)
        tab[i] = value;
}

template<typename DT>
Vector<DT>::Vector(const std::initializer_list<DT>& v) : sizeVector(v.size()), capacityVector(v.size()) {
    tab = new DT[v.size()];

    for (int i = 0; i < v.size(); i++)
        tab[i] = *(v.begin() + i);
}

template<typename DT>
Vector<DT>::Vector(const Vector<DT>& v) : sizeVector(v.sizeVector), capacityVector(v.capacityVector) {
    tab = new DT[capacityVector];

    for (int i = 0; i < sizeVector; i++)
        tab[i] = v.tab[i];
}

template<typename DT>
Vector<DT>::Vector(Vector<DT>&& v) : sizeVector(v.sizeVector), capacityVector(v.capacityVector) {
    tab = v.tab;
    v.tab = nullptr;
    v.sizeVector = 0;
    v.capacityVector = 0;
}

template<typename DT>
Vector<DT>& Vector<DT>::operator=(const Vector<DT>& v) {
    if (this == &v)
        return *this;

    delete[] tab;
    sizeVector = v.sizeVector;
    capacityVector = v.capacityVector;
    tab = new DT[capacityVector];

    for (int i = 0; i < capacityVector; i++)
        tab[i] = v.tab[i];
}

template<typename DT>
Vector<DT>& Vector<DT>::operator=(Vector<DT>&& v) {
    if (this == &v)
        return *this;

    delete[] tab;
    sizeVector = v.sizeVector;
    capacityVector = v.capacityVector;
    tab = v.tab;
    v.sizeVector = 0;
    v.capacity = 0;
    v.tab = nullptr;

    return *this;
}

template<typename DT>
Vector<DT>::~Vector() {
    delete[] tab;
}

template<typename DT>
bool Vector<DT>::operator==(const Vector<DT>& v) {
    if (sizeVector == v.sizeVector && capacityVector == v.capacityVector) {
        for (int i = 0; i < sizeVector; i++)
            if (tab[i] != v.tab[i])
                return false;
        return true;
    }
    return false;

}

template<typename DT>
bool Vector<DT>::operator!=(const Vector<DT>& v) {
    return !operator==(v);
}

template<typename DT>
int Vector<DT>::capacity() {
    return capacityVector;
}

template<typename DT>
int Vector<DT>::size() {
    return sizeVector;
}

template<typename DT>
const DT& Vector<DT>::back() const {
    if (sizeVector == 0)
        throw std::logic_error("Empty");

    return tab[sizeVector - 1];
}

template<typename DT>
DT& Vector<DT>::back() {
    if (sizeVector == 0)
        throw std::logic_error("Empty");

    return tab[sizeVector - 1];
}

template<typename DT>
DT& Vector<DT>::operator[](int size) {
    if (size > sizeVector - 1 || size < 0)
        throw std::out_of_range("Out of scope");
    else
        return tab[size];
}

template<typename DT>
const DT& Vector<DT>::operator[](int size) const {
    if (size > sizeVector - 1 || size < 0)
        throw std::out_of_range("Out of scope");
    else
        return tab[size];
}

template<typename DT>
Iterator<DT> Vector<DT>::end() {
    Iterator<DT> temp(tab + sizeVector);
    return temp;
}

template<typename DT>
Iterator<DT> Vector<DT>::begin() {
    Iterator<DT> temp(tab);
    return temp;
}

template<typename DT>
Iterator<DT> Vector<DT>::erase(Iterator<DT> pos) {
    int i = 0;
    auto it = (*this).begin();

    for (it; it != pos; it++, i++);

    for (auto it = pos + 1; it != (*this).end(); it++, i++)
        tab[i] = tab[i + 1];

    sizeVector--;
    return pos;
}

template<typename DT>
Iterator<DT> Vector<DT>::insert(Iterator<DT> pos, const DT& value) {
    int i = 0;

    if (capacityVector > sizeVector) {
        for (Iterator<DT> it = tab + sizeVector; it != pos; it--, i++)
            tab[sizeVector - i] = tab[sizeVector - i - 1];
        *pos = value;
        sizeVector++;
    }
    else {
        DT* temp = new DT[sizeVector + 1];
        for (Iterator<DT> it = tab; it != pos; it++, i++)
            temp[i] = tab[i];
        temp[i] = value;
        i++;
        for (Iterator<DT> it = tab + i + 1; it != tab + sizeVector + 2; it++, i++)
            temp[i] = tab[i - 1];
        delete[] tab;
        tab = temp;
        sizeVector++;
        capacityVector = sizeVector;
    }
}

#endif 
