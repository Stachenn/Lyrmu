// Stachenn 2023-2025

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../../include/jsonParser/parser.cpp"
#include "../include/sdlbutton/button.cpp"
#include "../include/sdlfont/font.cpp"

#include "scenes.cpp"

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
    // varible for reading file
    int configFileSize = 0;

    std::string configContent = "";

    std::ifstream configFile("res/config.json", std::ios::in | std::ios::ate);

    configFileSize = configFile.tellg();

    configFile.seekg(0, std::ios::beg);
    for (int i = 0; i < configFileSize+1; i++){
        configContent += configFile.get();
    }
    configFile.close();

    // definition of json parser for config file
    jsonParser config(configContent);

    if (config.parse() != JSON_OK){
        std::cout << "Error: Unable to parse file config.json / file does not exist / program cannot access its";
        return -1;
    }


    // window properties
    int windowSizeX = 1600;
    int windowSizeY = 830;

    // app properties from config file
    int currentScene = 0;
    int iconScale = 0;
    bool debugMode = false;
    bool needToRender = true;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    // definition of icons
    SDL_Texture *home = NULL;
    SDL_Texture *search = NULL;
    SDL_Texture *random = NULL;
    SDL_Texture *library = NULL;
    SDL_Texture *settings = NULL;
    SDL_Texture *bar = NULL;
    // event handler
    SDL_Event event;

    SDL_Color backgroundColor = hexToSDLColor(configValues[config.find("backgroundColor")].erase(0,2));

    // icons, buttons properties - pos, size
    SDL_Rect iconssize = {0, 0, 0, 0};
    SDL_Rect iconspos = {0, 0, 0, 0};
    SDL_Rect buttonShape = {500, 500, 500, 500};
    SDL_Rect background = {0, 0, 0, 0};

    SDL_Rect barsize = {0, 0, 0, 0};
    SDL_Rect barpos = {0, 0, 0, 0};

    // vectors for storing values from config file
    std::vector<std::string> configValues = config.getValues();
    std::vector<std::string> configNames = config.getNames();



    iconScale = std::stoi(configValues[config.find("iconScale")]);

    barsize.w = 1400+1400*iconScale*0.05;
    barsize.h = 170+170*iconScale*0.05;
    barsize.x = (windowSizeX - barsize.w) / 2;
    barsize.y = windowSizeY - 190;

    iconssize.w = 252;
    iconssize.h = 162;
    iconssize.x = 100;
    iconssize.y = barsize.y;

    if (iconScale > 1){
        iconssize.x = 100 - ((windowSizeX / 2) - (((252+252 * iconScale*0.05) * 5 + (25*4)) / 2));

        iconssize.w = 252+252*iconScale*0.05;
        iconssize.y = (barsize.y - 225) + ((windowSizeY / 2) - (162+162*iconScale*0.05));
    }

    background.x = 0;
    background.y = 0;
    background.w = windowSizeX;
    background.h = windowSizeY;

    if (configValues[config.find("DEBUG_MODE")] == "true"){
        debugMode = true;
    }

    window = SDL_CreateWindow("Test window", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, windowSizeX, windowSizeY, NULL);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255);

    scenes scenesMenager(window, renderer, backgroundColor, debugMode, windowSizeY, windowSizeX, iconScale);



    // init buttons using sdlbutton lib
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

    // app loop - rendering, button handling, etc.
    while (true){
        if (SDL_PollEvent(&event) != 0 || needToRender){
            //exiting app handling
            if (event.type == SDL_QUIT){
                break;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN){
                needToRender = true;
                //button handling
                if (homeb.isClicked(event)){
                    currentScene = 0;
                    std::cout << "home";
                }
                if (randomb.isClicked(event)){
                    currentScene = 1;
                    std::cout << "random";
                }
                if (searchb.isClicked(event)){
                    currentScene = 2;
                    std::cout << "search";
                }
                if (libraryb.isClicked(event)){
                    currentScene = 3;
                    std::cout << "library";
                }
                if (settingsb.isClicked(event)){
                    currentScene = 4;
                    std::cout << "settings";
                }
            }
            // section where when needed render app
            SDL_RenderClear(renderer);

            scenesMenager.home();
            scenesMenager.baar();

            SDL_RenderPresent(renderer);

            needToRender = false;
        }
    }
    // destroying sdl closing app
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
