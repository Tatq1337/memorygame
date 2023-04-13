#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "Game.h"
#include <time.h>
#include <stdlib.h>
#include "Utils.h"
#include <SDL_ttf.h>

int init(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    IMG_Init(IMG_INIT_PNG);
    if (TTF_Init() < 0)
    {
        SDL_Log("%s", TTF_GetError());
        return -1;
    }
    font = TTF_OpenFont("assets/font.ttf", 24);


    return 0;
}

int main(int argc, char** argv){
    (void)argc;(void)argv;
    if(init() == 1){ //init
        return 1;
    }
    srand(time(NULL));
    SDL_Window *window = SDL_CreateWindow("MEMORY GAME ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
    if(!window){
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    last_game_step = SDL_GetTicks();
    gameStart();

    int running = 1;
    while(running == 1){
        tickClock();

        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    printf("\t");
                    onClick(event.button.x, event.button.y);
                    break;
                case SDL_KEYDOWN:
                    printf("KEY PRESS : %d\n", event.key.keysym.sym);
                default:
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 34, 34, 34, 255);
        SDL_RenderClear(renderer);
        gameUpdate();
        gameDraw();
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}

