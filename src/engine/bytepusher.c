/****************************************************************************** 
* 
* Bytepusher VM impl
* (C) 2020 Alex Oberhofer
*
******************************************************************************/
#ifndef _BPUSH_
#define _BPUSH_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../../include/sys.h"

#define MEM_SIZE 0x1000008
#define CYCLES_PER_FRAME 65536
#define D_DIMENSION 256
#define W_SCALE 1

pixel_t screen[D_DIMENSION][D_DIMENSION];
uint8_t ram[MEM_SIZE];
uint32_t pc = 0;

/* Load file into system memory */
void load(FILE *fp)
{
    /* Determine file size */
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    /*Read into system memory */
    uint8_t *filebuffer = malloc(size);
    fread(filebuffer, size, 1, fp);
    memcpy(ram, filebuffer, size);

    free(filebuffer);
}

/* Reset VM System Memory */
void memclr()
{
    memset(ram, 0, MEM_SIZE);
}

/*Step through CPU Cycle loop */
void step() {
    uint32_t i;
    pc = ram[2] << 16 | ram[3] << 8 | ram[4];

    for (i = 0; i < CYCLES_PER_FRAME; i++) {
        int A = ram[pc]     << 16 | ram[pc + 1] << 8 | ram[pc + 2];
        int B = ram[pc + 3] << 16 | ram[pc + 4] << 8 | ram[pc + 5];

        ram[B] = ram[A];

        pc = ram[pc + 6] << 16 | ram[pc + 7] << 8 | ram[pc + 8];
    }
}

void usage() {
    printf("BytePusher by Alex Oberhofer\n");
    printf("Usage:\n");
    printf("$ bp <path to program>\n");
    exit(1);
}

int main(int argc, char* argv[]) 
{
    if(argc == 1) usage();

    v_init();

    /*load program into system memory*/
    FILE *fp = fopen(argv[1], "rb");
    load(fp);

    /* Never Return  */
    for(;;){
        e_poll(ram);
        step();
        v_blit(screen, ram);
        s_sleep();
    }
    
    v_fin();
}

#endif