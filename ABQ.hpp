#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T> {
    size_t capacity_;
    size_t curr_size_;
    int headPos;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ():capacity_(1),curr_size_(0),headPos(0),array_(nullptr){}
    explicit ABQ(const size_t capacity):capacity_(capacity),curr_size_(0),headPos(0),array_(new T[capacity]){}
    ABQ(const ABQ& other):capacity_(other.capacity_),curr_size_(other.curr_size_),headPos(other.headPos),array_(new T[other.capacity_]) {
        for (int i = 0; i<curr_size_;i++) {
            array_[i] = other.array_[i];
        }
    }

    ABQ& operator=(const ABQ& rhs) {
        if (this == &rhs){return *this;}
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        headPos = rhs.headPos;
        T* temp = new T[rhs.capacity_];
        for (int i = 0; i<curr_size_;i++) {
            temp[i] = rhs.array_[i];
        }
        delete[] array_;
        array_ = temp;
        temp = nullptr;
        return(*this);
    }

    ABQ(ABQ&& other) noexcept : capacity_(other.capacity_),curr_size_(other.curr_size_),headPos(other.headPos),array_(other.array_) {
        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.headPos = 0;
        other.array_ = nullptr;
    }
    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this == &rhs){return *this;}
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        headPos = rhs.headPos;
        delete[] array_;
        array_ = rhs.array_;
        rhs.array_ = nullptr;
        rhs.capacity_ = 0;
        rhs.headPos = -1;
        rhs.curr_size_ = 0;
        return(*this);
    }
    ~ABQ() noexcept override {
        capacity_ = 0;
        curr_size_ = 0;
        headPos = -1;
        delete[] array_;
        array_ = nullptr;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override{return curr_size_;}
    [[nodiscard]] size_t getMaxCapacity() const noexcept{return capacity_;}
    [[nodiscard]] T* getData() const noexcept{return array_;}

    // Insertion
    void enqueue(const T& data) override {
        if (curr_size_ == capacity_) { //if we have to increase the array size and copy over the elements alr
            // we'll copy them ordered
            size_t tempCap = capacity_;
            capacity_ *= scale_factor_;
            T* temp = new T[capacity_];
            for (int i = 0; i<curr_size_;i++) {
                temp[i] = array_[(headPos+curr_size_)%tempCap];
                headPos++;
            }
            headPos = 0;
            temp[curr_size_] = data;
            curr_size_++;
            delete[] array_;
            array_ = temp;
            temp = nullptr;
        }
        else {
            array_[(headPos+curr_size_)%capacity_] = data;
            curr_size_++;
        }

    }

    // Access
    T peek() const override{return array_[headPos];}

    // Deletion
    T dequeue() override {
        if (curr_size_==0) {
            throw(std::runtime_error("Tried to pop when no eles"));
        }
        T temp = array_[headPos];
        headPos = (headPos+1)%capacity_;
        curr_size_--;
        return(temp);
    }

};
