#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "button.hpp"

button::button(int posX, int posY, int sizeX, int sizeY, SDL_Window* windo){
    shape.x = posX;
    shape.y = posY;
    shape.w = sizeX;
    shape.h = sizeY;
    window = windo;
}

button::~button(){
    SDL_DestroyTexture(texture);
}

int button::isClicked(){
    //SDL_PollEvent(&event);
    //std::cout << event.type;
    /*if (event.type == SDL_MOUSEBUTTONEVENT){
        if (SDL_GetWindowID(window) == event.button.windowID){
            if (event.button.type == SDL_MOUSEBUTTONDOWN){
                
                if (event.button.x < (shape.x + shape.w) && event.button.x > shape.x){
                    if (event.button.y < (shape.y + shape.h) && event.button.y > shape.y){
                        return 1;
                    }
                }
                
            }
        }
    }
    */
    return 0;
}

