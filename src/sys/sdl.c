/****************************************************************************** 
* 
* SDL 2 Implementation of sys.h interface 
* (C) 2020 Alex Oberhofer
*
******************************************************************************/
#ifndef _SYSH_
#define _SYSH_

#include <stdio.h>
#include <SDL2/SDL.h>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Texture* texture = NULL;

typedef struct pixel {
    uint8_t a; 
    uint8_t r; 
    uint8_t g; 
    uint8_t b; 
} pixel_t;

void v_init()
{
    printf("Start v_init()\n");

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Err\n");
    }

    window = SDL_CreateWindow("Bytepusher", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 256 , 256, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_STREAMING, 256, 256);

    printf("End v_init()\n");
}

void v_blit(pixel_t screen[][256], uint8_t ram[])
{
    printf("Start v_blit()\n");

    int x;
    for (x = 0; x < 256; x++) {
        int y;
        for (y = 0; y < 256; y++) {
            uint8_t pixel = ram[(ram[5] << 16) | (y << 8) | x];
            screen[y][x].b = (pixel % 6) * 0x33;
            pixel /= 6;
            screen[y][x].g = pixel % 6 * 0x33;
            pixel /= 6;
            screen[y][x].r = pixel % 6 * 0x33;
            screen[y][x].a = 0xFF;
        }
    }

    SDL_UpdateTexture(texture, NULL, screen, 256 * sizeof(uint32_t));
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    printf("End v_blit()\n");  
}

void v_fin()
{
    printf("Start v_fin()\n");

    printf("End v_fin()\n");    
}

void e_poll() 
{
    SDL_Event e;
    while(SDL_PollEvent(&e)) 
    {
        switch (e.type) 
        {
            case SDL_QUIT:
                exit(1);
            }
        }
}

void s_sleep() 
{
    SDL_Delay(1000);
}

#endif