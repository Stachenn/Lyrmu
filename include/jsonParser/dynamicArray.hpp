#pragma once

#include <iostream>

template <typename T> class array{
    private:   
        struct element{      
            T* value;
            element* next;
            element* previous;

            int index;       
        };
        element* lastElement = nullptr;
        
        int size = 0;

    public:
        array();
        ~array();
        
        void pushBack(T value);
        void erase();
        void changeValue(int index);
        T get(int index);
        int getSize() {return size;};
};
