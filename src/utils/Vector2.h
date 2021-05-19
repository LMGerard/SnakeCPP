//
// Created by lmgd on 21/04/2021.
//

#ifndef SNAKE_VECTOR2_H
#define SNAKE_VECTOR2_H


class Vector2 {
public:
    float x;
    float y;
    Vector2();
    Vector2(float x, float y);

    void set(float x, float y);
    void set(Vector2 vector2);

    void add(float x, float y);
    void add(Vector2 vector2);

    int int_x() const;
    int int_y() const;
};


#endif //SNAKE_VECTOR2_H
