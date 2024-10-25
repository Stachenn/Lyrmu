#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../../include/jsonParser/parser.cpp"
#include "../include/sdlbutton/button.cpp"

//#include "../include/sdlfont/font.cpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <cmath>

SDL_Color hexToSDLColor(std::string number){
    int result = 0;
    int cache = 0;
    int index = 0;
    std::string resultString = "";
    
    SDL_Color color;

    for (int i = 0; i < 3; i++){
        for (int j = 1; j > -1; j--){
            if (number[index] > 47 && number[index] < 58){
                result += (9 - (57 - number[index])) * pow(16, j);
            }
            else{
                cache = toupper(number[index]);
                if (cache > 64 && cache < 71){
                    result += ((5 - (70 - cache)) + 10) * pow(16, j);
                }
                else{
                    color.r = 0;
                    color.g = 0;
                    color.b = 0;
                    color.a = 255;
                    return color;
                }
            }
            index++;
        }
        for (int i = 3; i > std::to_string(result).length(); i--){
            resultString.append("0");
        }
        resultString.append(std::to_string(result));

        result = 0;
    }

    color.a = 255;
    color.r = std::stoi(resultString.substr(0, 3));
    color.g = std::stoi(resultString.substr(3, 3));
    color.b = std::stoi(resultString.substr(6, 3));
    return color;
}

int main(int argc, char** argv){
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cout << "Failed with initialization SDL2, Error: " << SDL_GetError();
        return -1;
    }
    if (IMG_Init(IMG_INIT_PNG) == 0){
        std::cout << "Failed with initialiaztion SDL2_image, Error: " << SDL_GetError();
        return -1;
    }
    if (TTF_Init() == -1){
        std::cout << "Failed with initialiaztion SDL2_ttf, Error: " << TTF_GetError();
        return -1;
    }
    int configFileSize = 0;
    std::string configContent = "";
    
    std::ifstream configFile("res/config.json", std::ios::in | std::ios::ate);

    configFileSize = configFile.tellg();

    configFile.seekg(0, std::ios::beg);

    for (int i = 0; i < configFileSize+1; i++){
        configContent += configFile.get();
    } 
    configFile.close();
    
    jsonParser config("");

    config.content = configContent;
    if (config.parse() != JSON_OK){
        std::cout << config.parse();
        std::cout << "Error: Unable to parse file config.json / file does not exist / program cannot access its";
        return -1;
    }
    
    int windowSizeX = 1600;
    int windowSizeY = 830; 

    std::vector<std::string> configValues = config.getValues();
    std::vector<std::string> configNames = config.getNames();
    bool debugMode = false;

    if (configValues[config.find("DEBUG_MODE")] == "true"){
        debugMode = true;
    }

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    
    SDL_Color backgroundColor = hexToSDLColor(configValues[config.find("backgroundColor")].erase(0, 2));

    SDL_Rect iconssize = {0, 0, 0, 0};
    SDL_Rect iconspos = {0, 0, 0, 0};

    SDL_Rect background = {0, 0, 0, 0};

    SDL_Rect barsize = {0, 0, 0, 0};
    SDL_Rect barpos = {0, 0, 0, 0};

    barsize.w = 1400;
    barsize.h = 170;
    barsize.x = (windowSizeX - barsize.w) / 2;
    barsize.y = windowSizeY - 190;

    iconssize.w = 252;
    iconssize.h = 162;
    iconssize.x = 110;

    iconssize.y = barsize.y;

    background.x = 0;
    background.y = 0;
    background.w = windowSizeX;
    background.h = windowSizeY;

    SDL_Texture *home = NULL;// = IMG_LoadTexture(renderer, "/home/stanislaw/Project/CppCode/spotif/uitests/build/debug/home.png");
    //std::cout << IMG_LoadTexture(renderer, "/home/stanislaw/Project/CppCode/spotif/uitests/build/debug/home.png");
    SDL_Texture *search = NULL;
    SDL_Texture *random = NULL;
    SDL_Texture *library = NULL;
    SDL_Texture *settings = NULL;
    SDL_Texture *bar = NULL;
    
    SDL_Event event;
    
    window = SDL_CreateWindow("Test window", SDL_WINDOWPOS_UNDEFINED, 
                              SDL_WINDOWPOS_UNDEFINED, windowSizeX, windowSizeY, NULL);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    
    //SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255);
    //SDL_RenderFillRect(renderer, &background);
    bool needToRender = true;
    // SDL_RenderPresent(renderer);    

    home = IMG_LoadTexture(renderer, "res/icons/home.png");
    search = IMG_LoadTexture(renderer, "res/icons/search.png");
    random = IMG_LoadTexture(renderer, "res/icons/random.png");
    library = IMG_LoadTexture(renderer, "res/icons/library.png");
    settings = IMG_LoadTexture(renderer, "res/icons/settings.png");
    bar = IMG_LoadTexture(renderer, "res/interface/bar.png");

    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255);    
    
    SDL_Rect buttonShape = {500, 500, 500, 500};

    button testbutton(buttonShape, window);
    
    button randomb(iconssize, window);
    iconssize.x += iconssize.w + 25;

    button searchb(iconssize, window);
    iconssize.x += iconssize.w + 25;

    button homeb(iconssize, window);
    iconssize.x += iconssize.w + 25;

    button libraryb(iconssize, window);
    iconssize.x += iconssize.w + 25;

    button settingsb(iconssize, window);
    iconssize.x += iconssize.w + 25;

    while (true){
        if (SDL_PollEvent(&event) != 0 || needToRender){ 
            if (event.type == SDL_QUIT){
                break;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN){
                while (true){
                    if (homeb.isClicked(event)){
                        std::cout << "home";
                        break;
                    }
                    if (randomb.isClicked(event)){
                        std::cout << "random";
                        break;
                    }
                    if (searchb.isClicked(event)){
                        std::cout << "search";
                        break;
                    }
                    if (libraryb.isClicked(event)){
                        std::cout << "library";
                        break;
                    }
                    if (settingsb.isClicked(event)){
                        std::cout << "settings";
                        break;
                    }
                    else{
                        break;
                    }
                }
            }
            SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255);
            SDL_RenderClear(renderer);

            SDL_RenderCopy(renderer, bar, NULL, &barsize);
            
            SDL_RenderCopy(renderer, random, NULL, &iconssize);
            iconssize.x += iconssize.w + 25;

            SDL_RenderCopy(renderer, search, NULL, &iconssize);
            iconssize.x += iconssize.w + 25;

            SDL_RenderCopy(renderer, home, NULL, &iconssize);
            iconssize.x += iconssize.w + 25;

            SDL_RenderCopy(renderer, library, NULL, &iconssize);
            iconssize.x += iconssize.w + 25;
            
            SDL_RenderCopy(renderer, settings, NULL, &iconssize);
            
            if (debugMode){
                iconssize.x = 110;

                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                for (int i = 0; i < 5; i++){
                    SDL_RenderDrawRect(renderer, &iconssize);
                    
                    iconssize.x += iconssize.w + 25;
                }
                SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255);
            }
            iconssize.x = 110;

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderDrawRect(renderer, &background);
            SDL_RenderPresent(renderer);
            
            needToRender = false;
        }
        //testbutton.isClicked();
    }
    SDL_DestroyTexture(home);
    SDL_DestroyTexture(random);
    SDL_DestroyTexture(search);
    SDL_DestroyTexture(library);
    SDL_DestroyTexture(settings);
    SDL_DestroyTexture(bar);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    
    return 0;
}
