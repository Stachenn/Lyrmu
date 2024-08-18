#include "../include/jsonParser/dynamicArray.cpp"
#include "../include/jsonParser/parser.cpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char* argv[]){
    system("chcp 65001");
    std::string songName = "";
    std::string jsonFromSite = "";
	
    std::vector <std::string> values;
    std::vector <std::string> names;
	std::ifstream site;
    jsonParser test("");
    std::cout << "type name of song";
    std::cin >> songName;
    system("del cache.txt");
    system(std::string("curl https://lrclib.net/api/search?q=" + songName + " >> cache.txt").c_str());
    
    site.open("cache.txt", std::ios::ate);
    
    int siteSize = site.tellg();

    site.seekg(0, std::ios::beg);
    
    for (int i = 0; i < siteSize; i++){
        jsonFromSite += site.get();
    }
    
    test.content = jsonFromSite;
    test.parse();
    values = test.getValues();
    names = test.getNames();

    int a = test.find("\"plainLyrics\"");

	std::cout << values[8];
    if (a == -1){
        //std::cout << 'a';
		site.close();
        return 0;
    }
    

    site.close();
    return 0;
}
