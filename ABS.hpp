#pragma once
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS():capacity_(1),curr_size_(0),array_(nullptr){}
    explicit ABS(const size_t capacity):capacity_(capacity),curr_size_(0),array_(new T[capacity]){}

    ABS(const ABS& other):capacity_(other.capacity_),curr_size_(other.curr_size_),array_(new T[other.capacity_]) {
        for (int i = 0; i<curr_size_;i++) {
            array_[i] = other.array_[i];
        }
    }


    ABS& operator=(const ABS& rhs) {
        if (this==&rhs){return(*this);}

        T* temp = new T[rhs.capacity_];
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        for (int i = 0; i<curr_size_;i++) {
            temp[i] = rhs.array_[i];
        }
        delete[] array_;
        array_ = temp;
        temp = nullptr;
        return(*this);
    }
    ABS(ABS&& other) noexcept: capacity_(other.capacity_), curr_size_(other.curr_size_),array_(other.array_){
        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.array_ = nullptr;
    }
    ABS& operator=(ABS&& rhs) noexcept {
        if (this == &rhs){return *this;}
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = rhs.array_;

        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        rhs.array_ = nullptr;
        return(*this);
    }
    ~ABS() noexcept override {
        delete[] array_;
        array_ = nullptr;
        capacity_ = 0;
        curr_size_ = 0;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return(curr_size_);
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    // Push item onto the stack
    void push(const T& data) override {
        if (curr_size_ == capacity_) {
            capacity_*=scale_factor_;
            T* temp = new T [capacity_];
            for (int i = 0; i<curr_size_;i++) {
                temp[i] = array_[i];
            }
            delete[] array_;
            array_ = temp;
            temp = nullptr;

        }
        array_[curr_size_] = data;
        curr_size_++;
    }

    T peek() const override{return array_[curr_size_-1];}

    T pop() override {
        if (curr_size_ == 0) {
            std::cerr<<"tried to pop when no elements present"<<std::endl;
        }
        T temp = array_[curr_size_-1];
        curr_size_--;
        return(temp);
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
