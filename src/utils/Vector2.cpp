//
// Created by lmgd on 21/04/2021.
//

#include "Vector2.h"

Vector2::Vector2() {
    this->x = 0;
    this->y = 0;
}

Vector2::Vector2(float x, float y) {
    this->x = x;
    this->y = y;
}

void Vector2::set(float _x, float _y) {
    this->x = _x;
    this->y = _y;
}

void Vector2::set(Vector2 vector2) {
    this->x = vector2.x;
    this->y = vector2.y;
}

void Vector2::add(float add_x, float add_y) {
    this->x = this->x + add_x;
    this->x = this->y + add_y;
}

void Vector2::add(Vector2 vector2) {
    this->x = this->x + vector2.x;
    this->y = this->y + vector2.y;
}

int Vector2::int_x() const {
    return (int) this->x;
}

int Vector2::int_y() const {
    return (int) this->y;
}




