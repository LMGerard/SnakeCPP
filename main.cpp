#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "src/Menu.h"
#include "src/Game.h"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500


int main(int argc, char *argv[]) {
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
        return -1;
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        return 1;
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || SDL_Init(SDL_INIT_AUDIO) < 0)
        return 1;

    SDL_Window *win = SDL_CreateWindow("Snake by LMGerard", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);;

    int page_index = 1;
    while (page_index != 0) {
        if (page_index == 1)
            page_index = Menu(renderer).run();
        else if (page_index == 2)
            page_index = Game(renderer, win).run();
    }
    Mix_CloseAudio();
    Mix_FreeChunk(Game::apple_sound);
    Mix_FreeChunk(Game::dying_sound);
    Mix_FreeMusic(Game::background_music);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    return 0;
}




