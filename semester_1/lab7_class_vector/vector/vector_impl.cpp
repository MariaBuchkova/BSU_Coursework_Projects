#include "vector_impl.h"
#include<iostream>
#include <cstdint>
#include <initializer_list>
#include<stdexcept>

Vector::Vector() {}
Vector::Vector(size_t amount) :
    size_(amount),capacity_(size_), arr_(new int[capacity_]{}) {}
Vector::Vector(std::initializer_list<int> list) : 
    size_(list.size()), capacity_(size_), arr_(new int[capacity_]) {
    std::copy(list.begin(), list.end(), arr_);
}
Vector::~Vector() {
    delete[] arr_;
}


Vector::Vector(const Vector& other) : 
    size_(other.size_), capacity_(other.capacity_), arr_(new int[capacity_]) {
    std::copy(other.arr_, other.arr_ + size_, arr_);
}
Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        delete[] arr_;
        arr_ = new int[capacity_];
        std::copy(other.arr_, other.arr_ + size_, arr_);
    }
    return *this;
}


int& Vector::operator[](const size_t i) {
    return arr_[i];
}
const int& Vector::operator[](const size_t i) const {
    return arr_[i];
}
int& Vector::At(const size_t i){
    if (i >= size_) {
        throw std::out_of_range("Error! index out of range");
    } 
    return arr_[i];
}
const int& Vector::At(const size_t i) const {
    if (i >= size_) {
        throw std::out_of_range("Error! index out of range");
    }
    return arr_[i];
}


size_t Vector::Size() const {
    return size_;
}
size_t Vector::Capacity() const {
    return capacity_;
}


void Vector::Swap(Vector& other) {
    std::swap(arr_, other.arr_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

void Vector::PushBack(const int num) {
    if (capacity_ > size_) {
        arr_[size_++] = num;
    } else {
        if (capacity_ > 0) {
            capacity_ *= 2;
        } 
        else {
            capacity_ = 1;
        }
        int* newArr = new int[capacity_];
        std::copy(arr_, arr_ + size_, newArr);
        newArr[size_++] = num;
        delete[] arr_;
        arr_ = newArr;
    }
}
void Vector::PopBack() {
    if (size_ > 0) {
        --size_;
    }
}
void Vector::Clear() {
    size_ = 0;
}
void Vector::Reserve(const size_t amount) {
    if (amount > capacity_) {
        int* newArr = new int[amount];
        std::copy(arr_, arr_ + size_, newArr);
        delete[] arr_;
        arr_ = newArr;
        capacity_ = amount;
    }
}

std::ostream& operator<<(std::ostream& out, const Vector& v){
    out << "[";
    if (v.size_ > 0) {
        out << v.arr_[0];
        for (size_t i = 1; i < v.size_; ++i) {
            out << ", " << v.arr_[i];
        }
    }
    out << "]";
    return out;
}