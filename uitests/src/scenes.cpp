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
    notFounded = IMG_LoadTexture(renderer, "res/icons/notfoundedOLD.png");
    iconBorder = IMG_LoadTexture(renderer, "res/icons/iconBorder.png");
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
      SDL_DestroyTexture(notFounded);
      SDL_DestroyTexture(iconBorder);
      SDL_DestroyTexture(cacheTxt);

      //delete sahabek;

      objectDestroyed = true;
    }
}

void scenes::renderScene(int sceneIndex, bool forceToRender){
  if (sceneIndex > 5){
    std::cout << "Warning/Error: Scenes index is higher than 5\n";
  }
  else{
    if (!forceToRender && sceneIndex == lastSceneIndex){
        return;
    }
    if (sceneIndex != lastSceneIndex && sceneIndex != 0 && !forceToRender){
        std::cout << "Cleared on " << sceneIndex << '\n';
        SDL_RenderClear(renderer);
    }

    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255);

    if (sceneIndex == 0){
        this->bar();
        std::cout << "bar\n";

    }
    if (sceneIndex == 1){
        this->home();

        std::cout << "home\n";
    }
    if (sceneIndex == 2){
        this->random();

        std::cout << "random\n";
    }
    if (sceneIndex == 3){
        this->search();

        std::cout << "search\n";
    }
    if (sceneIndex == 4){
        this->library();

        std::cout << "library\n";
    }
    if (sceneIndex == 5){
        this->settings();

        std::cout << "settings\n";
    }
  }
}

void scenes::bar(){
    lastSceneIndex = 0;
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
        iconssize.x = barsize.x;

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
  lastSceneIndex = 1;
  cacheSurf = TTF_RenderText_Solid(testFont, "home", red);
  cacheTxt = SDL_CreateTextureFromSurface(renderer, cacheSurf);
  SDL_FreeSurface(cacheSurf);

  homeSongsPosition = {0, 0, 0, 0};
  homeSongsPosition.w = 120;
  homeSongsPosition.h = 120;
  homeSongsPosition.y = 120;
  homeSongsPosition.x = barsize.x;

  SDL_RenderCopy(renderer, notFounded, NULL, &homeSongsPosition);

  homeSongsPosition.w = 128;
  homeSongsPosition.h = 128;
  homeSongsPosition.y = 116;
  homeSongsPosition.x = barsize.x-4;
  SDL_RenderCopy(renderer, iconBorder, NULL, &homeSongsPosition);

  SDL_RenderCopy(renderer, cacheTxt, NULL , &testRect);
}

void scenes::library(){
  lastSceneIndex = 4;

  cacheSurf = TTF_RenderText_Solid(testFont, "library", red);
  cacheTxt = SDL_CreateTextureFromSurface(renderer, cacheSurf);
  SDL_FreeSurface(cacheSurf);
  SDL_RenderCopy(renderer, cacheTxt, NULL , &testRect);
}

void scenes::settings(){
  lastSceneIndex = 5;

  cacheSurf = TTF_RenderText_Solid(testFont, "settings", red);
  cacheTxt = SDL_CreateTextureFromSurface(renderer, cacheSurf);
  SDL_FreeSurface(cacheSurf);
  SDL_RenderCopy(renderer, cacheTxt, NULL , &testRect);
}

void scenes::random(){
  lastSceneIndex = 2;

  cacheSurf = TTF_RenderText_Solid(testFont, "random", red);
  cacheTxt = SDL_CreateTextureFromSurface(renderer, cacheSurf);
  SDL_FreeSurface(cacheSurf);
  SDL_RenderCopy(renderer, cacheTxt, NULL , &testRect);
}

void scenes::search(){
  lastSceneIndex = 3;

  for (int i = 30; i > 1; i--){
    SDL_RenderClear(renderer);
    this->bar();

    this->barsize.w = (1456 + this->iconScale * 14) / i;
    this->barsize.h = (164 + this->iconScale * 14) / i;
    this->barsize.x = (*this->windowSizeX - this->barsize.w) / 2;
    this->barsize.y = (*this->windowSizeY - this->barsize.h) / 3;
    SDL_RenderCopy(renderer, bart, NULL, &barsize);
    SDL_RenderPresent(renderer);
    SDL_Delay(30);
  }
}
