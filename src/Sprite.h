//
// Created by lmgd on 21/04/2021.
//
#ifndef SNAKE_SPRITE_H
#define SNAKE_SPRITE_H

#include <SDL.h>
#include <SDL_image.h>
#include "utils/Vector2.h"
#include <vector>

class Sprite {
public:
    SDL_Renderer *sdlRenderer;
    SDL_Texture *img;
    SDL_Rect rect{};

    Sprite(SDL_Renderer *renderer, const char *image_path);

    virtual void draw();

    bool collide_rect(SDL_Rect rect) const;
};


#endif //SNAKE_SPRITE_H
