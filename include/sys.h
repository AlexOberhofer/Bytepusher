/****************************************************************************** 
* 
* System interface for porting 
* (C) 2020 Alex Oberhofer
*
******************************************************************************/
#ifndef _SYSH_
#define _SYSH_


/* VIDEO */
void v_init();

void v_blit();

void v_fin();

/* AUDIO */
void a_init();

void a_poll();

void a_fin();

/* IO */

#endif