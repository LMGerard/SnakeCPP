//
// Created by lmgd on 22/04/2021.
//
#include "SDL.h"
#include <SDL_image.h>
#include "utils/Vector2.h"
#ifndef SNAKE_APPLE_H
#define SNAKE_APPLE_H


class Apple {
public:
    SDL_Renderer *sdlRenderer;
    SDL_Texture *img;
    SDL_Rect rect;
    Vector2 position;
    Apple(SDL_Renderer* renderer);

    void draw();
};


#endif //SNAKE_APPLE_H
