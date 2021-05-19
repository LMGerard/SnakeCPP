//
// Created by lmgd on 22/04/2021.
//
#include "Button.h"


Button::Button(SDL_Renderer *renderer, const char *normal_image_path, const char *hover_image_path, Vector2 position,
               Vector2 size) {
    this->renderer = renderer;
    this->normal_img = IMG_LoadTexture(renderer, normal_image_path);
    this->hover_img = IMG_LoadTexture(renderer, hover_image_path);

    this->rect.x = (int) (position.x - size.x / 2);
    this->rect.y = (int) (position.y - size.y / 2);
    this->rect.w = size.int_x();
    this->rect.h = size.int_y();
}

void Button::draw(int mouse_x, int mouse_y) {
    if (this->collide_with_point(mouse_x, mouse_y))
        SDL_RenderCopy(this->renderer, this->hover_img, nullptr, &this->rect);
    else
        SDL_RenderCopy(this->renderer, this->normal_img, nullptr, &this->rect);
}

bool Button::collide_with_point(int mouse_x, int mouse_y) const {
    return (
            mouse_x > this->rect.x &&
            mouse_x < this->rect.x + this->rect.w &&
            mouse_y > this->rect.y &&
            mouse_y < this->rect.y + this->rect.h
    );
}