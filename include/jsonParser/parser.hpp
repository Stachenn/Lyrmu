#pragma once

#include <iostream>
#include <cstring>

#include "dynamicArray.hpp"

class jsonParser{
    private:
        template <typename T> T ret(T x) {return x;};
        
        template <typename T> void push(const char** cacheTable, const char** tableToAdd, int tableSize, T valueToAdd);
        //bool checkCorrectStructure(const char* contentToCheck);
        int varAmount = 0;
        
        const char* content = "";

        array <const char*> varNames;
        array <const char*> varValues;
        array <const char*> varTypes;
        const char** test;
    public:
        ///@brief Create jsonParser object
        ///@param content json content to parse can be change later
        jsonParser(const char* content);
        ~jsonParser();

        ///@brief Parse 'content'
        ///@return Table of all varibles n values of it 
        void parse(const char* content);
        
        const char** getNames(){return test;};//{return this->varNames;};
        const char** getValues(){return test;};//{return this->varValues;};
        const char** getTypes(){return test;};//{return this->varTypes;};
        /// @brief Find varible
        /// @param varibleToFind varible to search 
        /// @return Varible value or '"-1"' if not found
        const char** find(const char* varibleToFind);
};