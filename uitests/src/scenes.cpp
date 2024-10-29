#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "scenes.hpp"

scenes::scenes(SDL_Window* windo, SDL_Renderer* rendere, SDL_Color backgroundColo, bool debugMod, int windowSizY, int windowSizX){
    this->window = windo;
    this->renderer = rendere;
    this->backgroundColor = backgroundColo;
        
    this->debugMode = debugMod;
    this->windowSizeY = windowSizY; 
    this->windowSizeX = windowSizX;

    homet = IMG_LoadTexture(renderer, "res/icons/home.png");
    searcht = IMG_LoadTexture(renderer, "res/icons/search.png");
    randomt = IMG_LoadTexture(renderer, "res/icons/random.png");
    libraryt = IMG_LoadTexture(renderer, "res/icons/library.png");
    settingst = IMG_LoadTexture(renderer, "res/icons/settings.png");
    bart = IMG_LoadTexture(renderer, "res/interface/bar.png");
}

scenes::~scenes(){
    SDL_DestroyTexture(homet);
    SDL_DestroyTexture(randomt);
    SDL_DestroyTexture(searcht);
    SDL_DestroyTexture(libraryt);
    SDL_DestroyTexture(settingst);
    SDL_DestroyTexture(bart);
}
void scenes::baar(){
    SDL_Rect iconssize = {0, 0, 0, 0};
    SDL_Rect barsize = {0, 0, 0, 0};

    barsize.w = 1400;
    barsize.h = 170;
    barsize.x = (windowSizeX - barsize.w) / 2;
    barsize.y = windowSizeY - 190;

    iconssize.w = 252;
    iconssize.h = 162;
    iconssize.x = 110;
    iconssize.y = barsize.y;

    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, bart, NULL, &barsize);
            
    SDL_RenderCopy(renderer, randomt, NULL, &iconssize);
    iconssize.x += iconssize.w + 25;

    SDL_RenderCopy(renderer, searcht, NULL, &iconssize);
    iconssize.x += iconssize.w + 25;

    SDL_RenderCopy(renderer, homet, NULL, &iconssize);
    iconssize.x += iconssize.w + 25;

    SDL_RenderCopy(renderer, libraryt, NULL, &iconssize);
    iconssize.x += iconssize.w + 25;
            
    SDL_RenderCopy(renderer, settingst, NULL, &iconssize);
            
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
    //SDL_RenderDrawRect(renderer, &background);
    SDL_RenderPresent(renderer);
}

void scenes::home(){

}

void scenes::library(){

}

void scenes::settings(){

}

void scenes::random(){

}

void scenes::search(){

}

