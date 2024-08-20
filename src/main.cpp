#include "../include/jsonParser/dynamicArray.cpp"
#include "../include/jsonParser/parser.cpp"
#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

size_t reciveData(char* recivedData, size_t size, size_t nmemb, std::string varStoragedData){
    varStoragedData += recivedData;
    return 0;
}

int main(int argc, char* argv[]){
    #ifdef _WIN32 || _WIN64
        system("chcp 65001");
    #endif

    std::string songName = "";
    std::string jsonFromSite;

    std::vector <std::string> values;
    std::vector <std::string> names;

    CURL *curl = curl_easy_init();
    CURLINFO info;
    CURLcode res;

    jsonParser test("");

    std::cout << "type name of song";
    std::cin >> songName;
    if (curl){

        curl_easy_setopt(curl, CURLOPT_URL, std::string("https://lrclib.net/api/search?q=" + songName).c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, reciveData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonFromSite);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/1.0");

        curl_easy_perform(curl);

        test.content = jsonFromSite;
        curl_easy_cleanup(curl);
    }
    
    else{
        res = curl_easy_getinfo(curl, info, CURLINFO_HTTP_CONNECTCODE);
        std::cout << res;
        std::cout << "Error: connection with api failed (maybe)";
    }
    
    test.parse();
    values = test.getValues();
    names = test.getNames();

    int a = test.find("plainLyrics");
    std::cout << a;
	std::cout << values[8];

    if (a == -1){
        std::cout << "Error: can not find song / api changed";
        return -1;
    }


    //site.close();
    return 0;
}
