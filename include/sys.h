#ifndef _SYSH_
#define _SYSH_
/* System interface for porting */


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