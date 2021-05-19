//
// Created by lmgd on 22/04/2021.
//
#include "utils/Button.h"
#include <SDL_image.h>
#include <SDL.h>
#ifndef SNAKE_MENU_H
#define SNAKE_MENU_H


class Menu {
public:
    SDL_Renderer *renderer;
    explicit Menu(SDL_Renderer *renderer);

    int run() const;

};

class PlayButton : public Button{
public:
    explicit PlayButton(SDL_Renderer *renderer);
};

#endif //SNAKE_MENU_H
