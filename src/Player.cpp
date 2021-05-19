//
// Created by lmgd on 21/04/2021.
//

#include "Player.h"
#include "iostream"

Player::Player(SDL_Renderer *renderer) {
    this->sdlRenderer = renderer;
    this->snake_head_img = IMG_LoadTexture(renderer, R"(C:\Users\lmgd\CLionProjects\Snake\resources\snake_head.png)");
    this->snake_body_img = IMG_LoadTexture(renderer, R"(C:\Users\lmgd\CLionProjects\Snake\resources\snake_body.png)");
    this->snake_tail_img = IMG_LoadTexture(renderer, R"(C:\Users\lmgd\CLionProjects\Snake\resources\snake_tail.png)");
    this->rect.x = 100;
    this->rect.y = 100;
    this->rect.w = 20;
    this->rect.h = 20;
    this->speed = this->rect.w;
    this->_asked_direction.set(1, 0);

    this->snake_parts.emplace_back(this->rect.x, this->rect.y);
    this->snake_parts.emplace_back(this->rect.x - this->rect.w, this->rect.y);
    this->snake_parts.emplace_back(this->rect.x - 2 * this->rect.w, this->rect.y);

    this->snake_length = 3;
};

void Player::draw() {
    SDL_Rect dstrect;
    dstrect.w = this->rect.w;
    dstrect.h = this->rect.h;
    int angle;
    size_t size = this->snake_parts.size();
    for (int i = 0; i < size; i++) {
        dstrect.x = this->snake_parts[i].int_x();
        dstrect.y = this->snake_parts[i].int_y();
        if (i == 0) {
            if (i + 1 < size){
                if (this->snake_parts[i].x < this->snake_parts[i + 1].x)
                    angle = 180;
                else if (this->snake_parts[i].x > this->snake_parts[i + 1].x)
                    angle = 0;
                else if ((this->snake_parts[i].y > this->snake_parts[i + 1].y))
                    angle = 90;
                else
                    angle = 270;
            } else angle = 90;

            SDL_RenderCopyEx(this->sdlRenderer, this->snake_head_img, nullptr, &dstrect, angle, nullptr, SDL_FLIP_NONE);
        } else if (i + 1 < size) {
            if (this->snake_parts[i].x == this->snake_parts[i - 1].x)
                angle = 90;
            else
                angle = 0;
            SDL_RenderCopyEx(this->sdlRenderer, this->snake_body_img, nullptr, &dstrect, angle, nullptr, SDL_FLIP_NONE);
        } else {
            if (this->snake_parts[i].x < this->snake_parts[i - 1].x)
                angle = 0;
            else if (this->snake_parts[i].x > this->snake_parts[i - 1].x)
                angle = 180;
            else if ((this->snake_parts[i].y > this->snake_parts[i - 1].y))
                angle = 270;
            else
                angle = 90;
            SDL_RenderCopyEx(this->sdlRenderer, this->snake_tail_img, nullptr, &dstrect, angle, nullptr, SDL_FLIP_NONE);
        }
    }
}

int Player::update() {
    // if dying remove each part one by one, then go back to menu
    if (this->dying) {
        if (this->snake_parts.empty())
            return -1;
        this->snake_parts.erase(this->snake_parts.begin());
        return 0;
    }
    // add snake_part
    if (this->snake_parts.size() != this->snake_length)
        this->snake_parts.emplace_back(0, 0);
    // change snake direction when on right coordinates
    if (this->rect.x % this->rect.w == 0 && this->rect.y % this->rect.h == 0 &&
        abs(this->_asked_direction.int_x()) != abs(this->direction.int_x()))
        this->set_direction(this->_asked_direction);
    // update head position
    this->rect.x += this->change.int_x();
    this->rect.y += this->change.int_y();
    // change position if going out of screen
    if (this->rect.x < 0)
        this->rect.x = 500 - this->rect.w;
    else if (this->rect.x >= 500)
        this->rect.x = 0;
    if (this->rect.y < 0)
        this->rect.y = 500 - this->rect.w;
    else if (this->rect.y >= 500)
        this->rect.y = 0;
    // update parts position
    for (int i = this->snake_parts.size() - 1; i > 0; i--) {
        this->snake_parts[i].set(this->snake_parts[i - 1]);
    }
    this->snake_parts[0].set(this->rect.x, this->rect.y);
    // dying if collide with himself
    if (this->collide_self())
        this->dying = true;
    return 0;
}

void Player::ask_direction(float x, float y) {
    this->_asked_direction = Vector2(x, y);
}

void Player::eat_apple() {
    this->snake_length++;
}

bool Player::collide_self() {
    auto rect = SDL_Rect();
    for (int i = 3; i < this->snake_parts.size(); ++i) {
        rect.x = this->snake_parts[i].int_x();
        rect.y = this->snake_parts[i].int_y();
        rect.w = this->rect.w;
        rect.h = this->rect.h;
        if (this->collide_rect(rect))
            return true;
    }
    return false;
}

void Player::set_direction(Vector2 vector2) {
    this->direction.set(vector2);

    auto norm = (float) sqrt(pow(this->direction.x, 2) + pow(this->direction.y, 2));

    if (norm == 0.)
        this->change.set(0, 0);
    else
        this->change.set(this->speed / norm * this->direction.x, this->speed / norm * this->direction.y);
}

bool Player::collide_rect(SDL_Rect sdlRect) const {
    auto left_A = this->rect.x;
    auto right_A = this->rect.x + this->rect.w;
    auto top_A = this->rect.y;
    auto bottom_A = this->rect.y + this->rect.h;

    auto left_B = sdlRect.x;
    auto right_B = sdlRect.x + sdlRect.w;
    auto top_B = sdlRect.y;
    auto bottom_B = sdlRect.y + sdlRect.h;

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