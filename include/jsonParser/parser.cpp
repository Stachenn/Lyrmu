#pragma once

#include <iostream>
#include <cstring>

#include "parser.hpp"

/// @brief Create jsonParser object
/// @param content json content to parse can be change later
/// @return nothing 

//jsonParser::addToTable()
jsonParser::jsonParser(const char* content){
    this->content = content;
}   

/// @brief Delete jsonParser object
jsonParser::~jsonParser(){
    delete this->content;
    delete this;
}

void jsonParser::parse(const char* userContent){
    const char* content = this->content;
    const char* cacheString;

    long long unsigned index = 0;

    int copyIndex = 0;
    int objectInfo = 0;
    int skips = 0;
    int currentVarAmount = 0;

    while (true){
        std::cout << index;
        if (content[index] == '"'){
            index++;
            while (true){
                if (char(content[index]) == '"'){
                    varNames.pushBack(cacheString);
                    std::cout << *varNames[0];
                    cacheString = "";
                    break;
                }
                //std::cout << content[index];
                //td::cout << "aa";
                index++;
                cacheString += content[index];
            }
        }

        // Saving value of varible
        if (content[index] == ':'){
            if (content[index+1] == '"'){
                skips = 2;
            }
            while (true){
                if (content[index] == '"'){
                    if (skips < 1){
                        int charToDelete;

                        copyIndex = index;
                        while (true){
                            if (content[copyIndex] == '"'){
                                char cp[strlen(cacheString) + 1];
                                strcpy(cp, cacheString);
                                
                                for (int i = strlen(cacheString); i < charToDelete+strlen(cacheString);i--){
                                    cp[i] = ' ';
                                }
                                cacheString = cp;
                                varValues.pushBack(cacheString);
                                varAmount++;

                                index--;
                                break;
                            }
                            charToDelete++;
                            copyIndex--;
                        }
                        break;
                    }
                    else{
                        skips--;
                    }
                }
                cacheString += content[index];
                index++;
            }
        }
        if (content[index] == '}'){
            objectInfo--;
        }
        if (content[index] == '{'){
            objectInfo++;
        }
        // Checking if any varible was added
        std::cout << currentVarAmount << '\n';
        std::cout << varAmount << '\n';
        if (varAmount > currentVarAmount){
            std::cout << varValues[varAmount-1];

            if (varValues[varAmount-1] == "false" || varValues[varAmount-1] == "true"){
                varTypes.pushBack("bool");
            }
            if (varValues[varAmount-1] == "null"){
                varTypes.pushBack("null");
            }
            if (varValues[varAmount-1][0] == '"' && varValues[varAmount-1][strlen(varValues[varAmount])] == '"'){
                varTypes.pushBack("string");                
            }
            for (int i = 0; i < strlen(varValues[varAmount]); i++){
                if (varValues[varAmount-1][i] > 47 && varValues[varAmount-1][i] < 58){
                    continue;
                }
                else{
                    varTypes.pushBack("error");
                    break;
                }
                if (i+1 == std::strlen(varValues[varAmount-1])){
                    varTypes.pushBack("int");
                }
            }
            if (varValues[varAmount-1][0] == '{' && varValues[varAmount-1][strlen(varValues[varAmount-1])] == '}'){
                varTypes.pushBack("object");                
                
                jsonParser object(varValues[varAmount-1]);
                object.parse(varValues[varAmount-1]);
                
                const char** objNames = object.getNames();
                const char** objTypes = object.getTypes();
                const char** objValues = object.getValues();

                for (int i = 0; i < object.varAmount; i++){
                    varTypes.pushBack(objTypes[i]);
                    varNames.pushBack(objNames[i]);
                    varValues.pushBack(objValues[i]);
                }
            }
            if (varValues[varAmount-1][0] == '[' && varValues[varAmount-1][strlen(varValues[varAmount-1])] == ']'){
                varTypes.pushBack("table");                
            }
            currentVarAmount++;
        }
        if (objectInfo < 1){
            break;
        }
        index++;
    }
    std::cout << varNames[0];
}

///@return list of founded items 
const char** jsonParser::find(const char* varibleToFind){

    static const char* f[5] = {"ft", "th"};

    return f;
}