#include "lyric.hpp"

#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <codecvt>
#include <locale>
#include <thread>
#include "..\..\include\thread\mingw.thread.h"
#include "..\..\include\thread\mingw.invoke.h"

void getLyric(std::string songName, std::string availableNameOfCacheFile, std::string& varibleToStore){
    std::string siteContent = "";
    std::string formatedSongName = "";

    std::ifstream site(availableNameOfCacheFile + ".txt");

    for (int i = 0; i < int(songName.length()); i++){
        if (songName[i] == ' '){
            formatedSongName += "%20";
        }
        else{
            formatedSongName += songName[i];
        }
    }
    
    std::string lyricSearchSite;

    lyricSearchSite = std::string("https://genius.com/api/search/multi?per_page=5&q=" + formatedSongName);

    if (!site.fail()){
        site.close();

        return;
    }
    site.close();

    system(std::string("curl -s -X GET ""\"" + lyricSearchSite + "\"" + ">> " + availableNameOfCacheFile + ".txt").c_str());
    
    site.open(availableNameOfCacheFile + ".txt", std::ios::ate);

    int siteSize = site.tellg();
    site.seekg(0, std::ios::beg);
    
    for (int i = 0; i < siteSize; i++){
        siteContent += site.get();
    }

    int cursor = siteContent.find("\"""url""\":\"")+7;
    std::string url = "";

    while (true){
        if (siteContent[cursor] == '"'){
            break;
        }
        else{
            url += siteContent[cursor];
        }
        cursor++;
    }
    site.close();
    
    system(std::string("del " + availableNameOfCacheFile + ".txt").c_str());
    system(std::string("curl -s ""\"" + url + "\"" + ">> " + availableNameOfCacheFile + ".txt").c_str());

    site.open(availableNameOfCacheFile + ".txt", std::ios::ate);

    siteSize = site.tellg();
    site.seekg(0, std::ios::beg);
    
    siteContent = "";

    for (int i = 0; i < siteSize; i++){
        siteContent += site.get();
    }
    std::string lyric;

    cursor = siteContent.find("window.__PRELOADED_STATE__ = JSON.parse(");
    int endCursor = siteContent.find("window.__APP_CONFIG__");

    for (int i = cursor; i < endCursor; i++){
        if ((siteContent[cursor-1] == 'r' && siteContent[cursor] == '>') || (siteContent[cursor] == '>' && siteContent[cursor-1] == '"')){

            if (siteContent[cursor+1] == '\\' && siteContent[cursor+2] == '\\' && siteContent[cursor+3] == 'n'){
                siteContent[cursor+1] = ' ';
                siteContent[cursor+2] = ' ';
                siteContent[cursor+3] = ' ';
            }
            else{
                lyric += "   ";
            }
            
            while (true){
                cursor++;
                //if (cursor >)
                if (cursor > endCursor){
                    break;
                }

                if (siteContent[cursor] == '<'){// && siteContent[cursor+1] == 'b'){
                    cursor++;
                    break;
                }
                //std::cout << int('ż');
                
                        //std::cout << cursor << "\n";
                lyric += siteContent[cursor];
                        //break;    
                //}
            
                //lyric+=siteContent[cursor];
  
                //std::cout << siteContent[cursor];
            }
            lyric += "\n";
            continue;
        }
        cursor++;
    }
    site.close();
    system(std::string("del " + availableNameOfCacheFile + ".txt").c_str());
    //std::cout << lyric;
    varibleToStore = lyric;
    return;
}
