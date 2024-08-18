#pragma once

#include <iostream>
#include <cstring>

#include "parser.hpp"

/// @brief Create jsonParser object
/// @param content json content to parse can be change later
/// @return nothing 

//jsonParser::addToTable()
jsonParser::jsonParser(std::string content){
    this->content = content;
}   

/// @brief Delete jsonParser object
jsonParser::~jsonParser(){
}

int jsonParser::find(std::string varibleName){
    for (int i = 0; i < this->varNames.size()-1; i++){
        //std::cout << this->varNames[i];
        if (this->varNames[i] == varibleName){
            return 0;
        }
    }
    return -1;
}


const char** jsonParser::getAll(std::vector <std::string> table){
    const char* tabl[table.size()-1];
    for (int i = 0; i < table.size()-1; i++){
        tabl[i] = table[i].c_str();
    }
    return tabl;
}

int jsonParser::getType(){
    int i = 0;
    int j = std::string(content).length()-1;

    while (true){
        if (std::string(content).length()-1 < i){
            return -1;
            break;
        }
        if (content[i] != ' '){
            break;
        }
        i++;
    }
    while (true){
        if (0 > j){
            return -1;
            break;
        }
        if (content[j] != ' '){
            break;
        }
        j--;
    }
    if (content[i] == '[' && content[j] == ']'){
        return 1;
    }
    if (content[i] == '{' && content[j] == '}'){
        return 0;
    }
    else{
        return -1;
    }
}

void jsonParser::parse(){
    std::string content = this->content;
    std::string cache = "";

    bool isInObject = false;
    bool isInString = false;
    bool isObject = false;
    int objectSkips = 0;
    int index = 0;
    int copyIndex = 0;
    int skips = 0;
    int type = getType();
    int currentVarAmount = 0;
    
    if (type == 1){ 
        objectSkips++;
    }

    while (true){
        // Start saving var name
        //std::cout << content[index];
        if (content[index] == '"' && type != 1){
            while (true){
                index++;
                
                if (content[index] == '"'){
                    varNames.push_back(cache);
                    cache = "";

                    break;
                }
                cache += content[index];
            }
        }
        if (content[index] == ':' || (type == 1 && content[index] != ' ')){
            //std::cout << 'a';
            skips = 0;
            index++;

            if (type == 1){
                varNames.push_back(std::to_string(varAmount));
            }
            
            while (true){
                if (content[index] != ' '){
                    break;                  
                }
                index++;
            }
            
            while (true){
                if (content[index] == '"'){
                    isInString = !isInString;
                }
                if (content[index] == '{' || content[index] == '[' && !isInString){
                    isInObject = true;
                    isObject = true;
                    skips++;
                }
                if (content[index] == '}' || content[index] == ']' && !isInString){
                    skips--;
                }
                if (isInObject && skips == 0){
                    isInObject = false;
                }
                if ((content[index] == ',' || content[index] == '}' || content[index] == ']') && (!isInObject && !isInString)){
                    copyIndex = cache.length();
                    while (true){
                        
                        if (cache[copyIndex] != ' '){
                            break;
                        }
                        cache.erase(copyIndex, 1);
                        copyIndex--;
                    }
                    if ((content[index] == '}' || content[index] == ']') && isObject){
                        cache += content[index];
                        //index++;
                    }
                    varValues.push_back(cache);
                    cache = "";
					skips = 0;
                    varAmount++;
                    break;
                }
                cache += content[index];
                index++;     
            }
        }
        
        if (varAmount > currentVarAmount){
            while (true){
                if (varValues[varAmount-1] == "false" || varValues[varAmount-1] == "true"){
                    varTypes.push_back("bool");
                    break;
                }
                
                if (varValues[varAmount-1] == "null"){
                    varTypes.push_back("null");
                    break;
                }
                
                if (varValues[varAmount-1][0] == '"' && varValues[varAmount-1][varValues[varAmount-1].length()-1] == '"'){
                    varTypes.push_back("string"); 
                    break;               
                }
                if (varValues[varAmount-1][0] > 47 && varValues[varAmount-1][0] < 58){
                    for (int i = 0; i < varValues[varAmount-1].length()-1; i++){
                        if (varValues[varAmount-1][i] > 47 && varValues[varAmount-1][i] < 58){}
                        else{
                            varTypes.push_back("error");
                            break;
                        }
                        if (i+1 > varValues[varAmount-1].length()-1){
                            varTypes.push_back("int");
                            break;
                        }     
                    }
                    break;
                }
                if (varValues[varAmount-1][0] == '{' && varValues[varAmount-1][varValues[varAmount-1].length()-1] == '}' ||
                    varValues[varAmount-1][0] == '[' && varValues[varAmount-1][varValues[varAmount-1].length()-1] == ']'   ){
                    
                    if (varValues[varAmount-1][0] == '[' && varValues[varAmount-1][varValues[varAmount-1].length()-1] == ']'){
                        varTypes.push_back("table");
                    }
                    else{
                        varTypes.push_back("object");                
                    }

                    jsonParser object(varValues[varAmount-1].c_str());

                    //std::cout << '|';
                    object.parse();
                    ///std::cout << '|';

                    std::vector<std::string> objNames = object.getNames();
                    std::vector<std::string> objTypes = object.getTypes();
                    std::vector<std::string> objValues = object.getValues();

                    for (int i = 0; i < object.varAmount-1; i++){
                        
                        //std::cout << "\n" << objNames[i];
                        //std::cout << objValues[i];
                        //std::cout << objTypes[i];
                        varTypes.push_back(objTypes[i]);
                        varNames.push_back(objNames[i]);
                        varValues.push_back(objValues[i]);
                    }
                    
                    index++;                  
                    break;
                }

                else{
                    varTypes.push_back("error");
                    break;
                }
            }
            currentVarAmount++;
        }
        ///std::cout << 'x';
        if (content[index] == '{' || content[index] == '['){
            //std::cout << "content[index]";
            objectSkips++;
        }
        if (content[index] == '}' || content[index] == ']'){
            //std::cout << "content[index]";
            objectSkips--;
        }
        if (objectSkips == 0){
            //std::cout << "end";
            break;
        }
        index++;
    }
    return;
}
