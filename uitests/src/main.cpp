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
#include <filesystem>

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
    // config-setup varibles
    // ifstream configFile:106 line (i wont try creating file without constructor)
    std::string configContent = "";
    int configFileSize = 0;

    jsonParser config("");
    std::vector<std::string> configValues = {};
    std::vector<std::string> configNames = {};

    // icons, buttons properties - pos, size
    SDL_Rect iconssize = {0, 0, 0, 0};
    SDL_Rect barsize = {0, 0, 0, 0};

    //window properties
    int windowSizeX = 1600;
    int windowSizeY = 830;

    // render and debbuging varibles
    bool debugMode = false;
    bool needToRender = true;
    int iconScale = 0;
    int lastWindowXSize = 1600;
    int lastWindowYSize = 830;
    // window, renderer, etc. - window creation varibles
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Event event;
    SDL_Color backgroundColor = {0, 0, 0, 0};

    // init sdl2 libs
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

    // reading config and exctracting it
    std::ifstream configFile("res/config.json", std::ios::in | std::ios::ate);

    configFileSize = configFile.tellg();

    configFile.seekg(0, std::ios::beg);
    for (int i = 0; i < configFileSize+1; i++){
        configContent += configFile.get();
    }
    configFile.close();

    config.content = configContent;

    if (config.parse() != JSON_OK){
        std::cout << "Error: Unable to parse file config.json / file does not exist / program cannot access its";
        return -1;
    }
    // exctracting data from config to varibles
    configValues = config.getValues();
    configNames = config.getNames();
    iconScale = std::stoi(configValues[config.find("iconScale")]);
    backgroundColor = hexToSDLColor(configValues[config.find("backgroundColor")].erase(0,2));
    if (configValues[config.find("DEBUG_MODE")] == "true"){
        debugMode = true;
    }

    // re-scaling icons basing on config
    barsize.w = 1456 + iconScale * 14;                      // old 1400+1400 * this->iconScale*0.05; //1400 + this->iconScale * 14;
    barsize.h = 164 + iconScale * 14;
    barsize.x = (windowSizeX - barsize.w) / 2;
    barsize.y = windowSizeY - 204 - iconScale * 14;

    iconssize.w = 238 + iconScale * 14;
    iconssize.h = 162 + iconScale * 14;
    iconssize.x = barsize.x;
    iconssize.y = barsize.y;

    // init window and renderer
    window = SDL_CreateWindow("Test window", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, windowSizeX, windowSizeY, SDL_WINDOW_RESIZABLE); //SDL_WINDOW_RESIZABLE

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);

    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255);

    //init scenesMenager
    scenes scenesMenager(window, renderer, backgroundColor, debugMode, &windowSizeY, &windowSizeX, iconScale);
    scenesMenager.bar();
    // init buttons using sdlbutton lib
    button randomb(iconssize, window, "random");
    iconssize.x += iconssize.w + 25;

    button searchb(iconssize, window, "search");
    iconssize.x += iconssize.w + 25;

    button homeb(iconssize, window, "home");
    iconssize.x += iconssize.w + 25;

    button libraryb(iconssize, window, "library");
    iconssize.x += iconssize.w + 25;

    button settingsb(iconssize, window, "settings");

    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255);
    SDL_RenderClear(renderer);

    scenesMenager.renderScene(1);
    SDL_RenderPresent(renderer);
    // app loop - rendering, button handling, etc.
    while (true){
        if (SDL_PollEvent(&event) != 0 || needToRender){
            //exiting app handling
            //std::cout << "\n" << event.type << "\n";
            SDL_GetWindowSize(window, &windowSizeX, &windowSizeY);
            if (lastWindowXSize != windowSizeX){
                std::cout << std::filesystem::current_path() << " - Log : Change window size from " << lastWindowXSize <<  ',' << lastWindowYSize << " to" << windowSizeX << ',' << windowSizeY;
                // Resacling window
                barsize.w = 1456 + iconScale * 14;                      // old 1400+1400 * this->iconScale*0.05; //1400 + this->iconScale * 14;
                barsize.x = (windowSizeX - barsize.w) / 2;
                barsize.y = windowSizeY - 204 - iconScale * 14;

                iconssize.x = barsize.x; // 100 - deafult
                iconssize.y = barsize.y;

                randomb.shape.x = iconssize.x;

                iconssize.x += iconssize.w + 25;
                searchb.shape.x = iconssize.x;

                iconssize.x += iconssize.w + 25;
                homeb.shape.x = iconssize.x;

                iconssize.x += iconssize.w + 25;
                libraryb.shape.x = iconssize.x;

                iconssize.x += iconssize.w + 25;
                settingsb.shape.x = iconssize.x;

                lastWindowXSize = windowSizeX;
                lastWindowYSize = windowSizeY;
            }
            if (event.type == SDL_QUIT){
                break;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN){
                //button handling
                //beka2 = ((windowSizeX - barsize.w) / 2);
                std::cout << "Mouse click detected \n";
                //homeb.shape

                if (homeb.isClicked(event)){
                    scenesMenager.renderScene(0);
                    //SDL_RenderPresent(renderer);
                }
                if (randomb.isClicked(event)){
                    scenesMenager.renderScene(2);
                }
                if (searchb.isClicked(event)){
                    scenesMenager.renderScene(3);
                }
                if (libraryb.isClicked(event)){
                    scenesMenager.renderScene(4);
                }
                if (settingsb.isClicked(event)){
                    scenesMenager.renderScene(5);
                }
                scenesMenager.renderScene(1);
                SDL_RenderPresent(renderer);
            }
            // section where when needed render app

            needToRender = false;
        }
    }
    // destroying sdl closing app
    scenesMenager.~scenes();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
