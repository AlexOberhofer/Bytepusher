/****************************************************************************** 
* 
* Bytepusher VM impl
* (C) 2020 Alex Oberhofer
*
******************************************************************************/
#ifndef _BPUSH_
#define _BPUSH_

#include <stdio.h>
#include <stdint.h>
#include "../../include/sys.h"

#define MEM_SIZE 0x1000008
#define D_DIMENSION 256
#define W_SCALE 1

typedef struct pixel {
    uint8_t a; 
    uint8_t r; 
    uint8_t g; 
    uint8_t b; 
} pixel_t;

pixel_t screen[D_DIMENSION][D_DIMENSION];
uint8_t ram[MEM_SIZE];
uint32_t pc = 0;

/* Load file into system memory */
void load()
{

}

/* Reset VM System Memory */
void memclr()
{

}

/*Step through CPU Cycle loop */
void step() {

}

int main() 
{
    v_init();
    
    printf("Success :)\n");
}

#endif