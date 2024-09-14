#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

class button{
    private:
        SDL_Texture* texture = nullptr;
        SDL_Window* window = nullptr;
        std::string filePath = "";

    public:
        SDL_Rect shape = {0, 0, 0, 0};

        button(SDL_Rect shap, SDL_Window* windo, const char* pngTexturePath);
        ~button();

        int isClicked(SDL_Event event);
        int changeTexuture(const char* newPath);
        
        void fadeOut(int speed); //SDL_SetTextureAlphaMod(texture, 0);
        void fadeIn(int speed);
};