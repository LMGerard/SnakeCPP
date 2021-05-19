//
// Created by lmgd on 23/04/2021.
//
#include <random>
#include <ctime>

#include "Game.h"
#include "Player.h"
#include "Apple.h"
#include "Sprite.h"

typedef std::mt19937 MyRNG;

Mix_Chunk *Game::apple_sound = nullptr;
Mix_Chunk *Game::dying_sound = nullptr;
Mix_Music *Game::background_music = nullptr;

Game::Game(SDL_Renderer *renderer, SDL_Window *window) : renderer(renderer), window(window) {
    if (Game::apple_sound == nullptr)
        Game::apple_sound = Mix_LoadWAV(R"(C:\Users\lmgd\CLionProjects\Snake\resources\apple_sound.mp3)");
    if (Game::dying_sound == nullptr)
        Game::dying_sound = Mix_LoadWAV(R"(C:\Users\lmgd\CLionProjects\Snake\resources\dying_sound.mp3)");
    if (Game::background_music == nullptr)
        Game::background_music = Mix_LoadMUS(R"(C:\Users\lmgd\CLionProjects\Snake\resources\thefatrat-xenogenesis.mp3)");
}

int Game::run() {
    MyRNG rng;
    rng.seed(time(nullptr));
    std::uniform_int_distribution<uint32_t> uint_dist25(0, 24);

    Sprite pause = Sprite(renderer, R"(C:\Users\lmgd\CLionProjects\Snake\resources\pause_text.png)");
    pause.rect.w *= 5; pause.rect.h *= 5;
    pause.rect.x = 250 - pause.rect.w / 2; pause.rect.y = 250 - pause.rect.h / 2;
    Apple apple = Apple(renderer);
    apple.position.set(uint_dist25(rng) * apple.rect.w, uint_dist25(rng) * apple.rect.h);
    Player player = Player(renderer);

    Mix_PlayMusic(Game::background_music, -1);
    Mix_VolumeMusic(40);

    SDL_ShowCursor(0);
    int page_index = 0;
    Uint32 timer = SDL_GetTicks();
    while (true) {
        // event handling
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                break;
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                this->paused = !this->paused;
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN)
                player.ask_direction(0, 1);
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP)
                player.ask_direction(0, -1);
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT)
                player.ask_direction(1, 0);
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT)
                player.ask_direction(-1, 0);
        }
        if (!(SDL_GetWindowFlags(this->window) & SDL_WINDOW_INPUT_FOCUS))
            this->paused = true;
        if (!this->paused) {
            if (SDL_GetTicks() - timer > player.update_time) {
                timer = SDL_GetTicks();

                if (player.dying)
                    Mix_PlayChannel(0, Game::dying_sound, 0);
                else
                    player.update_time = 100 * pow(0.97, player.snake_parts.size());

                if (player.update() < 0) {
                    page_index = 1;
                    break;
                };

                if (player.collide_rect(apple.rect)) {
                    Mix_PlayChannel(0, Game::apple_sound, 0);
                    player.eat_apple();
                    apple.position.set(uint_dist25(rng) * apple.rect.w, uint_dist25(rng) * apple.rect.h);
                }
            }
        }

        SDL_RenderClear(this->renderer);

        apple.draw();
        player.draw();
        if (this->paused)
            pause.draw();
        SDL_RenderPresent(this->renderer);
    }
    Mix_PauseMusic();
    SDL_DestroyTexture(player.snake_body_img);
    SDL_DestroyTexture(player.snake_head_img);
    SDL_DestroyTexture(pause.img);
    SDL_DestroyTexture(apple.img);

    SDL_ShowCursor(1);
    return page_index;
}