#include "C:\cpp\spotif\lib\YouTube-Simple-Api\Youtube.cpp"

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]){
    std::string prompt = "";
    std::string fixedPrompt = "";

    std::cout << "Type song to download : ";
    std::getline(std::cin, prompt);

    //for (unsigned int i = 0; i < prompt.length(); i++){
    //    if (prompt[i] == ' '){
    //        fixedPrompt += "+";
    //    }
    //    else{
    //        fixedPrompt += prompt[i];
    //    }
    //}

    std::cout << "\n Finding " << prompt << "...";

    //std::system(std::string("curl https://www.youtube.com/results?search_query=" + fixedPrompt + " >> site.txt").c_str());
    //std::ifstream Site("site.txt", std::ios::out);
    
    //Site.seekg(0, std::ios::end);
    
    //int fileSize = 0;
    //fileSize = Site.tellg();

    //Site.seekg(0, std::ios::beg);
    
    //std::string fileContent;

    //for (int i = 0; i < fileSize+1; i++){
    //    fileContent += Site.get();
    //} 

    //int cursor = fileContent.find("{" "\"webCommandMetadata" "\":{" "\"url" "\":" "\"/watch?v=")+39;
    //int v = fileContent.find("src=" "\"https://i.ytimg.com/" "");
    
    std::string watchUrl = findVideo(prompt, "site.txt");
    //for (int i = 0; i < 11; i++){
    //    watchUrl += fileContent[cursor];
    //    cursor++;
    //}

    
    system(std::string("download.py " + std::string("https://www.youtube.com/watch?v=") + watchUrl).c_str());

    return 0;
}
