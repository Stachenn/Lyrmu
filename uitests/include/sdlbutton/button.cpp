#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "button.hpp"

button::button(SDL_Rect shap, SDL_Window* windo){
    shape = shap;
    window = windo;
}

button::~button(){
}

int button::isClicked(SDL_Event event){ 
    if (event.type == SDL_MOUSEBUTTONDOWN){
        if (SDL_GetWindowID(window) == event.button.windowID){         
            if (event.button.x < (shape.x + shape.w) && event.button.x > shape.x){
                if (event.button.y < (shape.y + shape.h) && event.button.y > shape.y){
                    return 1;
                }
            }
        }
    }
    return 0;
}

