#include "Youtube.hpp"

#include <fstream>
#include <iostream>
#include <string>

/// @brief Search Youtube video
/// @param phrase to search
/// @return 'watchUrl' that can be use in 'Youtube' object
void findVideo(std::string phrase, std::string availableNameOfCacheFile, std::string& varibleToStore)
{
    std::string fixdPhrase = "";
    if (phrase[0] == ' '){
        //return;
    }
    for (int i = 0; i < int(phrase.length()); i++){
        if (phrase[i] == ' '){
            fixdPhrase += "+";
        }
        else{
            fixdPhrase += phrase[i];
        }
    }
    std::ifstream Site(availableNameOfCacheFile + ".txt");
    if (!Site.fail()){
        std::cout << "fff";
        return;
    }
    Site.close();

    //system(std::string("curl https://www.youtube.com/results?search_query=" + fixdPhrase + " >> " + availableNameOfCacheFile + ".txt").c_str());
    system(std::string("curl -s https://www.youtube.com/results?search_query=Przytomna-Nosowska >> " + availableNameOfCacheFile + ".txt").c_str());
    Site.open(availableNameOfCacheFile + ".txt", std::ios::ate);

    int siteContentSize = Site.tellg();
    Site.seekg(0, std::ios::beg);

    std::string siteContent;
    for (int i = 0; i < siteContentSize; i++){
        siteContent += Site.get();
    }
    Site.close();
    system(std::string("del " + availableNameOfCacheFile + ".txt").c_str());
    int cursor = siteContent.find("watch?v=")+8;
    //std::cout << cursor;
    //int cursor = siteContent.find("{" "\"webCommandMetadata" "\":{" "\"url" "\":" "\"/watch?v=")+39;
    std::string watchUrl = "";
    for (int i = 0; i < 11; i++){
        watchUrl += siteContent[cursor];
        cursor++;
    }

    //std::cout << watchUrl;//siteContent.find("{" "\"webCommandMetadata" "\":{" "\"url" "\":" "\"/watch?v=")+39;
    varibleToStore = std::string("https://www.youtube.com/watch?v=" + watchUrl);
}