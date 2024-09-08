#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

class button{
    private:
        SDL_Event event;
        SDL_Texture* texture = nullptr;
        SDL_Window* window = nullptr;
        std::string filePath = "";

    public:
        SDL_Rect shape = {0, 0, 0, 0};

        button(int posX, int posY, int sizeX, int sizeY, SDL_Window* windo);
        ~button();

        int isClicked();
        int changeTexuture(std::string newPath);
        
        void fadeOut(int speed); //SDL_SetTextureAlphaMod(texture, 0);
        void fadeIn(int speed);
};