#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class scenes{
    private:
        SDL_Texture *homet = NULL;
        SDL_Texture *searcht = NULL;
        SDL_Texture *randomt = NULL;
        SDL_Texture *libraryt = NULL;
        SDL_Texture *settingst = NULL;
        SDL_Texture *bart = NULL;

        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        SDL_Color backgroundColor;
        
        bool debugMode = false;
        int windowSizeY = 0; 
        int windowSizeX = 0;
    public:
        scenes(SDL_Window* windo, SDL_Renderer* rendere, SDL_Color backgroundColo, bool debugMod, int windowSizY, int windowSizX);
        ~scenes();

        void baar();
        void search();
        void settings();
        void library();
        void home();
        void random();
};
