#pragma once
#include <SDL_ttf.h>

#define SCREEN_WIDTH 750
#define SCREEN_HEIGHT 820

SDL_Renderer *renderer;

uint32_t deltaTime = 0;
Uint32 minimum_fps_delta_time = (1000 / 6); //
Uint32 last_game_step ;
uint32_t last_tick_time = 0;

void tickClock(){
    Uint32 now = SDL_GetTicks();

    if (last_game_step < now) {

        Uint32 delta_time = now - last_game_step;

        if (delta_time > minimum_fps_delta_time) {
            delta_time = minimum_fps_delta_time;
        }
        deltaTime = delta_time;
        last_game_step = now;
    }
}

typedef struct Vec2i{
    int x;
    int y;
} Vec2i;

typedef struct Color{
    int r;
    int g;
    int b;
} Color;

Vec2i newVec2(int x,int y){
    Vec2i v;
    v.x = x;
    v.y = y;

    return v;
}

TTF_Font* font;
SDL_Surface* surface = NULL;
SDL_Texture* texture = NULL;
void showText(int x, int y, const char* text, int r,int g,int b ) {

    SDL_Color fg ;
    fg.r = r;fg.g = g;fg.b = b;

    surface = TTF_RenderText_Solid(font, text, fg);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect srcRest;
    SDL_Rect desRect;
    TTF_SizeText(font, text, &srcRest.w, &srcRest.h);

    srcRest.x = 0;
    srcRest.y = 0;

    desRect.x = x;
    desRect.y = y;

    desRect.w = srcRest.w;
    desRect.h = srcRest.h;
    SDL_RenderCopy(renderer, texture, &srcRest, &desRect);

    SDL_DestroyTexture(texture);
}