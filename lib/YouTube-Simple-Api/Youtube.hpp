#pragma once

#include <fstream>
#include <iostream>
#include <string>
//std::string 
void findVideo(std::string phrase, std::string availableNameOfCacheFile, std::string& varibleToStore);

class Youtube{
    public:
        Youtube(std::string watchUrl);
        ~Youtube();
        /// @brief Search Youtube video
        /// @param phrase to search
        /// @return 'watchUrl' that can be use in 'Youtube' constructor
        
};

