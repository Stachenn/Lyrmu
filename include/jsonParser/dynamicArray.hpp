#pragma once

#include <iostream>

template <typename T> class array{
    private:   
        struct element{      
            T value;        
            element* next;
            element* previous;

            int index;       
        };
        int x;
        element* lastElement = nullptr;
        
        int size = 0;

    public:
        ~array();
        
        void pushBack(T value);
        void erase();
        void changeValue(int index);
        
        T& operator[](int i);
        int getSize() {return size;};
};
