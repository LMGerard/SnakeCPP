//
// Created by lmgd on 21/04/2021.
//

#ifndef SNAKE_PLAYER_H
#define SNAKE_PLAYER_H

#include <SDL.h>
#include <SDL_image.h>

#include "utils/Vector2.h"
#include "vector"


class Player {
private:
    SDL_Renderer *sdlRenderer;

    SDL_Rect rect;
    int snake_length;
    Vector2 _asked_direction;
public:
    SDL_Texture *snake_head_img;
    SDL_Texture *snake_body_img;
    SDL_Texture *snake_tail_img;
    double update_time;
    bool dying = false;
    Vector2 direction;
    Vector2 change;
    float speed;
    std::vector<Vector2> snake_parts;

    explicit Player(SDL_Renderer *renderer);

    int update();

    void ask_direction(float x, float y);

    void draw();

    void eat_apple();
    void set_direction(Vector2 vector2);
    bool collide_self();
    bool collide_rect(SDL_Rect rect) const;
};

#endif //SNAKE_PLAYER_H


