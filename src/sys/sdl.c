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

#define SYSTRACE 0
#define FB_XY 256 /* Dimenson of our square framebuffer */

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Texture* texture = NULL;

/* Uses the same key layout as my chip 8 emulator */
static const SDL_Keycode keymap[] = { 
	SDLK_x, SDLK_1, SDLK_2, SDLK_3, SDLK_q, SDLK_w, SDLK_e, SDLK_a,
	SDLK_s, SDLK_d, SDLK_z, SDLK_c, SDLK_4, SDLK_r, SDLK_f, SDLK_v,
};

typedef struct pixel {
    uint8_t a; 
    uint8_t r; 
    uint8_t g; 
    uint8_t b; 
} pixel_t;


/* Sleep */
void s_sleep() 
{
    SDL_Delay(4);
}

/* Initialize video subsystem */
void v_init()
{
    if(SYSTRACE) printf("Start v_init()\n");

    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        exit(1);
    } else 
    {
        window = SDL_CreateWindow("Bytepusher", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, FB_XY , FB_XY, SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_STREAMING, FB_XY, FB_XY);
    }

    if(SYSTRACE) printf("End v_init()\n");
}

/* Draw texture data to screen */
void v_blit(pixel_t screen[][FB_XY], uint8_t ram[])
{
    if(SYSTRACE) printf("Start v_blit()\n");

    int x, y;
    for (x = 0; x < FB_XY; x++) 
    {
        for (y = 0; y < FB_XY; y++) 
        {
            uint8_t pixel = ram[(ram[5] << 16) | (y << 8) | x];
            screen[y][x].b = (pixel % 6) * 0x33;
            pixel /= 6;
            screen[y][x].g = pixel % 6 * 0x33;
            pixel /= 6;
            screen[y][x].r = pixel % 6 * 0x33;
            screen[y][x].a = 0xFF;
        }
    }

    SDL_UpdateTexture(texture, NULL, screen, FB_XY * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    if(SYSTRACE) printf("End v_blit()\n");  
}

/* cleanup */
void v_fin()
{
    if(SYSTRACE) printf("Start v_fin()\n");

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    if(SYSTRACE) printf("End v_fin()\n");    
}

/* Input polling */
int e_poll(uint8_t ram[]) 
{
    SDL_Event e;
    uint16_t inputdata;
    size_t i;

    /*pull our key data from io map*/
    inputdata = ram[0]<<8 | ram[1];
    
	while (SDL_PollEvent(&e)) 
    {
		switch(e.type) 
        {
            case SDL_QUIT: return 0;
            default:
            for (i = 0; i < sizeof(keymap)/sizeof(*keymap); i++)
            {
                if (e.key.keysym.sym == keymap[i])
                {
                    inputdata = (inputdata & ~(1 << i)) | (e.type == SDL_KEYDOWN)<<i;
                } else if (e.key.keysym.sym == SDLK_ESCAPE) 
                {
                    return 0;
                }
            }
			break;
        }

	}
	ram[0] = inputdata >> 8;
	ram[1] = inputdata & 0xFF;
    return 1;
}
#endif