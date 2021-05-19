//
// Created by lmgd on 22/04/2021.
//
#include <SDL.h>
#include <SDL_image.h>
#include "Vector2.h"

#ifndef SNAKE_BUTTON_H
#define SNAKE_BUTTON_H


class Button {
public:
    SDL_Renderer *renderer;
    SDL_Rect rect = SDL_Rect();
    SDL_Texture *normal_img;
    SDL_Texture *hover_img;

    Button(SDL_Renderer *renderer,
           const char *normal_image_path,
           const char *hover_image_path,
           Vector2 position,
           Vector2 size);

    void draw(int mouse_x, int mouse_y);

    bool collide_with_point(int mouse_x, int mouse_y) const;
};


#endif //SNAKE_BUTTON_H
