#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>
#include <iostream>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:

    // Big 5
    ABDQ():data_(new T[4]),capacity_(4),size_(0),front_(0),back_(0){}
    explicit ABDQ(std::size_t capacity):data_(new T[capacity]),capacity_(capacity),size_(0),front_(0),back_(0){}
    ABDQ(const ABDQ& other):data_(new T[other.capacity_]),capacity_(other.capacity_),size_(other.size_),front_(other.front_),back_(other.back_) {
        for (int i = 0; i<size_;i++) {
            data_[i] = other.data_[i];
        }
    }
    ABDQ(ABDQ&& other) noexcept : data_(other.data_),capacity_(other.capacity_),size_(other.size_),front_(other.front_),back_(other.back_) {
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }
    ABDQ& operator=(const ABDQ& other) {
        if (this == &other){return *this;}
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        T* temp = new T[capacity_];
        for (int i = 0; i<size_;i++) {
            temp[i] = other.data_[i];
        }
        delete[] data_;
        data_ = temp;
        temp = nullptr;
        return(*this);
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other){return *this;}
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        delete[] data_;
        data_ = other.data_;
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = -1;
        other.back_ = -1;

        return(*this);

    }
    ~ABDQ() override {
        delete[] data_;
        data_ = nullptr;
        capacity_ = 0;
        size_ = 0;
        front_ = -1;
        back_ = -1;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (size_ == capacity_) { //if we have to increase the array size and copy over the elements alr
            // we'll copy them ordered
            ensureCapacity();
            T* temp = new T[capacity_];
            for (int i = 0; i<size_;i++) { //can't put the same loop in capacity pq im using different indices
                if (front_>=capacity_ -1) {
                    temp[i+1] = data_[front_];
                    front_ = 0;
                }
                else {
                    temp[i+1] = data_[front_];
                    front_++;
                }
            }
            front_ = 0;
            back_ = size_;
            temp[0] = item;
            size_++;
            delete[] data_;
            data_ = temp;
            temp = nullptr;

        }
        else {
            if (front_ == 0 && size_ !=0){
                front_ = capacity_-1;
                data_[front_] = item;
            }
            else if (size_==0){
                front_ = 0;
                data_[front_] = item;
            }
            else {
                --front_;
                data_[front_] = item;
            }
            size_++;


        }
    }
    void pushBack(const T& item) override {
        if (size_ == capacity_) { //if we have to increase the array size and copy over the elements alr
            // we'll copy them ordered
            size_t tempCap = capacity_;
            ensureCapacity();
            T* temp = new T[capacity_];
            for (int i = 0; i<size_;i++) {
                temp[i] = data_[(front_+size_)%tempCap];
                front_++;
            }
            front_ = 0;
            back_ = size_;
            temp[size_] = item;
            size_++;
            delete[] data_;
            data_ = temp;
            temp = nullptr;
        }
        else {
            data_[(front_+size_)%capacity_] = item;
            back_ = (front_+size_)%capacity_;
            size_++;
        }

    }

    // Deletion
    T popFront() override {
        if (size_==0||capacity_==0) {
            throw(std::runtime_error("Tried to pop when no eles"));
        }
        T temp = data_[front_];
        size_--;

        if (front_+1 ==capacity_) {front_ = 0;}
        else {front_ ++;}

        return(temp);

    }
    T popBack() override {
        if (size_==0) {
            throw(std::runtime_error("Tried to pop when no eles"));
        }
        T temp = data_[back_];
        size_--;

        if (back_-1<=-1) {back_ = size_-1;}
        else {back_ --;}

        return(temp);
    }

    void ensureCapacity() {capacity_ *= SCALE_FACTOR;}

    // Access
    const T& front() const override {
        if (size_==0||capacity_==0) {
            throw(std::runtime_error("Tried to access when no eles"));
        }
        return data_[front_];
    }
    const T& back() const override {
        if (size_==0||capacity_==0) {
            throw(std::runtime_error("Tried to access when no eles"));
        }
        return data_[back_];
    }

    // Getters
    std::size_t getSize() const noexcept override{return size_;}

    void shrinkIfNeeded() {
        if ((size_*4)/capacity_<=1) {
            size_t tempCap = capacity_;
            capacity_/=2;
            T* temp = new T[capacity_];
            for (int i = 0; i<size_;i++) {
                temp[i] = data_[(front_+size_)%tempCap];
                front_++;
            }
            front_ = 0;
            back_ = size_;
            delete[] data_;
            data_ = temp;
            temp = nullptr;
        }
    }
    T* get_data_() {
        return data_;
    }

    void printForward() {
        for (int i = 0; i<capacity_;i++) {
            std::cout<<data_[i]<<std::endl;
        }
        std::cout<<""<<std::endl;

        std::cout<<front_<<std::endl;
        std::cout<<back_<<std::endl;

        std::cout<<front()<<std::endl;
        std::cout<<back()<<std::endl;

    }

    void shrinkIfNeeded() {
        if (size_*4 == capacity_) {
            size_t tempCap = capacity_;
            capacity_/=2;
            T* temp = new T[capacity_];
            for (int i = 0; i<size_;i++) {
                temp[i] = data_[(front_+size_)%tempCap];
                front_++;
            }
            front_ = 0;
            back_ = size_;

            delete[] data_;
            data_ = temp;
            temp = nullptr;
        }
    }
};
