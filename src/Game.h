//
// Created by lmgd on 23/04/2021.
//
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H


class Game {
private:
    bool paused = false;
public:
    static Mix_Chunk *apple_sound;
    static Mix_Chunk *dying_sound;
    static Mix_Music *background_music;
    SDL_Renderer *renderer;
    SDL_Window *window;
    explicit Game(SDL_Renderer *renderer, SDL_Window *window);

    int run();

};


#endif //SNAKE_GAME_H
