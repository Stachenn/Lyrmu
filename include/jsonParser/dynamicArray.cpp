#pragma once

#include <iostream>
#include "dynamicArray.hpp"

template <typename T> array<T>::~array(){
    element* i = lastElement;     
    element* tmp = lastElement;

    for (int j = 0; j < size-1; j++){
        tmp = i->previous;
        
        delete i;
        i = tmp;
    }
    return;
}


template <typename T> T& array<T>::operator[](int i){
    element* k = lastElement;
    this->x = i;
    if (i > size){
        throw std::out_of_range("Given argument 'i' is out of range");
    }

    for (int j = 0; j < size; j++){
        if (k->index == i){
            return k->value;
        }
        k = k->previous;
    }
    throw std::out_of_range("Given argument 'i' is out of range");
}

template <typename T> void array<T>::pushBack(T value){
    element* newElement = new element();
    
    newElement->value = value;
    newElement->index = size;

    newElement->previous = nullptr;
    newElement->next = nullptr;

    if (lastElement != nullptr){
	    newElement->previous = lastElement;
        lastElement->next = newElement;
    }
    lastElement = newElement;

    size++;
    return;
}