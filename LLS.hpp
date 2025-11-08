#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() =default;
    // Insertion
    void push(const T& item) override {list.addHead(item);}

    // Deletion
    T pop() override {
        if (list.getCount()==0) {
        throw(std::runtime_error("Tried to pop w no eles"));
        }
        T temp = list.getHead()->data;
        list.removeHead();
        return(temp);
    }

    // Access
    T peek() const override {
        if (list.getCount()==0){
            throw(std::runtime_error("Tried to access w no eles"));
        }
        return(list.getHead()->data);

    }

    //Getters
    std::size_t getSize() const noexcept override{return(list.getCount());}
};