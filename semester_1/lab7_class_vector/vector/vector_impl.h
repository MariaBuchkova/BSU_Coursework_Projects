#pragma once
#include <initializer_list>
#include<iostream>

class Vector {
private: 
	size_t size_ = 0;
    size_t capacity_ = 0;
    int* arr_ = nullptr;
public:
    Vector();
    Vector(size_t);
    Vector(std::initializer_list<int>);
    ~Vector();

    Vector(const Vector&);
    Vector& operator=(const Vector&);

    int& operator[](const size_t);
    const int& operator[](const size_t) const;
    int& At(const size_t);
    const int& At(const size_t) const;

    size_t Size() const;
    size_t Capacity() const;
    

    void Swap(Vector& other);
    void PushBack(const int);
    void PopBack();
    void Clear();
    void Reserve(const size_t);
    
    friend std::ostream& operator<<(std::ostream&, const Vector&);

};
