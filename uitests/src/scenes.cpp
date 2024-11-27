#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "scenes.hpp"

scenes::scenes(SDL_Window* windo, SDL_Renderer* rendere, SDL_Color backgroundColo, bool debugMod, int windowSizY, int windowSizX, int iconScal){
    this->window = windo;
    this->renderer = rendere;
    this->backgroundColor = backgroundColo;
        
    this->debugMode = debugMod;
    this->windowSizeY = windowSizY; 
    this->windowSizeX = windowSizX;
    this->iconScale = iconScal;

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

void scenes::returnButton(){

}

void scenes::baar(){
    SDL_Rect iconssize = {0, 0, 0, 0};
    SDL_Rect barsize = {0, 0, 0, 0};

    barsize.w = 1400+1400 * iconScale*0.05;
    barsize.h = 170+170 * iconScale*0.05;
    barsize.x = (windowSizeX - barsize.w) / 2;
    barsize.y = windowSizeY - 190;   

    iconssize.w = 252;
    iconssize.h = 162;
    iconssize.x = 100;
    iconssize.y = barsize.y;
    
    if (iconScale > 1){
        barsize.y = windowSizeY - 190 - (10*iconScale); 

        iconssize.w = 252+252 * iconScale*0.05;
        iconssize.h = 162+162 * iconScale*0.05;
        iconssize.y = (barsize.y - 225) + ((this->windowSizeY / 2) - (162+162 * iconScale*0.05));

        if (((this->windowSizeX / 2) - (((252+252 * iconScale*0.05) * 5 + (25*4)) / 2)) > 0){
            iconssize.x = 100 - ((this->windowSizeX / 2) - (((252+252 * iconScale*0.05) * 5 + (25*4)) / 2));
        }
        else {
            iconssize.x = ((this->windowSizeX / 2) - (((252+252 * iconScale*0.05) * 5 + (25*4)) / 2));
        }
    }
    
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255);
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
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        
        iconssize.x = 100;
        if (iconScale > 1){
            iconssize.x = 100 - ((this->windowSizeX / 2) - (((252+252 * iconScale*0.05) * 5 + (25*4)) / 2));
        }

        for (int i = 0; i < 5; i++){
            SDL_RenderDrawRect(renderer, &iconssize);
                    
            iconssize.x += iconssize.w + 25;
        }
        SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255);
    }
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

