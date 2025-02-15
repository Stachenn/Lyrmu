#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../include/sdlfont/font.cpp"
#include <vector>

class scenes{
    private:
        std::vector<SDL_Surface*> surfaces = {};
        std::vector<SDL_Texture*> textures = {};
        std::vector<int> lastSceneIndexes = {};

        SDL_Color red = {255, 0, 0};

        SDL_Texture *homet = nullptr;
        SDL_Texture *searcht = nullptr;
        SDL_Texture *randomt = nullptr;
        SDL_Texture *libraryt = nullptr;
        SDL_Texture *settingst = nullptr;
        SDL_Texture *bart = nullptr;

        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        SDL_Texture* cacheTxt = nullptr;
        SDL_Surface* cacheSurf = nullptr;
        TTF_Font* testFont = nullptr;

        int lastSceneIndex = 255;
        //textDisplay* sahabek = nullptr;

    public:
        SDL_Color backgroundColor = {0,0,0,0};
        SDL_Rect testRect = {500, 500, 100, 100};
        bool debugMode = false;
        bool objectDestroyed = false;

        int windowSizeY = 0;
        int windowSizeX = 0;
        int iconScale = 1;

        scenes(SDL_Window* windo, SDL_Renderer* rendere, SDL_Color backgroundColo, bool debugMod, int windowSizY, int windowSizX, int iconScal);
        ~scenes();

        void bar();
        void search();
        void settings();
        void library();
        void home();
        void random(); // 5 scenes

        void clearLastScene(std::vector<int> indexes);
        void renderScene(int sceneIndex, bool force = false);
};
