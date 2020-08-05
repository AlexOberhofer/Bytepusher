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

void v_init()
{
    printf("Start v_init()\n");

    printf("End v_init()\n");
}

void v_blit()
{
    printf("Start v_blit()\n");

    printf("End v_blit()\n");  
}

void v_fin()
{
    printf("Start v_fin()\n");

    printf("End v_fin()\n");    
}

#endif