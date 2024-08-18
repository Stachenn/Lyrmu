#pragma once

#include <iostream>
#include <cstring>
#include <vector>

#include "dynamicArray.hpp"

class jsonParser{
    private:
        template <typename T> T ret(T x) {return x;};
        
        template <typename T> void push(const char** cacheTable, const char** tableToAdd, int tableSize, T valueToAdd);
        //bool checkCorrectStructure(const char* contentToCheck);
        int getType();
        int varAmount = 0;
        
        std::vector <std::string> varNames = {};
        std::vector <std::string> varValues = {};
        std::vector <std::string> varTypes = {};

        const char** getAll(std::vector <std::string> table);
        const char** test;

    public:
        std::string content = "";
        ///@brief Create jsonParser object
        ///@param content json content to parse can be change later
        jsonParser(std::string content);
        ~jsonParser();

        ///@brief Parse 'content'
        ///@return Table of all varibles n values of it 
        void parse();
        
        std::vector<std::string> getNames(){return varNames;};//{return this->varNames;};
        std::vector<std::string> getValues(){return varValues;};//{return this->varValues;};
        std::vector<std::string> getTypes(){return varTypes;};//{return this->varTypes;};
       
        /// @brief Find varible
        /// @param varibleName varible to search 
        /// @return Varible index or -1 if not found
        int find(std::string varibleName);
};