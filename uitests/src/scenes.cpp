// Stachenn 2023-2025

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "scenes.hpp"
#include "../include/sdlfont/font.cpp"
// problem here \/
scenes::scenes(SDL_Window* windo, SDL_Renderer* rendere, SDL_Color backgroundColo, bool debugMod, int* windowSizY, int* windowSizX, int iconScal){

    this->window = windo;
    this->renderer = rendere;
    this->backgroundColor = backgroundColo;

    this->debugMode = debugMod;
    this->windowSizeY = windowSizY;
    this->windowSizeX = windowSizX;
    this->iconScale = iconScal;
    testFont = TTF_OpenFont("res/fonts/inter.ttf", 12);

    homet = IMG_LoadTexture(renderer, "res/icons/home.png");
    searcht = IMG_LoadTexture(renderer, "res/icons/search.png");
    randomt = IMG_LoadTexture(renderer, "res/icons/random.png");
    libraryt = IMG_LoadTexture(renderer, "res/icons/library.png");
    settingst = IMG_LoadTexture(renderer, "res/icons/settings.png");
    bart = IMG_LoadTexture(renderer, "res/interface/bar.png");


    //SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255);

}
scenes::~scenes(){
    if (objectDestroyed == false){
      TTF_CloseFont(testFont);
      SDL_DestroyTexture(homet);
      SDL_DestroyTexture(randomt);
      SDL_DestroyTexture(searcht);
      SDL_DestroyTexture(libraryt);
      SDL_DestroyTexture(settingst);
      SDL_DestroyTexture(bart);
      SDL_DestroyTexture(cacheTxt);
      //delete sahabek;

      objectDestroyed = true;
    }
}

void scenes::renderScene(int sceneIndex, bool forceToRender){
  if (sceneIndex > 5){
    std::cout << "Warning/Error: Scenes index is higher than 5";
  }
  else{
    std::cout << "\n" << "lastSceneIndex ==" << lastSceneIndex;
    std::cout << "\n" << "sceneIndex ==" << sceneIndex;

    if (!forceToRender && sceneIndex == lastSceneIndex){
        return;
    }
    if (sceneIndex != lastSceneIndex && sceneIndex != 1){
        std::cout << "\n" << "Cleared on " << sceneIndex;
        SDL_RenderClear(renderer);
    }
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255);

    if (sceneIndex == 0){
        this->home();

        std::cout << "home";
    }
    if (sceneIndex == 1){
        this->bar();

        std::cout << "bar";
    }
    if (sceneIndex == 2){
        this->random();

        std::cout << "random";
    }
    if (sceneIndex == 3){
        this->search();

        std::cout << "search";
    }
    if (sceneIndex == 4){
        this->library();

        std::cout << "library";
    }
    if (sceneIndex == 5){
        this->settings();

        std::cout << "settings";
    }
  }
}

void scenes::bar(){
    lastSceneIndex = 1;
    //standard w1 == 1470
    //standard h1 == 178
    //standard w2 == 1540
    //standard h2 == 187

    this->barsize.w = 1456 + this->iconScale * 14;// old 1400+1400 * this->iconScale*0.05; //1400 + this->iconScale * 14;
    this->barsize.h = 164 + this->iconScale * 14;
    this->barsize.x = (*this->windowSizeX - this->barsize.w) / 2;
    this->barsize.y = *this->windowSizeY - 204 - this->iconScale * 14;

    this->iconssize.w = 238 + this->iconScale * 14;
    this->iconssize.h = 162 + this->iconScale * 14;
    this->iconssize.x = this->barsize.x; // 100 - deafulte
    this->iconssize.y = this->barsize.y;
    std::cout << "b "<< iconssize.w;

    std::cout <<  "SCENES:"<< this->iconssize.x;
    SDL_RenderCopy(renderer, bart, NULL, &barsize);
    
    std::cout << "RANDOMSCENE:" << this->iconssize.x;
    SDL_RenderCopy(renderer, randomt, NULL, &iconssize);
    iconssize.x += iconssize.w + 25;

    std::cout << "SEACHSCNEEN:" << this->iconssize.x;
    SDL_RenderCopy(renderer, searcht, NULL, &iconssize);
    iconssize.x += iconssize.w + 25;

    std::cout << "HOMESCENE:" << this->iconssize.x;
    SDL_RenderCopy(renderer, homet, NULL, &iconssize);
    iconssize.x += iconssize.w + 25;

    std::cout << "LIBRARYSCEENE:" << this->iconssize.x;
    SDL_RenderCopy(renderer, libraryt, NULL, &iconssize);
    iconssize.x += iconssize.w + 25;

    std::cout << "SETTINGSSCENE:" << this->iconssize.x;
    SDL_RenderCopy(renderer, settingst, NULL, &iconssize);

    if (debugMode){
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        iconssize.x = barsize.x;
        std::cout << "debug:" << iconssize.x;
        for (int i = 0; i < 5; i++){
            SDL_RenderDrawRect(renderer, &iconssize);

            iconssize.x += iconssize.w + 25;
        }
        SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255);
    }
}
void scenes::clearLastScene(std::vector<int> indexes){
}

void scenes::home(){
  lastSceneIndex = 0;
  cacheSurf = TTF_RenderText_Solid(testFont, "beka3", red);
  cacheTxt = SDL_CreateTextureFromSurface(renderer, cacheSurf);
  SDL_FreeSurface(cacheSurf);
  SDL_RenderCopy(renderer, cacheTxt, NULL , &testRect);
}

void scenes::library(){
  lastSceneIndex = 4;

}

void scenes::settings(){
  lastSceneIndex = 5;
}

void scenes::random(){
  lastSceneIndex = 2;

}

void scenes::search(){
  lastSceneIndex = 3;

}
