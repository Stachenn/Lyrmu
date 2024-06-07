#pragma once

#include <iostream>
#include <vector>
#include "parser.hpp"

/// @brief Create jsonParser object
/// @param content json content to parse can be change later
/// @return nothing 
jsonParser::jsonParser(const char* content){
    this->content = content;
}   

/// @brief Delete jsonParser object
jsonParser::~jsonParser(){
    delete this->content;
    
    delete this->varNames;
    delete this->varTypes;
    delete this->varValues;
    delete this->cache;

    varTypes = nullptr;
    varNames = nullptr;
    varValues = nullptr;
    cache = nullptr;

    delete this;
}
 
const char** jsonParser::parse(const char* userContent){
    const char* content = userContent;
    int index = 0;

    int objectIn = 0;
    int objectOut = 0;

    if (std::strlen(this->content) <= 1){
        content = this->content;
    }

    while (true){
        if (content[index] == '"'){
            while (true){
                if (content[index] == '"'){
                    varAmount++;
                    for (int i = 0; i < varAmount; i++){
                        cache[i] = varNames[i];
                    }

                    delete this->varNames;
                    delete this->cache;
                    
                    varNames = new const char**[varAmount];
                    cache = new const char**[varAmount];

                    for (int i = 0; i < varAmount; i++){
                        varNames[i] = cache[i];
                    }
                    varNames[varAmount-1] = cacheName;
                    cacheName = "";
                }
                cacheName += content;
                index++;
            }
            //jsonParser recursionObject = jsonParser("");
            //recursionObject.~jsonParser();
            //jsonParser::parse();
            // Nie wiem czy zrobic rekurencje czy nie
            // ...trudne sie trafilo
            // jednak rekurencja :)
        }
        if ()



        if (this->content[index] == '{'){
            objectIn++;
        }

        if (this->content[index] == '}'){
            objectOut++;
            //tableOut--;
        }
        if (std::strlen(this->content) == index){
            if (objectIn > objectOut){
                //return "-2";
            }
            //return "-1";
        }
        index++;
    }
    return {"fds", "fdsd"};
    
    //int amountOfFindedVaribles = 0;

    //for (int i = 0; i < this->content; i++){
    //    if 
    //}
    //static const char* g[] = {"helo", "jes"};
    //static const char** f[4] = {"ft", "ht", g, "d"};
    delete content;
}

///@return list of founded items 
const char** jsonParser::find(const char* varibleToFind){

    static const char* f[5] = {"ft", "th"};

    return f;
}