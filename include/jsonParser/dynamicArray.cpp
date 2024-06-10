#pragma once

#include <iostream>
#include "dynamicArray.hpp"

template <typename T> array<T>::array(){}

template <typename T> array<T>::~array(){
    element* i = lastElement;     
    element* tmp = lastElement;

    for (int j = 0; j < size; j++){      
        if (i->previous == nullptr){
            //debuging stuffs
            //std::cout << i->value << '\n';
            //std::cout << *i->value << '\n';

            delete i->value;
            delete i;

            return;
        }
        else{
            //debuging stuffs
            //std::cout << i->value << '\n';
            //std::cout << *i->value << '\n';

            tmp = i->previous;
            delete i->value;
            delete i->next;
            i = tmp;
           
        }
        
    }
    return;
}

template <typename T> void array<T>::pushBack(T value){
    element* newElement = new element();
    
    newElement->value = new T(value);
    newElement->index = size;

    newElement->previous = nullptr;
    newElement->next = nullptr;
    
    if (lastElement != nullptr){
	    newElement->previous = lastElement;
        lastElement->next = newElement;
    }
    lastElement = newElement;
    //debuging stuffs
    //std::cout << newElement->value << '\n' << '\n';
    size++;
    return;
}

template <typename T> T array<T>::get(int index){
    element* i = lastElement;

    if (index > size){
        throw std::runtime_error("-1");
    }
    while (true){
        if (i->index == index){
            delete i;
            return *i->value;
        }
        i = i->previous;
    }
}
