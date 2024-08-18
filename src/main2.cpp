#include "C:\cpp\spotif\lib\YouTube-Simple-Api\Youtube.cpp"
#include "C:\cpp\spotif\lib\Genius-Simple-Api\lyric.cpp"
//#include "..\include\curl\curl.h"
//#include "..\include\jsonParser\parser.cpp"
#include "..\include\jsonParser\dynamicArray.cpp"

#include <windows.h>
#include <chrono>
#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>

#include "..\include\thread\mingw.thread.h"
#include "..\include\thread\mingw.invoke.h"

void play(std::string songName, std::string f){
    mciSendString(TEXT(std::string("play " + songName + ".mp3 wait").c_str()), NULL, 0, NULL);
}

int main(int argc, char* argv[]){
    
    array<int> test;
    test.pushBack(10);
    test.pushBack(20);
    test.pushBack(230);
    test.~array();

    return 0;
    std::string prompt = "";    
    std::string watchUrl = "";
    std::string lyric = "";
    std::string l[3]; 
    //std::string lyric = "";

    // ustalenie w konsoli system znakow ktory obsluguje polskie znaki "utf-8" 
    system("chcp 65001");

    //Get song from user
    std::cout << "Type song to download : ";
    std::getline(std::cin, prompt);
    std::cout << prompt;
    // ----


    //std::thread lyricThread(getLyric, prompt, "lyric", std::ref(lyric));
    //std::thread searchVid(findVideo, prompt, "site", std::ref(watchUrl));
    
    getLyric(prompt, "lyric", l);
    std::cout << l[0];
    //findVideo(prompt, "site", watchUrl);
    return 0;
    //searchVid.join();
    //
    //std::cout << std::string("download.py ").c_str();
    
    system(std::string("download.py " + watchUrl).c_str()); 
    //std::cout << "|" << lyric << "|";
    //std::cout << "|" << watchUrl << "|";
    //std::cout << lyric;
    //watchUrl = searchVid.get_return_value();
    //std::cout << lyricThread.get_return_value();
    //std::cout << "\n Finding " << prompt << "...";
    //lyricThread.join();
    std::cout << lyric;
    return 0;
}
