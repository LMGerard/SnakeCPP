//
// Created by lmgd on 22/04/2021.
//

#include "Apple.h"
Apple::Apple(SDL_Renderer *renderer) {
    this->sdlRenderer = renderer;
    this->img = IMG_LoadTexture(renderer, R"(C:\Users\lmgd\CLionProjects\Snake\resources\apple.png)");
    this->rect.w = 20; this->rect.h = 20;
    this->position.set(this->rect.w * 4, this->rect.h * 5);
};

void Apple::draw() {
    this->rect.x = this->position.int_x();
    this->rect.y = this->position.int_y();
    SDL_RenderCopy(this->sdlRenderer, this->img, nullptr, &this->rect);
}
