//
// Created by lmgd on 22/04/2021.
//
#include "iostream"
#include "Menu.h"

Menu::Menu(SDL_Renderer *renderer) : renderer(renderer) {}

int Menu::run() const {
    Vector2 mouse_pos = Vector2(0, 0);
    auto play_button = PlayButton(renderer);
    int page_index = 0;
    while (true) {
        SDL_RenderClear(renderer);
        play_button.draw(mouse_pos.x, mouse_pos.y);
        SDL_RenderPresent(renderer);

        SDL_Event e;
        SDL_WaitEvent(&e);

        if (e.type == SDL_QUIT)
            break;
        else if (e.type == SDL_MOUSEMOTION)
            mouse_pos.set(e.motion.x, e.motion.y);
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
            if (play_button.collide_with_point(e.button.x, e.button.y)) {
                page_index = 2;
                break;
            }
        } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == 13) { // ENTER KEY = 13
            page_index = 2;
            break;
        }
    }

    SDL_DestroyTexture(play_button.normal_img);
    SDL_DestroyTexture(play_button.hover_img);
    return page_index;
}


PlayButton::PlayButton(SDL_Renderer *renderer) :
        Button(renderer,
               R"(C:\Users\lmgd\CLionProjects\Snake\resources\play_button.png)",
               R"(C:\Users\lmgd\CLionProjects\Snake\resources\play_button_selected.png)",
               Vector2(250, 250), Vector2(300, 100)) {
}