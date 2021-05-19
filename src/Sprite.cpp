//
// Created by lmgd on 21/04/2021.
//

#include "Sprite.h"

Sprite::Sprite(SDL_Renderer *renderer, const char *image_path) {
    this->sdlRenderer = renderer;
    this->img = IMG_LoadTexture(renderer, image_path);

    this->rect.x = 0; this->rect.y = 0;
    this->rect.w = 50; this->rect.h = 50;
}

void Sprite::draw() {
    SDL_RenderCopy(this->sdlRenderer, this->img, nullptr, &this->rect);
}

bool Sprite::collide_rect(SDL_Rect _rect) const {
    auto left_A = this->rect.x;
    auto right_A = this->rect.x + this->rect.w;
    auto top_A = this->rect.y;
    auto bottom_A = this->rect.y + this->rect.h;

    auto left_B = _rect.x;
    auto right_B = _rect.x + _rect.w;
    auto top_B = _rect.y;
    auto bottom_B = _rect.y + _rect.h;

    if (bottom_A <= top_B)
        return false;
    if (top_A >= bottom_B)
        return false;
    if (right_A <= left_B)
        return false;
    if (left_A >= right_B)
        return false;
    return true;
}