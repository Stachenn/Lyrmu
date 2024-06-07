#include "C:\cpp\spotif\lib\YouTube-Simple-Api\Youtube.cpp"
#include "C:\cpp\spotif\lib\Genius-Simple-Api\lyric.cpp"
//#include "..\include\curl\curl.h"

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
    std::string prompt = "";    
    std::string watchUrl = "";
    std::string lyric = "";

    // ustalenie w konsoli system znakow ktory obsluguje polskie znaki "utf-8" 
    system("chcp 65001");

    //Get song from user
    std::cout << "Type song to download : ";
    std::getline(std::cin, prompt);
    std::cout << prompt;
    // ----


    std::thread lyricThread(getLyric, prompt, "lyric", std::ref(lyric));
    std::thread searchVid(findVideo, prompt, "site", std::ref(watchUrl));
    //getLyric(prompt, "lyric", lyric);
    //findVideo(prompt, "site", watchUrl);
    searchVid.join();
    //
    //std::cout << std::string("download.py ").c_str();
    
    system(std::string("download.py " + watchUrl).c_str()); 
    //std::cout << "|" << lyric << "|";
    //std::cout << "|" << watchUrl << "|";
    //std::cout << lyric;
    //watchUrl = searchVid.get_return_value();
    //std::cout << lyricThread.get_return_value();
    //std::cout << "\n Finding " << prompt << "...";
    lyricThread.join();
    std::cout << lyric;
    return 0;
}
