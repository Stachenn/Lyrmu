#pragma once
#include <iostream>
#include <vector>

class jsonParser{
    private:
        template <typename T> T returnVal(T x) {return x;};
        
        int varAmount;
        
        const char** cacheName;
        const char** cache;

        const char** varNames;
        const char** varValues;
        const char** varTypes;
        //std::vector<const char*> varName[1];
        //std::vector<const char*> varValue[1];
        //std::vector<const char*> varType[1];
        //std::vector<const char*> varName[1];
        //std::vector<const char*> varValue[1];
        //std::vector<const char*> varType[1];
        //const char* jsonLis[4] = {"fr", "yf", "wf"};

    public:
        const char* content = "";

        ///@brief Create jsonParser object
        ///@param content json content to parse can be change later
        jsonParser(const char* content);
        ~jsonParser();

        ///@brief Parse 'content'
        ///@return Table of all varibles n values of it 
        const char** parse(const char* content);

        /// @brief Find varible
        /// @param varibleToFind varible to search 
        /// @return Varible value or '"-1"' if not found
        const char** find(const char* varibleToFind);
};