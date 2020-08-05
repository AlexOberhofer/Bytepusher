/****************************************************************************** 
* 
* System interface for porting 
* (C) 2020 Alex Oberhofer
*
******************************************************************************/
#ifndef _SYSH_
#define _SYSH_

typedef struct pixel {
    uint8_t a; 
    uint8_t r; 
    uint8_t g; 
    uint8_t b; 
} pixel_t;

/* VIDEO */
void v_init();

void v_blit(pixel_t screen[][256], uint8_t ram[]);

void v_fin();

/* AUDIO */
void a_init();

void a_poll();

void a_fin();

/* IO */

void e_poll();

/* zzz... */
void s_sleep();

#endif