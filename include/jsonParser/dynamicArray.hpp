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
        int x = 0;
        element* lastElement = nullptr;
        
        int size = 0;

    public:
        ~array();
        
        void pushBack(T value);
        void erase(int i);
        void changeValue(int index);
        
        T returnNormaly();
        T& operator[](int i);
        int getSize() {return size;};
};
