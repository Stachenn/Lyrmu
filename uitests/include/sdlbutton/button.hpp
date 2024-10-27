#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

class button{
    private:
        SDL_Window* window = nullptr;
    public:
        SDL_Rect shape;

        button(SDL_Rect shap, SDL_Window* windo);
        ~button();

        int isClicked(SDL_Event event);

        void fadeOut(int speed); //SDL_SetTextureAlphaMod(texture, 0);
        void fadeIn(int speed);
};